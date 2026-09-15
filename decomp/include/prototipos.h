/* Hecho por aridad.py: cuantos argumentos recibe cada funcion, para m2c. No editar.
 * Devuelve s32 si algun llamador lee v0 al volver y void si ninguno; las marcadas con ? solo
 * se llaman por punteros y no se sabe. */
s32 func_80010000(void); /* ? */
s32 BuclePrincipal(void); /* ? */
s32 func_80010604(void); /* ? */
s32 func_8001060C(void); /* ? */
s32 func_80010614(void); /* ? */
s32 func_8001061C(void); /* ? */
s32 func_80010624(void); /* ? */
s32 func_8001062C(s32, s32); /* ? */
s32 func_80010670(s32, s32); /* ? */
s32 func_800106C8(void); /* ? */
s32 start(void); /* ? */
void func_80010880(s32, s32);
void func_80010920(s32, s32, s32, s32);
void func_80010BD8(s32);
void ImprimirDepuracion(s32, s32, s32, s32);
void func_800112C0(s32, s32);
void func_800113DC(s32, s32);
s32 func_8001164C(s32, s32, s32);
s32 func_8001166C(s32, s32);
s32 func_80011704(s32, s32);
s32 func_8001179C(s32, s32);
s32 func_800117B8(s32);
s32 func_80011838(void); /* ? */
s32 func_80011850(s32, s32); /* ? */
s32 func_80011930(s32, s32); /* ? */
s32 func_80011B60(s32, s32); /* ? */
s32 func_80011D9C(s32, s32); /* ? */
s32 func_8001201C(s32); /* ? */
s32 func_80012040(s32); /* ? */
s32 func_80012054(s32, s32); /* ? */
void func_80012094(s32);
s32 func_800120DC(s32);
s32 func_8001210C(s32, s32, s32); /* ? */
s32 func_80012130(s32, s32, s32, s32); /* ? */
void func_800123E0(void);
s32 func_80012640(s32);
s32 func_80012790(s32); /* ? */
void func_800128CC(void);
s32 func_80012900(void);
s32 func_80012A44(s32);
void func_80012AE4(s32, s32, s32);
void func_80012B0C(s32);
void func_80012C80(s32);
void func_80012CDC(s32);
s32 func_80012D74(s32);
void func_80012DDC(s32, s32, s32, s32);
void SubirAVRAM(s32, s32);
void func_80012ECC(s32, s32);
s32 func_80012F2C(s32, s32, s32); /* ? */
void func_80012FE4(s32, s32);
s32 func_80013090(s32); /* ? */
void func_800130EC(s32);
s32 func_8001315C(s32); /* ? */
void func_8001321C(s32);
s32 func_80013714(s32, s32); /* ? */
s32 func_8001390C(s32, s32); /* ? */
s32 func_800139F8(s32, s32); /* ? */
s32 func_80013AE4(s32, s32, s32); /* ? */
s32 func_80013C28(s32); /* ? */
s32 func_80013D24(void); /* ? */
s32 LoadTPage(s32, s32, s32, s32);
s32 E00_OBJ_A8(void); /* ? */
s32 E00_OBJ_AC(s32); /* ? */
s32 LoadClut(s32, s32, s32);
s32 LoadClut2(s32, s32, s32);
void SetDefDrawEnv(s32, s32, s32, s32);
s32 E03_OBJ_78(void); /* ? */
void SetDefDispEnv(s32, s32, s32, s32);
s32 GetTPage(s32, s32, s32, s32);
s32 GetClut(s32, s32);
s32 AddPrim(s32, s32); /* ? */
void func_800140BC(s32);
void func_800140DC(s32, s32);
void func_8001410C(s32);
void func_8001412C(s32);
void func_8001414C(s32);
void func_8001416C(s32);
void func_8001418C(s32);
void func_800141AC(s32);
void func_800141CC(s32);
void SetDrawTPage(s32, s32, s32, s32);
void SetDrawMode(s32, s32, s32, s32);
s32 P41_OBJ_8C(void); /* ? */
void InitHeap(void);
s32 FlushCache(void); /* ? */
void GPU_cw(void);
void _bu_init(void);
void func_800142FC(void);
s32 DeliverEvent(void); /* ? */
s32 OpenEvent(void);
void CloseEvent(void);
void WaitEvent(void);
s32 TestEvent(void);
void EnableEvent(void);
s32 InitPAD2(void); /* ? */
s32 StartPAD2(void); /* ? */
s32 StopPAD2(void); /* ? */
s32 PAD_init2(void); /* ? */
void ReturnFromException(void);
void ResetEntryInt(void);
void HookEntryInt(void);
s32 func_800143E4(void);
s32 func_800143F4(void); /* ? */
s32 open(void);
s32 lseek(void);
s32 read(void);
s32 write(void);
void close(void);
s32 firstfile2(void);
s32 nextfile(void);
s32 erase(void);
void ChangeClearPAD(void);
void SysEnqIntRP(void);
void SysDeqIntRP(void);
void ChangeClearRCnt(void);
void func_800144C4(s32, s32, s32);
s32 func_80014560(s32); /* ? */
void func_80014598(s32);
s32 EnablePAD(void); /* ? */
s32 DisablePAD(void); /* ? */
s32 _patch_pad(void); /* ? */
s32 func_80014670(s32, s32, s32); /* ? */
s32 func_80014774(s32, s32);
s32 func_80014910(void); /* ? */
s32 func_80014988(void); /* ? */
s32 func_800149C0(void); /* ? */
s32 func_80014A28(void); /* ? */
s32 func_80014A6C(void);
s32 _remove_ChgclrPAD(void); /* ? */
s32 func_80014AEC(s32);
s32 func_80014B00(s32);
void bzero(s32, s32);
s32 BZERO_OBJ_28(void); /* ? */
s32 func_80014B4C(s32);
s32 memchr(s32, s32, s32);
s32 MEMCHR_OBJ_20(s32, s32, s32); /* ? */
s32 MEMCHR_OBJ_48(void); /* ? */
s32 memcpy(s32, s32, s32); /* ? */
void memmove(s32, s32, s32);
s32 MEMMOVE_OBJ_64(void); /* ? */
void memset(s32, s32, s32);
s32 MEMSET_OBJ_28(void); /* ? */
void _putchar(s32);
s32 PUTCHAR_OBJ_40(void); /* ? */
s32 PUTCHAR_OBJ_9C(void); /* ? */
s32 _putchar_flash(void); /* ? */
s32 putchar(s32); /* ? */
s32 PUTCHAR_OBJ_178(void); /* ? */
s32 PUTCHAR_OBJ_1D4(void); /* ? */
s32 func_80014F10(void);
void strcat(s32, s32);
s32 STRCAT_OBJ_8C(void); /* ? */
s32 func_80014FF0(s32, s32);
s32 strcmp(s32, s32);
s32 STRCMP_OBJ_5C(void); /* ? */
void strcpy(s32, s32);
s32 func_800150F0(s32);
s32 strncmp(s32, s32, s32);
s32 STRNCMP_OBJ_78(void); /* ? */
s32 printf(s32, ...); /* ? */
s32 prnt(s32, s32, s32); /* ? */
s32 PRNT_OBJ_50(void); /* ? */
s32 PRNT_OBJ_7C(void); /* ? */
s32 PRNT_OBJ_AC(void); /* ? */
s32 PRNT_OBJ_BC(void); /* ? */
s32 PRNT_OBJ_C4(void); /* ? */
s32 PRNT_OBJ_E0(void); /* ? */
s32 PRNT_OBJ_E8(void); /* ? */
s32 PRNT_OBJ_F0(void); /* ? */
s32 PRNT_OBJ_168(void); /* ? */
s32 PRNT_OBJ_178(void); /* ? */
s32 PRNT_OBJ_180(void); /* ? */
s32 PRNT_OBJ_1DC(void); /* ? */
s32 PRNT_OBJ_1E4(void); /* ? */
s32 PRNT_OBJ_1EC(void); /* ? */
s32 PRNT_OBJ_1F4(void); /* ? */
s32 PRNT_OBJ_210(void); /* ? */
s32 PRNT_OBJ_214(s32); /* ? */
s32 PRNT_OBJ_244(s32); /* ? */
s32 PRNT_OBJ_258(void); /* ? */
s32 PRNT_OBJ_294(void); /* ? */
s32 PRNT_OBJ_298(s32); /* ? */
s32 PRNT_OBJ_2CC(void); /* ? */
s32 PRNT_OBJ_2DC(void); /* ? */
s32 PRNT_OBJ_334(void); /* ? */
s32 PRNT_OBJ_33C(void); /* ? */
s32 PRNT_OBJ_340(s32); /* ? */
s32 PRNT_OBJ_374(void); /* ? */
s32 PRNT_OBJ_380(void); /* ? */
s32 PRNT_OBJ_3B4(void); /* ? */
s32 PRNT_OBJ_3C8(void); /* ? */
s32 PRNT_OBJ_3CC(s32, s32); /* ? */
s32 PRNT_OBJ_46C(void); /* ? */
s32 PRNT_OBJ_58C(void); /* ? */
s32 PRNT_OBJ_630(void); /* ? */
s32 PRNT_OBJ_644(void); /* ? */
s32 PRNT_OBJ_65C(void); /* ? */
s32 PRNT_OBJ_664(void); /* ? */
void sprintf(s32, s32, ...);
s32 SPRINTF_OBJ_90(s32); /* ? */
s32 SPRINTF_OBJ_1BC(s32, s32); /* ? */
s32 SPRINTF_OBJ_258(s32, s32); /* ? */
s32 SPRINTF_OBJ_29C(void); /* ? */
s32 SPRINTF_OBJ_2C0(void); /* ? */
s32 SPRINTF_OBJ_2CC(void); /* ? */
s32 SPRINTF_OBJ_2D8(void); /* ? */
s32 SPRINTF_OBJ_2E4(void); /* ? */
s32 SPRINTF_OBJ_304(void); /* ? */
s32 SPRINTF_OBJ_35C(void); /* ? */
s32 SPRINTF_OBJ_390(s32); /* ? */
s32 SPRINTF_OBJ_47C(void); /* ? */
s32 SPRINTF_OBJ_57C(void); /* ? */
s32 SPRINTF_OBJ_590(s32, s32, s32); /* ? */
s32 SPRINTF_OBJ_59C(void); /* ? */
s32 SPRINTF_OBJ_5A4(s32, s32, s32, s32); /* ? */
s32 SPRINTF_OBJ_6A8(void); /* ? */
s32 SPRINTF_OBJ_6C8(void); /* ? */
s32 SPRINTF_OBJ_754(void); /* ? */
s32 SPRINTF_OBJ_788(s32, s32); /* ? */
s32 SPRINTF_OBJ_7A0(void); /* ? */
s32 SPRINTF_OBJ_82C(void); /* ? */
void puts(s32);
s32 PUTS_OBJ_28(void); /* ? */
s32 func_80016170(s32);
s32 exit(void);
s32 func_800161BC(void);
void func_800161C8(void);
void func_800161D4(s32, s32);
s32 func_8001626C(s32);
s32 func_800163E4(void); /* ? */
void func_800164BC(void);
s32 func_8001668C(s32, s32); /* ? */
s32 func_800167D4(void); /* ? */
s32 func_80016874(void); /* ? */
void func_800168EC(s32, s32);
void func_80016910(void);
s32 func_80016940(void);
s32 func_80016970(void);
void func_800169A0(s32);
s32 func_800169D4(void); /* ? */
s32 func_80016A04(void);
s32 func_80016A14(s32);
s32 func_80016A2C(void); /* ? */
s32 func_80016A98(s32, s32); /* ? */
void func_80016AC4(s32, s32);
s32 func_80016AF4(void);
s32 func_80016B4C(void); /* ? */
s32 func_80016CCC(s32, s32); /* ? */
void func_80016D78(s32, s32);
s32 func_80016DA0(void);
void func_80016DEC(s32);
s32 func_80016E00(void);
void func_80016E1C(s32, s32, s32, s32);
void func_80016F38(s32, s32);
void func_80017158(s32, s32, s32, s32);
s32 func_800171CC(s32, s32, s32, s32); /* ? */
s32 func_80017304(void);
s32 GsSetDrawBuffOffset(void); /* ? */
s32 GS_0022_OBJ_F4(void); /* ? */
void GsSetDrawBuffClip(void);
void GsSwapDispBuff(void);
void GsDefDispBuff(s32, s32, s32, s32);
s32 GS_103_OBJ_78(void); /* ? */
void func_800175F4(void);
s32 rsin(s32);
s32 GEO_00_OBJ_2C(void); /* ? */
s32 sin_1(s32);
s32 GEO_00_OBJ_C4(void); /* ? */
s32 rcos(s32);
s32 GEO_01_OBJ_98(void); /* ? */
void func_800177B4(void);
s32 SquareRoot0(void);
void MulMatrix0(s32, s32, s32);
void CompMatrix(s32, s32, s32);
void SetFarColor(s32, s32, s32);
s32 func_80017B5C(s32, s32); /* ? */
void func_80017B7C(void);
s32 func_80017B8C(void); /* ? */
void func_80017BC0(void);
s32 func_80017C6C(s32, s32, s32); /* ? */
s32 func_80017CBC(s32);
void func_80017CE4(s32);
s32 Afirmar(s32);
void func_80017D3C(s32);
s32 func_80017D80(s32);
s32 CargarArchivoEntero(s32, s32);
void ReproducirSTR(s32, s32);
void PantallasLegales(void);
void func_80018218(void);
void func_800182A8(void);
s32 func_80018408(void);
void func_80018488(s32);
void func_800185A8(s32, s32);
void CargarINO(s32, s32);
void ArchivoIniciar(s32);
void ArchivoCerrar(s32, s32);
void ArchivoAbrir(s32, s32, s32);
s32 func_800188C4(s32, s32);
s32 func_800189A4(s32);
void ArchivoLeer(s32, s32, s32);
void LeerLetraINO(s32);
void func_80018C8C(void);
void func_80018CB8(s32, s32);
void DibujarTexto(s32, s32);
void func_800190C0(void);
s32 func_800191D8(s32, s32); /* ? */
s32 func_80019234(s32);
void func_80019288(void);
s32 func_80019374(s32, s32); /* ? */
s32 func_800193F8(s32, s32, s32); /* ? */
void func_80019464(s32);
void func_8001951C(s32, s32);
s32 func_80019738(void); /* ? */
void func_800197E4(void);
void func_8001981C(void);
void func_80019C04(void);
void func_80019CC4(void);
void func_80019D18(void);
void func_80019D80(void);
void func_80019FBC(s32, s32, s32);
void func_8001A108(s32, s32, s32);
void func_8001A228(s32, s32);
void func_8001A4C0(s32);
void func_8001A620(s32, s32, s32);
void func_8001A668(s32, s32, s32);
s32 func_8001A754(s32, s32, s32, s32);
s32 func_8001ADD8(s32, s32, s32, s32);
void HerramientaConvertirTEX(s32);
s32 func_8001B000(s32); /* ? */
s32 func_8001B0C8(s32);
void func_8001B494(void);
void RegistrarTextura(s32);
s32 TexturaPorIndice(s32);
void func_8001B5F8(s32);
s32 func_8001B600(s32);
s32 func_8001B698(s32);
s32 func_8001B9C0(s32, s32);
void HerramientaConvertirPIC(s32);
s32 func_8001BE8C(s32, s32, s32, s32);
s32 func_8001BF8C(s32, s32, s32, s32);
s32 func_8001C004(s32, s32, s32, s32);
s32 func_8001C0D0(s32, s32, s32);
s32 func_8001C180(s32);
s32 func_8001C1D4(s32, s32);
s32 func_8001C280(s32, s32);
s32 func_8001C2D0(s32, s32, s32, s32);
s32 func_8001C304(s32, s32);
s32 func_8001C33C(s32, s32);
s32 func_8001C390(s32, s32, s32, s32);
s32 func_8001C3C4(s32);
void func_8001C404(s32, s32, s32);
void func_8001C45C(s32);
void func_8001C794(void);
void LeerNodoModelo(s32, s32, s32);
void func_8001CB4C(s32, s32, s32, s32);
void LeerModelosINO(s32, s32);
void HerramientaArmarModelos(s32, s32);
void LeerCuadriculaINO(s32);
void HerramientaArmarCuadricula(s32, s32);
void func_8001D518(void);
void func_8001D554(void);
void func_8001D5C0(s32);
void func_8001D778(void);
void func_8001D8EC(s32, s32);
void func_8001DF6C(void);
s32 func_8001E040(void); /* ? */
s32 func_8001E06C(s32, s32);
s32 func_8001E164(s32);
void func_8001E230(s32);
void func_8001E2DC(s32, s32);
void MatrizDesdeAngulos(s32, s32, s32, s32);
s32 func_8001E588(s32); /* ? */
void func_8001E7A8(s32, s32, s32, s32);
void func_8001E8F4(s32);
void func_8001E998(s32);
void func_8001E9DC(void);
s32 CrearParticula(s32, s32, s32, s32);
s32 func_8001ED9C(void);
s32 func_8001EDE4(s32); /* ? */
void func_8001F23C(void);
void func_8001F300(void);
void func_8001F334(void);
void func_8001F360(s32);
void func_8001F41C(s32);
void LeerParticulasINO(s32);
void func_8001F518(void);
void func_8001F524(s32);
void func_8001F6C8(s32);
void func_8001FA3C(s32, s32, s32, s32);
s32 func_8001FC5C(s32);
void func_8001FCF4(s32, s32);
void func_8001FD28(s32, s32);
void func_8001FD50(s32, s32, s32);
s32 func_80020294(s32, s32);
void func_800204F0(s32, s32, s32);
s32 func_800206E0(void); /* ? */
void func_800206E8(void);
void func_800206F0(void);
void func_80020764(s32);
s32 func_800207AC(s32, s32, s32);
void func_80020818(s32, s32);
s32 BitDeZona(s32);
void DibujarCeldasVisibles(s32, s32);
void ActivarObjetosCercanos(void);
void func_80021120(s32, s32);
void func_80021190(void);
s32 func_800211D4(void); /* ? */
void func_800212D4(void);
void func_800213A0(void);
void func_8002153C(void);
void func_800217D0(void);
void func_800218D4(void);
void func_800219C8(void);
void func_800219F8(void);
void func_80021A30(void);
void func_80021A94(s32, s32, s32, s32);
void func_80021B4C(void);
s32 func_80021C3C(void);
void func_80021C48(s32);
s32 func_80021CE4(s32);
s32 func_80021D44(s32, s32, s32);
void func_80021E54(s32, s32, s32, s32);
void func_80021F70(s32, s32, s32);
void func_8002205C(s32, s32, s32);
void func_80022104(s32, s32, s32);
s32 func_8002218C(s32, s32, s32);
s32 func_800221A8(s32, s32, s32, s32);
s32 func_800221FC(s32, s32, s32, s32);
s32 func_8002225C(s32, s32, s32, s32);
void func_80022298(s32, s32, s32);
s32 func_80022310(s32, s32, s32, s32); /* ? */
s32 func_800223E8(s32);
s32 func_8002244C(s32);
void func_800224B8(s32);
void func_80022528(void);
void func_80022564(void);
void func_80022614(s32);
void func_80022918(s32);
s32 func_80022BCC(s32); /* ? */
s32 func_80022D4C(s32); /* ? */
void func_80022E58(void);
s32 func_80022EF4(s32);
void ActualizarBarraVida(void);
s32 func_80022FD8(s32, s32); /* ? */
void func_8002303C(void);
s32 func_8002367C(s32); /* ? */
void func_80023AEC(void);
s32 func_80023B3C(s32); /* ? */
s32 func_80023E3C(s32); /* ? */
void func_80023FD4(s32);
s32 caseD_1(void); /* ? */
s32 caseD_0(void); /* ? */
void func_80024294(void);
void func_80024300(void);
void LeerSpritesINO(s32);
void func_80024444(void);
void func_80024450(s32, s32);
void CargarWRLDDATA(s32);
void CrearObjetoMundo(s32);
void func_800249B8(void);
s32 func_800249CC(s32, s32); /* ? */
void func_80024A48(s32);
void CrearRecogible(s32);
s32 func_80024DE4(void); /* ? */
s32 func_80024DEC(void); /* ? */
s32 func_80024DF4(void); /* ? */
s32 func_80024DFC(s32); /* ? */
s32 func_80024F6C(void); /* ? */
s32 func_80024F74(void); /* ? */
s32 thunk_FUN_8004866c(s32); /* ? */
s32 func_80024F84(void); /* ? */
s32 func_80024F8C(s32); /* ? */
s32 func_80024FF4(s32); /* ? */
void thunk_FUN_8001e588(s32);
s32 func_8002505C(void); /* ? */
s32 func_80025064(void); /* ? */
s32 func_8002506C(s32, s32, s32);
void func_80025258(s32);
s32 func_800252A0(s32, s32, s32, s32);
s32 func_800256E0(void);
s32 func_8002579C(void); /* ? */
void func_800257A4(void);
void func_800257F4(void);
void func_80025964(void);
s32 func_800259A8(void); /* ? */
s32 func_80025A10(void); /* ? */
void func_80025BA0(s32);
s32 func_80025C90(s32); /* ? */
void func_80025DA8(void);
s32 func_80025DD4(void); /* ? */
void PadStartCom(void);
s32 PadStopCom(void); /* ? */
s32 func_80025EF8(s32);
s32 func_8002622C(s32, s32);
s32 func_8002643C(s32, s32);
s32 func_800266B4(void);
void func_80026744(void);
s32 func_80026778(s32); /* ? */
s32 func_80026820(s32); /* ? */
s32 func_80026C18(s32); /* ? */
s32 func_80026C34(s32); /* ? */
s32 func_80026CFC(s32); /* ? */
s32 func_80026D50(s32); /* ? */
void func_80026DB0(s32);
s32 func_80026DC4(s32, s32); /* ? */
s32 func_80026DE4(s32, s32); /* ? */
s32 func_80026E04(s32, s32); /* ? */
s32 func_80026E24(s32); /* ? */
s32 func_80026E3C(s32, s32, s32); /* ? */
void func_80026E48(s32);
s32 func_80026ECC(s32);
s32 func_8002713C(s32);
void func_80027174(s32, s32);
s32 func_80027248(s32, s32);
s32 func_800272B0(s32, s32, s32); /* ? */
void func_80027348(s32, s32);
s32 func_80027368(s32); /* ? */
s32 func_800273B0(s32); /* ? */
s32 func_80027488(s32); /* ? */
s32 func_80027534(s32); /* ? */
s32 func_800275F8(s32); /* ? */
void func_80027998(void);
s32 func_800279B8(s32);
s32 func_80027A04(void);
s32 func_80027AD0(s32, s32, s32);
s32 func_80027BC8(s32, s32, s32); /* ? */
s32 func_80027C9C(s32, s32, s32); /* ? */
s32 func_80027D44(s32, s32);
s32 func_80027D7C(s32); /* ? */
s32 func_80027DF0(s32); /* ? */
s32 func_80027F08(s32); /* ? */
s32 func_80027F4C(s32, s32); /* ? */
s32 func_8002805C(s32); /* ? */
s32 func_800282D8(s32); /* ? */
s32 func_80028354(s32); /* ? */
void func_800283C4(s32, s32);
void func_800285FC(s32);
s32 func_8002886C(s32); /* ? */
s32 func_80028C54(s32); /* ? */
void func_80028D0C(void);
s32 func_80028D40(s32); /* ? */
void func_8002908C(s32);
s32 func_800290AC(void);
s32 func_8002914C(s32, s32, s32); /* ? */
s32 func_80029214(s32, s32, s32);
s32 func_800294F0(s32);
void func_80029518(s32);
void func_80029530(s32, s32);
void StSetRing(s32, s32);
s32 CdGetToc(s32);
s32 CdGetToc2(s32, s32);
s32 TOC_OBJ_220(void); /* ? */
s32 func_800297CC(void);
s32 func_80029808(void); /* ? */
s32 func_80029830(void); /* ? */
s32 func_80029858(void); /* ? */
void func_8002988C(void);
s32 func_8002991C(void);
s32 func_8002992C(void);
s32 func_8002993C(void);
s32 func_80029948(s32); /* ? */
void func_800299B4(void);
void func_800299D4(s32);
s32 func_800299E8(s32); /* ? */
s32 func_80029A1C(s32);
s32 func_80029A50(s32, s32);
s32 func_80029A70(s32, s32);
s32 func_80029A90(s32);
s32 func_80029AA4(s32);
s32 func_80029AB8(s32, s32, s32);
void func_80029BF4(s32, s32);
s32 func_80029D28(s32, s32, s32);
s32 CdMix(s32); /* ? */
void CdGetSector(s32, s32);
void func_80029EB4(s32, s32);
s32 func_80029ED4(s32);
void func_80029EF8(s32);
void func_80029F18(s32, s32);
s32 CdPosToInt(s32);
s32 func_8002A09C(void);
s32 func_8002A5F8(void); /* ? */
s32 func_8002A6D0(s32, s32);
s32 func_8002A950(s32, s32);
s32 func_8002AC18(s32, s32, s32, s32);
void func_8002B024(s32);
void func_8002B0AC(void);
s32 func_8002B180(void);
void func_8002B270(void);
s32 func_8002B2BC(void);
void func_8002B49C(s32);
s32 CD_getsector(s32, s32);
s32 func_8002B704(s32, s32);
s32 func_8002B7F0(s32, s32);
s32 func_8002B810(void);
s32 func_8002BAD4(s32, s32);
s32 func_8002BB78(s32);
s32 func_8002BE14(s32, s32, s32);
s32 func_8002BE88(s32, s32);
s32 func_8002C160(void); /* ? */
s32 CDR_1_OBJ_34(s32, s32); /* ? */
s32 CDR_1_OBJ_D4(void); /* ? */
s32 CDR_1_OBJ_19C(void); /* ? */
s32 CDR_1_OBJ_2A8(void); /* ? */
s32 CDR_1_OBJ_378(s32);
s32 CDR_1_OBJ_548(void); /* ? */
s32 CdReadBreak(void); /* ? */
s32 CDR_1_OBJ_634(void); /* ? */
s32 CDR_1_OBJ_6EC(void); /* ? */
s32 CdRead(s32, s32, s32);
s32 CDR_1_OBJ_77C(void); /* ? */
s32 CDR_1_OBJ_7E4(void); /* ? */
s32 CDR_1_OBJ_7F0(void); /* ? */
s32 CdReadSync(s32, s32);
s32 CDR_1_OBJ_934(void); /* ? */
s32 func_8002CB00(void); /* ? */
s32 func_8002CB2C(s32);
s32 func_8002CBB0(s32, s32); /* ? */
s32 func_8002CD3C(void); /* ? */
void func_8002CEB4(void);
s32 func_8002CF28(s32, s32, s32);
void StClearRing(void);
void func_8002D170(void);
s32 data_ready_callback(void); /* ? */
s32 StGetBackloc(s32); /* ? */
s32 C_004_OBJ_D4(void); /* ? */
void StSetStream(s32, s32, s32, s32);
void StFreeRing(s32);
void init_ring_status(s32, s32);
s32 StGetNext(s32, s32);
void func_8002D520(s32, s32, s32);
void func_8002D540(s32, s32, s32);
void func_8002D56C(s32, s32, s32, s32);
s32 func_8002D714(void); /* ? */
s32 func_8002E030(s32); /* ? */
s32 func_8002E0F4(s32, s32); /* ? */
s32 func_8002E0FC(s32, s32); /* ? */
s32 thunk_FUN_8004866c_8002E214(s32); /* ? */
s32 func_8002E21C(s32); /* ? */
s32 func_8002E51C(s32); /* ? */
void func_8002EC1C(void);
s32 func_8002ECFC(s32);
void func_8002ED30(s32);
void func_8002ED4C(s32);
void func_8002EDC8(s32);
void func_8002EF8C(s32);
s32 func_8002EFD0(s32);
void LeerMAO(s32);
void CargarANI(s32, s32, s32, s32);
void func_8002F298(void);
void func_8002F524(void);
void func_8002F780(void);
void func_8002F9A0(void);
void func_8002FBFC(void);
void func_8002FE64(void);
void func_8002FF1C(void);
void func_8002FFB8(s32);
s32 func_80030068(s32);
void func_800300C4(void);
void func_8003012C(void);
s32 func_8003015C(void);
s32 func_8003018C(s32); /* ? */
s32 func_8003019C(void); /* ? */
s32 func_80030208(s32); /* ? */
void func_80030E64(void);
void func_80030EC8(void);
void func_80030F18(s32);
s32 func_80031000(void); /* ? */
s32 DanoPorEnemigo(s32, s32); /* ? */
void func_800313E4(void);
void func_80031494(void);
s32 func_80031538(s32); /* ? */
s32 func_80031698(s32); /* ? */
s32 func_800318D4(void); /* ? */
void func_800318F4(s32);
void func_800325AC(s32, s32, s32);
void func_80032B98(s32, s32);
void func_80032F50(s32);
void func_80032F90(s32, s32);
void FisicaObjeto(s32, s32);
void func_80033AD8(s32);
void func_80033B1C(s32, s32, s32);
void func_80033EC8(s32, s32, s32, s32);
void DanoPorSuelo(s32, s32, s32, s32);
s32 func_80034710(s32); /* ? */
s32 func_80034770(s32); /* ? */
s32 func_8003477C(s32); /* ? */
s32 func_800349F0(s32); /* ? */
s32 func_80034F84(s32, s32);
void func_80034FD0(s32, s32);
s32 func_80035098(void); /* ? */
void func_800350A4(s32);
s32 func_800350FC(s32);
s32 func_80035190(s32); /* ? */
s32 func_80035314(s32); /* ? */
void func_80036250(void);
void func_8003630C(void);
void func_80036410(s32, s32, s32, s32);
void func_80036524(s32, s32, s32, s32);
s32 func_800365F0(s32, s32);
s32 func_80036880(s32, s32);
s32 func_80036D58(s32, s32, s32, s32);
s32 func_80037268(void); /* ? */
s32 func_80037278(s32, s32); /* ? */
s32 func_80037468(s32, s32); /* ? */
s32 func_80037738(s32, s32); /* ? */
s32 func_8003795C(s32, s32); /* ? */
s32 func_80037A18(s32); /* ? */
s32 func_80037DBC(s32, s32); /* ? */
s32 func_80037DE0(s32); /* ? */
s32 func_80037EE0(s32, s32, s32); /* ? */
s32 func_80037F24(s32); /* ? */
s32 func_80038154(s32); /* ? */
s32 func_8003821C(s32, s32); /* ? */
s32 func_80038318(s32); /* ? */
s32 func_80038918(s32); /* ? */
s32 func_800389DC(s32); /* ? */
s32 func_80038AF4(s32); /* ? */
s32 func_80038C38(s32); /* ? */
s32 func_80038D38(s32); /* ? */
s32 func_80038E50(s32); /* ? */
s32 func_80038EB4(s32, s32); /* ? */
s32 func_80038F08(s32, s32); /* ? */
s32 func_80038FAC(s32, s32); /* ? */
s32 func_80039030(s32); /* ? */
s32 func_8003909C(s32, s32); /* ? */
s32 func_80039104(s32, s32); /* ? */
s32 func_80039330(s32); /* ? */
s32 func_80039350(s32); /* ? */
s32 func_80039670(s32, s32); /* ? */
s32 func_8003973C(s32, s32, s32); /* ? */
s32 func_80039788(s32); /* ? */
s32 func_8003980C(s32); /* ? */
void func_800399A0(s32, s32);
void func_800399E8(s32, s32);
void func_80039A34(s32, s32, s32, s32);
void func_80039A70(s32, s32, s32, s32);
void func_80039AF4(s32, s32);
void func_80039B1C(s32, s32, s32, s32);
void func_80039BA0(s32, s32);
s32 func_80039BC8(s32, s32);
s32 func_80039D4C(s32, s32);
s32 func_80039DD0(s32, s32);
s32 func_80039EBC(s32, s32);
s32 func_80039FA4(s32, s32);
s32 func_8003A070(s32, s32);
s32 func_8003A17C(s32, s32);
s32 func_8003A250(s32);
s32 func_8003A258(s32);
s32 func_8003A260(s32);
s32 PuntoEnTriangulo(s32, s32, s32);
s32 func_8003A46C(s32, s32, s32);
s32 func_8003A524(s32, s32);
s32 func_8003A750(s32, s32);
s32 func_8003A94C(s32, s32, s32, s32);
s32 CeldaDePosicion(s32, s32);
s32 func_8003AE84(void);
s32 func_8003AF48(s32);
s32 func_8003AF9C(s32, s32, s32, s32);
void func_8003B38C(s32, s32, s32);
s32 func_8003B4DC(s32, s32); /* ? */
s32 func_8003B53C(s32, s32, s32); /* ? */
s32 func_8003B57C(s32); /* ? */
void func_8003B894(s32, s32, s32, s32);
s32 func_8003BB28(s32); /* ? */
s32 func_8003BBA8(s32); /* ? */
s32 func_8003BC04(s32); /* ? */
s32 func_8003BCB4(s32); /* ? */
s32 func_8003BDCC(s32); /* ? */
s32 thunk_FUN_8003be38(s32); /* ? */
s32 func_8003BE38(s32); /* ? */
s32 func_8003BFC4(s32, s32); /* ? */
s32 func_8003BFEC(s32); /* ? */
void func_8003C1E8(s32, s32, s32, s32);
s32 func_8003C528(s32); /* ? */
void func_8003C678(s32, s32, s32, s32);
s32 func_8003C8F8(s32, s32, s32); /* ? */
s32 func_8003C9DC(s32); /* ? */
s32 func_8003CE04(s32); /* ? */
s32 func_8003CEF0(s32, s32); /* ? */
s32 func_8003CF60(s32, s32); /* ? */
s32 func_8003D00C(s32); /* ? */
s32 func_8003D094(s32); /* ? */
s32 func_8003D158(s32, s32); /* ? */
s32 func_8003D160(s32, s32); /* ? */
void func_8003D278(s32);
s32 thunk_FUN_8004866c_8003D470(s32); /* ? */
s32 func_8003D478(s32); /* ? */
s32 func_8003D5F4(s32); /* ? */
void func_8003D7E8(void);
void CargarSonidoNivel(s32);
void func_8003D9D0(void);
void thunk_FUN_80042924(s32);
s32 TocarSonido(s32, s32, s32, s32);
void func_8003DC08(void);
void func_8003DC48(void);
s32 func_8003DD44(s32); /* ? */
s32 func_8003DD74(s32); /* ? */
s32 func_8003DD84(void); /* ? */
void func_8003DDA0(s32, s32);
s32 func_8003DDFC(void); /* ? */
void func_8003DE68(s32);
void func_8003DEE8(void);
void func_8003DFF0(void);
s32 func_8003E060(void);
void func_8003E0B4(void);
void func_8003E0C4(s32, s32);
void func_8003E284(void);
void func_8003E2AC(void);
void func_8003E2D4(s32);
s32 func_8003E554(void); /* ? */
void func_8003E610(s32, s32, s32, s32);
void func_8003E890(s32, s32, s32, s32);
void func_8003E914(s32, s32, s32);
s32 func_8003E958(s32, s32);
s32 func_8003E9FC(s32, s32); /* ? */
s32 func_8003EA38(s32); /* ? */
void func_8003EA90(void);
void func_8003EAF8(s32);
void _SpuInit(s32);
void SpuStart(void);
void SsUtReverbOff(void);
s32 _spu_gcSPU(void); /* ? */
s32 S_M_INT_OBJ_54(s32, s32, s32, s32); /* ? */
s32 S_M_INT_OBJ_C4(void); /* ? */
s32 S_M_INT_OBJ_270(void); /* ? */
void SpuInitMalloc(s32, s32);
s32 S_M_INIT_OBJ_4C(void); /* ? */
s32 _SpuIsInAllocateArea(void); /* ? */
s32 S_M_UTIL_OBJ_2C(s32, s32, s32, s32); /* ? */
s32 S_M_UTIL_OBJ_78(void); /* ? */
s32 _SpuIsInAllocateArea_(s32);
s32 S_M_UTIL_OBJ_B8(s32, s32, s32, s32); /* ? */
s32 S_M_UTIL_OBJ_104(void); /* ? */
s32 SpuMalloc(s32);
s32 S_M_M_OBJ_54(void); /* ? */
s32 S_M_M_OBJ_12C(void); /* ? */
s32 S_M_M_OBJ_2A8(void); /* ? */
void SpuFree(s32);
s32 S_M_F_OBJ_64(void); /* ? */
s32 _SpuSetAnyVoice(s32, s32, s32, s32); /* ? */
s32 S_SAV_OBJ_130(void); /* ? */
s32 S_SAV_OBJ_200(void); /* ? */
s32 S_SAV_OBJ_2A4(void); /* ? */
s32 S_SAV_OBJ_2AC(void); /* ? */
s32 S_SAV_OBJ_2B4(void); /* ? */
s32 func_8003F728(s32, s32); /* ? */
void SpuSetNoiseClock(s32);
void func_8003F7A8(s32, s32);
void SpuClearReverbWorkArea(s32);
s32 S_CRWA_OBJ_9C(s32, s32, s32, s32); /* ? */
s32 S_CRWA_OBJ_170(void); /* ? */
void SpuSetKey(s32, s32);
s32 S_SK_OBJ_1AC(void); /* ? */
s32 S_SK_OBJ_1B4(void); /* ? */
s32 SpuGetKeyStatus(s32);
s32 S_GKS_OBJ_2C(s32, s32); /* ? */
s32 S_GKS_OBJ_88(void); /* ? */
void SpuRead(s32, s32, s32, s32);
s32 SpuSetTransferStartAddr(s32);
s32 S_STSA_OBJ_4C(void); /* ? */
void SpuSetTransferMode(s32);
s32 S_STM_OBJ_1C(s32); /* ? */
s32 SpuIsTransferCompleted(s32);
s32 S_ITC_OBJ_88(void); /* ? */
s32 S_ITC_OBJ_90(void); /* ? */
void func_8003FD68(s32);
s32 func_8003FD90(void);
void SpuSetCommonAttr(s32);
s32 S_SCA_OBJ_58(s32, s32, s32); /* ? */
s32 S_SCA_OBJ_60(s32, s32, s32); /* ? */
s32 S_SCA_OBJ_68(s32, s32, s32); /* ? */
s32 S_SCA_OBJ_70(s32, s32, s32); /* ? */
s32 S_SCA_OBJ_78(s32, s32, s32); /* ? */
s32 S_SCA_OBJ_80(s32, s32, s32); /* ? */
s32 S_SCA_OBJ_88(s32, s32, s32); /* ? */
s32 S_SCA_OBJ_90(s32); /* ? */
s32 S_SCA_OBJ_98(s32, s32, s32); /* ? */
s32 S_SCA_OBJ_118(s32); /* ? */
s32 S_SCA_OBJ_120(s32); /* ? */
s32 S_SCA_OBJ_128(s32); /* ? */
s32 S_SCA_OBJ_130(s32); /* ? */
s32 S_SCA_OBJ_138(s32); /* ? */
s32 S_SCA_OBJ_140(s32); /* ? */
s32 S_SCA_OBJ_148(s32); /* ? */
s32 S_SCA_OBJ_150(s32); /* ? */
s32 S_SCA_OBJ_158(s32, s32); /* ? */
s32 S_SCA_OBJ_274(s32); /* ? */
s32 S_SCA_OBJ_2C8(s32); /* ? */
s32 S_SCA_OBJ_31C(s32); /* ? */
s32 S_SCA_OBJ_370(void); /* ? */
void SpuGetCommonAttr(s32);
s32 S_GCA_OBJ_E8(s32, s32, s32, s32); /* ? */
s32 S_GCA_OBJ_EC(s32, s32, s32, s32); /* ? */
s32 S_GCA_OBJ_1BC(void); /* ? */
s32 S_GCA_OBJ_1C0(s32, s32, s32, s32); /* ? */
s32 S_GCA_OBJ_1E0(s32, s32, s32); /* ? */
s32 S_GCA_OBJ_200(s32, s32, s32); /* ? */
s32 S_GCA_OBJ_260(s32); /* ? */
s32 S_GCA_OBJ_28C(s32); /* ? */
s32 S_GCA_OBJ_2D0(s32); /* ? */
s32 S_GCA_OBJ_2FC(void); /* ? */
s32 _spu_note2pitch(s32, s32, s32, s32);
s32 S_N2P_OBJ_C8(s32, s32); /* ? */
s32 _spu_pitch2note(s32, s32, s32); /* ? */
s32 S_N2P_OBJ_158(s32, s32, s32); /* ? */
s32 S_N2P_OBJ_1C0(s32, s32); /* ? */
void SpuSetVoiceAttr(s32);
s32 S_SVA_OBJ_13C(void); /* ? */
s32 S_SVA_OBJ_144(void); /* ? */
s32 S_SVA_OBJ_14C(void); /* ? */
s32 S_SVA_OBJ_154(void); /* ? */
s32 S_SVA_OBJ_15C(void); /* ? */
s32 S_SVA_OBJ_164(void); /* ? */
s32 S_SVA_OBJ_16C(void); /* ? */
s32 S_SVA_OBJ_170(s32); /* ? */
s32 S_SVA_OBJ_1A0(s32, s32); /* ? */
s32 S_SVA_OBJ_21C(void); /* ? */
s32 S_SVA_OBJ_224(void); /* ? */
s32 S_SVA_OBJ_22C(void); /* ? */
s32 S_SVA_OBJ_234(void); /* ? */
s32 S_SVA_OBJ_23C(void); /* ? */
s32 S_SVA_OBJ_244(void); /* ? */
s32 S_SVA_OBJ_24C(void); /* ? */
s32 S_SVA_OBJ_250(s32); /* ? */
s32 S_SVA_OBJ_280(s32, s32); /* ? */
s32 S_SVA_OBJ_480(s32, s32, s32); /* ? */
s32 S_SVA_OBJ_5C0(void); /* ? */
void SpuGetVoiceEnvelope(s32, s32);
void SpuSetCommonMasterVolume(s32, s32);
void _SsSndCrescendo(s32, s32);
s32 CRES_OBJ_1B8(void); /* ? */
void _SsSeqPlay(s32, s32);
s32 MIDIREAD_OBJ_DC(void); /* ? */
s32 MIDIREAD_OBJ_E0(void); /* ? */
void _SsSeqGetEof(s32, s32);
s32 MIDIREAD_OBJ_204(void); /* ? */
s32 MIDIREAD_OBJ_2D4(void); /* ? */
s32 MIDIREAD_OBJ_328(void); /* ? */
void _SsGetSeqData(s32, s32);
s32 MIDIREAD_OBJ_5F8(void); /* ? */
s32 MIDIREAD_OBJ_654(s32, s32); /* ? */
s32 MIDIREAD_OBJ_6A8(s32, s32); /* ? */
s32 MIDIREAD_OBJ_6BC(void); /* ? */
s32 MIDIREAD_OBJ_6C8(void); /* ? */
s32 _SsReadDeltaValue(s32, s32);
void _SsSndNextSep(s32, s32);
void _SsSndPause(s32, s32);
void _SsSndPlay(s32, s32);
void _SsSndReplay(s32, s32);
s32 SsSeqCalledTbyT(void); /* ? */
void SsGetSerialVol(s32, s32);
s32 SSGSV_OBJ_A4(s32); /* ? */
void _SsInit(void);
void func_80041C48(void);
void SsSetMVol(s32, s32);
void func_80041CD8(s32);
s32 func_80041F08(void); /* ? */
s32 func_80041F54(void); /* ? */
void SsUtReverbOn(void);
void func_80041FC8(s32, s32);
void SsSetSerialVol(s32, s32, s32);
void SsSetTickMode(s32);
s32 SSTICK_OBJ_4C(void); /* ? */
s32 SSTICK_OBJ_84(s32); /* ? */
s32 SSTICK_OBJ_A8(s32); /* ? */
s32 SSTICK_OBJ_C8(void); /* ? */
s32 SSTICK_OBJ_D8(void); /* ? */
s32 SSTICK_OBJ_E8(s32); /* ? */
s32 SSTICK_OBJ_100(s32); /* ? */
s32 SSTICK_OBJ_124(void); /* ? */
s32 SSTICK_OBJ_138(void); /* ? */
void _SsSndTempo(s32, s32);
s32 TEMPO_OBJ_124(s32, s32, s32, s32); /* ? */
s32 TEMPO_OBJ_130(s32, s32, s32, s32); /* ? */
s32 TEMPO_OBJ_204(void); /* ? */
void func_800425C8(s32, s32, s32, s32);
void func_80042924(s32);
void _SsVmDoAllocate(void);
s32 VM_ALOC2_OBJ_E8(s32, s32); /* ? */
void func_80042B68(void);
s32 func_80042B78(void); /* ? */
void _SsVmInit(s32);
s32 VM_INIT_OBJ_FC(void); /* ? */
s32 func_80043358(s32, s32);
s32 func_800433C0(s32, s32, s32, s32);
void vmNoiseOn(s32);
s32 VM_NO1_OBJ_1C4(void); /* ? */
s32 VM_NO1_OBJ_234(void); /* ? */
s32 VM_NO1_OBJ_2A4(void); /* ? */
s32 VM_NO1_OBJ_2CC(void); /* ? */
s32 VM_NO1_OBJ_3B0(s32, s32, s32, s32); /* ? */
s32 VM_NO1_OBJ_53C(s32, s32, s32, s32); /* ? */
void _SsVmKeyOffNow(void);
s32 VM_NOWOF_OBJ_34(s32, s32, s32); /* ? */
void _SsVmKeyOnNow(s32, s32);
s32 VM_NOWON_OBJ_1B4(s32, s32); /* ? */
s32 VM_NOWON_OBJ_224(s32, s32); /* ? */
s32 VM_NOWON_OBJ_294(s32, s32); /* ? */
s32 VM_NOWON_OBJ_2BC(s32, s32); /* ? */
s32 VM_NOWON_OBJ_3C4(s32, s32, s32); /* ? */
s32 VM_NOWON_OBJ_440(s32, s32, s32); /* ? */
void _SsVmSetSeqVol(s32, s32, s32);
s32 VM_SEQ_OBJ_324(s32, s32); /* ? */
s32 VM_SEQ_OBJ_3BC(s32, s32); /* ? */
s32 VM_SEQ_OBJ_440(s32, s32); /* ? */
s32 VM_SEQ_OBJ_470(s32, s32); /* ? */
s32 _SsVmGetSeqVol(s32, s32, s32); /* ? */
void _SsVmSeqKeyOff(s32);
s32 _SsVmVSetUp(s32, s32);
s32 VM_VSU_OBJ_B8(void); /* ? */
void SsVabClose(s32);
s32 func_800447DC(s32, s32); /* ? */
s32 func_800447E4(s32, s32, s32, s32);
s32 func_80044BD4(s32, s32, s32); /* ? */
s32 func_80044C40(s32, s32);
s32 SsVabTransBody(s32, s32);
s32 VS_VTB_OBJ_A4(void); /* ? */
void SsVabTransCompleted(s32);
s32 func_80044D64(s32); /* ? */
s32 func_80044E28(s32, s32); /* ? */
s32 func_80044E30(s32, s32); /* ? */
s32 thunk_FUN_8004866c_80044F48(s32); /* ? */
s32 IniciarEnemigoTipo15(s32); /* ? */
s32 func_80045278(s32); /* ? */
s32 func_80045974(s32); /* ? */
s32 func_80045A38(s32, s32); /* ? */
s32 func_80045A40(s32, s32); /* ? */
s32 thunk_FUN_8004866c_80045B58(s32); /* ? */
s32 func_80045B60(s32); /* ? */
s32 func_80045CF4(s32); /* ? */
s32 func_80045EE0(s32); /* ? */
s32 func_80045FA4(s32, s32); /* ? */
s32 func_80045FAC(s32, s32); /* ? */
s32 thunk_FUN_8004866c_800460C4(s32); /* ? */
s32 func_800460CC(s32); /* ? */
s32 func_80046428(s32); /* ? */
s32 func_80046B2C(void); /* ? */
s32 func_80046B50(void); /* ? */
s32 func_80046B6C(void); /* ? */
s32 func_80046B90(void); /* ? */
s32 func_80046BAC(void); /* ? */
s32 func_80046BC4(void); /* ? */
s32 func_80046C18(void); /* ? */
s32 func_80046D54(void); /* ? */
s32 func_80046D6C(void); /* ? */
s32 func_80046E0C(void); /* ? */
s32 func_80046EA4(void); /* ? */
s32 func_80046EAC(void); /* ? */
s32 func_80046EC0(void); /* ? */
s32 func_80046ED8(void); /* ? */
s32 func_80046F74(void); /* ? */
s32 func_80047010(void); /* ? */
s32 thunk_FUN_80047234(void); /* ? */
s32 func_80047058(void); /* ? */
s32 func_80047064(void); /* ? */
s32 func_800471A8(void); /* ? */
s32 func_800471CC(void); /* ? */
s32 func_800471F8(void); /* ? */
s32 func_80047234(void); /* ? */
s32 func_80047240(void); /* ? */
s32 IniciarRecogibleTipo18(s32); /* ? */
s32 func_800472D0(void); /* ? */
s32 func_800472D8(s32); /* ? */
s32 IniciarRecogibleTipo19(s32); /* ? */
s32 func_80047358(void); /* ? */
s32 func_80047360(s32); /* ? */
s32 RegistrarRecogible(s32); /* ? */
void func_80047710(void);
s32 func_800479D8(s32);
s32 func_800479E8(s32);
s32 func_80047AA4(s32);
s32 RecogibleNoTomado(s32);
s32 IniciarRecogibleTipo4(s32); /* ? */
s32 func_80047F0C(void); /* ? */
s32 func_80047F14(s32); /* ? */
s32 func_80047F24(s32); /* ? */
s32 func_80047FD0(s32); /* ? */
s32 func_80047FE0(s32); /* ? */
s32 func_80048024(void); /* ? */
s32 func_80048094(s32); /* ? */
void func_80048104(s32);
void func_80048164(s32, s32);
s32 func_80048228(s32); /* ? */
s32 func_80048374(s32, s32, s32);
void func_800483E8(s32);
void func_800483F8(s32);
void func_80048468(s32, s32);
void func_800484CC(s32, s32, s32, s32);
s32 func_8004866C(s32); /* ? */
void func_800486B8(s32, s32);
s32 func_80048710(s32, s32);
s32 func_80048754(s32, s32, s32, s32); /* ? */
s32 func_800487B0(s32, s32, s32);
s32 func_80048804(s32, s32, s32, s32); /* ? */
void func_80048900(void);
s32 func_80048908(s32, s32, s32, s32); /* ? */
void func_800489C4(s32);
void func_80048CF4(s32, s32, s32, s32);
void func_80048DC0(s32, s32, s32, s32);
s32 func_8004906C(s32, s32);
void func_80049110(s32, s32);
s32 func_80049218(s32, s32, s32); /* ? */
s32 func_800492B4(s32, s32, s32); /* ? */
s32 func_80049388(s32, s32, s32, s32); /* ? */
s32 func_8004951C(s32, s32, s32); /* ? */
s32 func_800496E4(s32, s32, s32); /* ? */
s32 func_800498F4(s32, s32, s32, s32); /* ? */
s32 func_80049A28(s32, s32, s32); /* ? */
s32 func_80049BD0(s32, s32, s32); /* ? */
s32 func_80049DE0(s32); /* ? */
s32 func_80049EA4(s32, s32); /* ? */
s32 func_80049EAC(s32, s32); /* ? */
s32 thunk_FUN_8004866c_80049FC4(s32); /* ? */
s32 func_80049FCC(s32); /* ? */
s32 func_8004A140(s32); /* ? */
s32 IniciarRecogibleTipo23(s32); /* ? */
s32 func_8004A39C(void); /* ? */
s32 func_8004A3A4(s32); /* ? */
void func_8004A3B4(s32, s32, s32);
s32 func_8004A4A8(s32); /* ? */
void func_8004AAE4(s32);
s32 func_8004AB24(s32); /* ? */
s32 func_8004ADB0(s32); /* ? */
void func_8004AEA4(void);
s32 func_8004AEAC(s32); /* ? */
s32 func_8004AF50(void);
void func_8004B14C(void);
void func_8004B21C(s32);
void func_8004B318(void);
void func_8004B320(s32);
void func_8004BDA0(void);
void func_8004C150(void);
void func_8004C224(void);
void func_8004C22C(void);
void thunk_FUN_8004aea4(void);
s32 func_8004C3A0(void);
void func_8004C480(s32);
void func_8004C514(s32);
void func_8004C5A8(s32);
void func_8004C63C(s32);
void func_8004C6D0(s32);
void func_8004C700(s32);
void func_8004C730(s32);
s32 func_8004C81C(void); /* ? */
void func_8004C824(void);
void func_8004C82C(void);
s32 func_8004CA4C(s32); /* ? */
s32 func_8004CA5C(s32); /* ? */
void func_8004CAB8(void);
s32 func_8004CB48(s32); /* ? */
s32 func_8004D0C0(s32); /* ? */
s32 func_8004DAC4(s32); /* ? */
s32 func_8004DB6C(s32, s32, s32, s32);
s32 func_8004DC10(s32, s32); /* ? */
void func_8004DC78(void);
s32 Reservar(s32, s32);
void Liberar(s32);
void func_8004E194(void);
void func_8004E238(void);
void func_8004E268(void);
s32 func_8004E2A4(s32);
s32 func_8004E2CC(s32); /* ? */
s32 func_8004E2E4(s32, s32); /* ? */
s32 func_8004E32C(s32, s32);
s32 func_8004E5D8(s32, s32); /* ? */
s32 func_8004E618(s32, s32);
void func_8004E6C0(s32, s32);
void func_8004E72C(s32);
s32 func_8004E774(s32, s32);
void func_8004E7FC(s32, s32, s32);
void func_8004E86C(s32, s32, s32);
s32 func_8004E8C4(s32, s32);
s32 func_8004EA90(s32, s32); /* ? */
s32 func_8004EAAC(s32); /* ? */
void func_8004EAE8(s32, s32, s32);
void func_8004EB04(void);
void func_8004EBD0(void);
s32 func_8004ED5C(void); /* ? */
s32 func_8004EDBC(void); /* ? */
s32 func_8004EE1C(void); /* ? */
void func_8004EE24(s32);
s32 func_8004EEF4(s32, s32); /* ? */
s32 func_8004F2BC(void); /* ? */
s32 func_8004F2D8(s32, s32, s32); /* ? */
s32 func_8004F4F0(void); /* ? */
s32 func_8004F50C(s32); /* ? */
s32 func_8004F568(s32, s32); /* ? */
s32 func_8004F834(s32, s32); /* ? */
s32 func_8004F918(s32, s32, s32); /* ? */
s32 func_8004F94C(void); /* ? */
s32 func_8004F968(s32, s32, s32); /* ? */
s32 func_8004F99C(s32, s32, s32); /* ? */
s32 func_8004F9C8(void); /* ? */
s32 func_8004F9F8(void); /* ? */
s32 func_8004FA10(void); /* ? */
void func_8004FA54(s32, s32);
void func_8004FC4C(s32);
void func_8004FD04(s32);
s32 func_8004FD34(s32); /* ? */
s32 func_80050034(s32); /* ? */
s32 func_800502DC(s32); /* ? */
s32 func_80050418(s32); /* ? */
s32 func_80050554(s32); /* ? */
s32 func_80050694(s32); /* ? */
s32 func_800507D4(s32);
s32 func_80050828(void); /* ? */
void func_800508D4(s32, s32);
s32 func_80050938(void); /* ? */
void func_800509A8(void);
void func_800509E8(s32);
void func_80050A50(s32);
s32 func_80050AB8(s32, s32, s32);
void func_80050C40(void);
s32 func_80050C84(s32, s32, s32);
s32 func_80050D3C(s32, s32, s32); /* ? */
s32 func_80050DF4(s32, s32, s32, s32); /* ? */
s32 func_80050F0C(s32, s32, s32, s32);
s32 func_80051024(s32, s32, s32, s32);
s32 func_80051284(s32);
void func_80051298(s32, s32, s32);
s32 func_800513B4(s32, s32, s32);
s32 func_800515B0(s32, s32);
void func_80051764(s32);
s32 func_80051820(s32); /* ? */
void UserFuncInit(void);
void UserFuncOpen(s32);
s32 USERFUNC_OBJ_7C(void); /* ? */
void UserFuncExecute(void);
s32 UserFuncComplete(void);
s32 func_800519E4(void); /* ? */
s32 func_800519F8(void); /* ? */
s32 func_80051A0C(void); /* ? */
s32 func_80051A20(void); /* ? */
s32 func_80051A34(void); /* ? */
s32 func_80051A48(void); /* ? */
s32 func_80051A5C(void); /* ? */
s32 func_80051A70(void); /* ? */
void func_80051A84(void);
void func_80051C60(void);
void func_80051D14(void);
s32 func_80051E1C(void);
s32 func_80051EF4(void);
s32 func_80051FCC(void);
s32 func_80052008(void);
void _card_info(void);
void _card_load(void);
void InitCARD2(void);
void StartCARD2(void);
void StopCARD2(void);
s32 _card_write(void);
s32 _card_read(void);
void _new_card(void);
s32 _card_status(void);
void _card_clear(s32);
s32 func_80052114(void); /* ? */
s32 func_80052140(void); /* ? */
s32 func_80052184(void); /* ? */
void func_800521AC(void);
void func_80052240(void);
void func_800522B0(void);
void func_800522E4(s32);
void func_80052350(void);
s32 func_80052388(void); /* ? */
s32 func_800523B4(void); /* ? */
s32 func_80052434(s32, s32, s32);
s32 func_80052578(s32);
s32 func_80052784(s32); /* ? */
s32 func_800528AC(s32); /* ? */
s32 func_80052E58(s32, s32); /* ? */
s32 func_80052E9C(void); /* ? */
s32 func_80052EA4(s32); /* ? */
s32 func_80052F6C(s32); /* ? */
s32 func_80052FC0(s32); /* ? */
s32 func_80053038(s32); /* ? */
s32 func_80053138(s32, s32); /* ? */
s32 func_80053250(s32, s32); /* ? */
s32 func_8005329C(s32); /* ? */
s32 func_800533E8(s32); /* ? */
s32 func_80053400(s32); /* ? */
s32 func_800534A0(s32); /* ? */
s32 func_800534D8(s32); /* ? */
s32 func_8005359C(s32); /* ? */
s32 func_800537C4(s32); /* ? */
s32 func_80053808(s32); /* ? */
s32 func_800538A0(s32); /* ? */
s32 func_800539D0(s32); /* ? */
void func_80053A64(s32);
s32 func_80053A98(s32);
s32 func_80053B30(s32); /* ? */
s32 func_80053B98(s32, s32, s32, s32);
s32 func_80053C74(s32); /* ? */
s32 func_80053ED8(s32); /* ? */
void func_80053F74(s32);
s32 func_80054068(s32); /* ? */
s32 func_8005473C(s32, s32); /* ? */
s32 func_800547EC(s32); /* ? */
s32 func_80054894(s32); /* ? */
s32 func_80054A58(s32); /* ? */
s32 thunk_FUN_8004866c_80054C54(s32); /* ? */
s32 func_80054C5C(s32); /* ? */
s32 func_800551FC(s32); /* ? */
s32 func_80055290(s32, s32); /* ? */
s32 func_800552C0(s32); /* ? */
s32 func_80055588(s32); /* ? */
s32 func_800555FC(s32); /* ? */
s32 func_80055614(s32); /* ? */
s32 func_80055624(s32); /* ? */
s32 func_80055634(s32); /* ? */
s32 func_800558F8(s32, s32); /* ? */
s32 func_80055998(s32); /* ? */
s32 func_80055A38(s32); /* ? */
s32 func_80055BF8(s32, s32, s32); /* ? */
s32 func_80055C08(void); /* ? */
s32 func_80055C10(s32); /* ? */
s32 func_80055CA4(void); /* ? */
s32 func_80055CAC(s32); /* ? */
s32 func_80055DEC(s32); /* ? */
s32 func_80055E04(s32); /* ? */
s32 func_80055F00(s32); /* ? */
s32 func_80055F34(s32, s32); /* ? */
s32 func_80055FC0(s32); /* ? */
s32 func_80056290(s32); /* ? */
s32 func_800563C4(s32); /* ? */
s32 func_8005655C(s32); /* ? */
s32 func_80056584(s32); /* ? */
s32 func_80056A08(void);
s32 func_80056B18(s32); /* ? */
s32 thunk_FUN_8004866c_80056C10(s32); /* ? */
s32 func_80056C18(s32, s32); /* ? */
s32 func_80056CE8(s32); /* ? */
s32 func_8005737C(s32); /* ? */
void func_800573C0(s32, s32, s32);
s32 func_80057610(s32); /* ? */
s32 func_80057800(s32); /* ? */
s32 func_8005794C(s32); /* ? */
s32 func_80057A10(s32, s32); /* ? */
s32 func_80057A18(s32, s32); /* ? */
s32 thunk_FUN_8004866c_80057B30(s32); /* ? */
s32 func_80057B38(s32); /* ? */
s32 func_80057CA0(s32); /* ? */
s32 func_80057E8C(void); /* ? */
s32 func_80057E94(s32); /* ? */
s32 func_80057F34(s32); /* ? */
s32 func_800582CC(s32); /* ? */
s32 func_8005865C(s32); /* ? */
s32 func_800589EC(s32, s32, s32); /* ? */
s32 func_80058EE4(s32, s32, s32); /* ? */
s32 func_800593E0(s32, s32, s32); /* ? */
void func_800598DC(s32, s32, s32);
s32 func_80059F2C(s32); /* ? */
s32 func_80059FB4(s32, s32); /* ? */
s32 func_80059FBC(s32); /* ? */
s32 func_8005A1EC(s32); /* ? */
s32 func_8005A360(s32); /* ? */
s32 func_8005AFC0(s32, s32); /* ? */
s32 func_8005B008(s32); /* ? */
s32 func_8005B150(s32); /* ? */
void func_8005B394(s32, s32, s32, s32);
s32 func_8005B460(s32); /* ? */
void func_8005B46C(s32, s32, s32, s32);
s32 func_8005B52C(s32); /* ? */
s32 func_8005B780(s32); /* ? */
s32 func_8005B794(s32); /* ? */
s32 func_8005B8D4(s32);
s32 func_8005B994(s32); /* ? */
void func_8005BA10(s32);
s32 func_8005BED0(s32); /* ? */
s32 func_8005C358(s32); /* ? */
s32 func_8005C8E0(s32); /* ? */
void func_8005C92C(s32);
void func_8005C940(s32);
void func_8005C964(void);
void func_8005C9D0(s32);
s32 func_8005CD98(s32);
void func_8005CE48(void);
s32 func_8005CEBC(void);
void func_8005D02C(s32);
s32 func_8005D0D0(void);
s32 func_8005D0F4(void);
s32 func_8005D164(s32);
void func_8005D1D0(void);
s32 func_8005D26C(void); /* ? */
s32 func_8005D3A0(s32);
void func_8005D3DC(void);
void func_8005D3F4(void);
void func_8005D504(void);
s32 func_8005D50C(s32, s32);
void func_8005D844(void);
s32 func_8005D8A0(s32);
void func_8005D8D0(s32);
void func_8005D9C0(s32, s32);
s32 func_8005DA50(s32, s32); /* ? */
s32 func_8005DADC(void); /* ? */
s32 func_8005DB70(void); /* ? */
s32 func_8005DC04(void);
void func_8005DC1C(s32);
void func_8005DCA0(s32);
void func_8005DCD4(s32, s32);
s32 func_8005DD50(s32, s32); /* ? */
s32 func_8005DD70(s32); /* ? */
s32 func_8005DDAC(s32); /* ? */
void func_8005DDE8(s32);
void DecDCTvlcSize2(s32);
s32 DecDCTvlc2(s32, s32, s32);
void DecDCTvlcBuild(s32);
s32 BUILD_OBJ_AC(s32); /* ? */
void func_8005E27C(s32, s32, s32);
s32 func_8005E290(s32, s32, s32, s32); /* ? */
void func_8005E2A0(void);
void func_8005E59C(void);
s32 func_8005E898(s32); /* ? */
void func_8005E9FC(s32, s32, s32, s32);
s32 func_8005EAD4(s32); /* ? */
s32 func_8005ED80(s32); /* ? */
s32 func_8005ED8C(s32); /* ? */
s32 func_80060170(s32); /* ? */
s32 func_80060274(s32); /* ? */
s32 func_80060368(s32); /* ? */
s32 func_80060558(s32);
s32 func_80060590(s32);
s32 func_800605C8(s32, s32, s32);
s32 func_800607AC(s32, s32, s32);
