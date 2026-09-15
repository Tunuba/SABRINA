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

-- Lectura y escritura de la RAM por direccion de la PS1 (0x80xxxxxx), para usar desde eval.
-- Van aqui y no en cada eval porque una URL larga hace que el servidor conteste 404.
local function p(a, t) return ffi.cast(t, PCSX.getMemPtr() + bit.band(a, 0x1fffff)) end
function rd32(a) return p(a, 'uint32_t*')[0] end
function wr32(a, v) p(a, 'uint32_t*')[0] = v end
function rd16(a) return p(a, 'uint16_t*')[0] end
function wr16(a, v) p(a, 'uint16_t*')[0] = v end
function rd8(a) return p(a, 'int8_t*')[0] end
function wr8(a, v) p(a, 'uint8_t*')[0] = v end

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

-- Contadores de paso por una direccion (punto de interrupcion que no pausa). Requiere arrancar el
-- emulador con -debugger -interpreter (emu.py lo hace con depurar=True).
--   contar?a=0x8003401c&t=Exec     pone el contador (t: Exec, Read o Write)
--   cuenta?a=0x8003401c            devuelve cuantas veces paso
Control.bps = {}
H.contar = function(req)
  local q = consulta(req)
  local a = tonumber(q.a)
  if not a then return error400('falta a') end
  local c = { n = 0 }
  c.bp = PCSX.addBreakpoint(a, q.t or 'Exec', tonumber(q.w or '4'), 'contador', function()
    c.n = c.n + 1
    return true
  end)
  Control.bps[a] = c
  return 'ok'
end
H.cuenta = function(req)
  local c = Control.bps[tonumber(consulta(req).a)]
  return c and tostring(c.n) or error400('no hay contador ahi')
end

-- Laboratorio de dano: justo cuando el juego entra al manejador de suelo de Sabrina (FUN_80033fc8,
-- a0 = objeto), escribe que esta en el suelo (+0x8c bit 0x10) sobre un suelo de tipo t (+0x80).
-- Asi el juego corre su propio codigo de dano sin tener que llegar a un nivel con lava.
--   suelo?t=4&n=1     inyecta n veces (una por pasada del manejador con el objeto de Sabrina)
H.suelo = function(req)
  local q = consulta(req)
  local t, n = tonumber(q.t or '4'), tonumber(q.n or '1')
  local hechos = 0
  Control.bpsuelo = PCSX.addBreakpoint(0x80033fc8, 'Exec', 4, 'suelo', function()
    if hechos >= n then return true end
    local a0 = PCSX.getRegisters().GPR.n.a0
    if a0 == rd32(0x8007caf8) then
      wr16(a0 + 0x80, t)
      wr16(a0 + 0x8c, bit.bor(rd16(a0 + 0x8c), 0x10))
      hechos = hechos + 1
    end
    return true
  end)
  return 'ok'
end

-- Captura de llamadas reales para verificar la descompilacion: las primeras n veces que el juego entra a
-- la direccion a, guarda los registros y toda la memoria (RAM de 2 MB y el scratchpad de 1 KB).
--   capturar?a=0x80047e48&n=5&dir=C:\...\capturas\RecogibleNoTomado[&inicio=5][&geo=1]
-- Deja en dir: NN.ram, NN.spad y NN.regs (una linea "r0 at v0 ... ra pc hi lo" en hexadecimal).
H.capturar = function(req)
  local q = consulta(req)
  local a, n, dir = tonumber(q.a), tonumber(q.n or '5'), q.dir
  -- inicio: numero del primer archivo (para sumar capturas a las que ya hay)
  -- geo=1: en vez de las primeras n llamadas, las llamadas 1, 4, 16, 64... (situaciones mas distintas)
  local inicio, geo = tonumber(q.inicio or '0'), q.geo == '1'
  if not a or not dir then return error400('faltan a o dir') end
  local hechas, llamadas, proxima = 0, 0, 1
  Control.bpcap = Control.bpcap or {}
  Control.bpcap[a] = PCSX.addBreakpoint(a, 'Exec', 4, 'captura', function()
    if hechas >= n then return true end
    llamadas = llamadas + 1
    if geo then
      if llamadas < proxima then return true end
      proxima = proxima * 4
    end
    local nombre = string.format('%s\\%02d', dir, inicio + hechas)
    local f = Support.File.open(nombre .. '.ram', 'TRUNCATE')
    f:write(ffi.string(PCSX.getMemPtr(), 0x200000))
    f:close()
    f = Support.File.open(nombre .. '.spad', 'TRUNCATE')
    f:write(ffi.string(PCSX.getScratchPtr(), 0x400))
    f:close()
    local r = PCSX.getRegisters()
    local t = {}
    for i = 0, 31 do t[#t + 1] = string.format('%08x', r.GPR.r[i]) end
    t[#t + 1] = string.format('%08x', r.pc)
    t[#t + 1] = string.format('%08x', r.GPR.n.hi)
    t[#t + 1] = string.format('%08x', r.GPR.n.lo)
    f = Support.File.open(nombre .. '.regs', 'TRUNCATE')
    f:write(table.concat(t, ' '))
    f:close()
    hechas = hechas + 1
    return true
  end)
  return 'ok'
end
H.capturadas = function(req)
  return 'ok'
end

H.salir = function(req)
  PCSX.nextTick(function() PCSX.quit(0) end)
  return 'ok'
end

PCSX.log('control.lua listo')
