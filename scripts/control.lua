-- Control remoto de PCSX-Redux por HTTP, para automatizar pruebas desde Python (emu.py).
-- Se carga con -dofile. Cada ruta queda en http://127.0.0.1:<puerto>/api/v1/lua/<nombre>
--   frames                    frames (vsync) desde que arranco
--   boton?b=CROSS,UP&f=10     mantiene esos botones pulsados f frames (nombres de PCSX.CONSTS.PAD.BUTTON)
--   eval?c=<codigo lua>       ejecuta el codigo y devuelve lo que retorne, como texto
--   guardar?n=<ruta>          guarda un estado del emulador en ese archivo
--   cargar?n=<ruta>           carga un estado desde ese archivo
--   salir                     cierra el emulador

local function decodificar(s)
  s = s:gsub('+', ' ')
  return (s:gsub('%%(%x%x)', function(h) return string.char(tonumber(h, 16)) end))
end

local function consulta(req)
  local t = {}
  local q = (req.urlData and req.urlData.query) or ''
  for par in q:gmatch('[^&]+') do
    local k, v = par:match('([^=]*)=?(.*)')
    t[decodificar(k)] = decodificar(v)
  end
  return t
end

local function error400(texto) return 'HTTP/1.1 400 Bad Request\r\n\r\n' .. texto end

Control = { frames = 0, pulsados = {} }
local pad = PCSX.SIO0.slots[1].pads[1]
local B = PCSX.CONSTS.PAD.BUTTON

-- Se guarda en Control para que el recolector de basura no se lleve el oyente
Control.oyente = PCSX.Events.createEventListener('GPU::Vsync', function()
  Control.frames = Control.frames + 1
  for b, n in pairs(Control.pulsados) do
    if n <= 1 then
      pad.clearOverride(b)
      Control.pulsados[b] = nil
    else
      Control.pulsados[b] = n - 1
    end
  end
end)

PCSX.WebServer = PCSX.WebServer or {}
PCSX.WebServer.Handlers = PCSX.WebServer.Handlers or {}
local H = PCSX.WebServer.Handlers

H.frames = function(req) return tostring(Control.frames) end

H.boton = function(req)
  local q = consulta(req)
  local f = tonumber(q.f or '6') or 6
  for nombre in (q.b or ''):gmatch('[^,]+') do
    local b = B[nombre:upper()]
    if not b then return error400('boton desconocido ' .. nombre) end
    pad.setOverride(b)
    Control.pulsados[b] = f
  end
  return 'ok'
end

H.eval = function(req)
  local q = consulta(req)
  local fn, err = loadstring(q.c or '')
  if not fn then return error400(tostring(err)) end
  local ok, r = pcall(fn)
  if not ok then return 'HTTP/1.1 500 Internal Server Error\r\n\r\n' .. tostring(r) end
  return tostring(r)
end

H.guardar = function(req)
  local q = consulta(req)
  if not q.n or q.n == '' then return error400('falta n') end
  local f = Support.File.open(q.n, 'TRUNCATE')
  f:writeMoveSlice(PCSX.createSaveState())
  f:close()
  return 'ok'
end

H.cargar = function(req)
  local q = consulta(req)
  if not q.n or q.n == '' then return error400('falta n') end
  local f = Support.File.open(q.n)
  if f:failed() then return error400('no se pudo abrir ' .. q.n) end
  PCSX.loadSaveState(f)
  f:close()
  return 'ok'
end

H.salir = function(req)
  PCSX.nextTick(function() PCSX.quit(0) end)
  return 'ok'
end

PCSX.log('control.lua listo')
