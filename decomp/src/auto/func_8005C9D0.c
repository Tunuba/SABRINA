#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s16 D_800D5818;
extern s16 D_800D581A;
extern s16 D_800D581C;
extern s16 D_800D581E;
extern s16 D_800D5820;
extern s16 D_800D5822;
extern s32 D_800D5824;
extern u16 D_800D5828;
extern s32 D_800D582C;
extern s16 D_800D5830;
extern s16 D_800D5832;
extern s16 D_800D5834;
extern s16 D_800D5836;
extern s16 D_800D5838;
extern s16 D_800D583A;
extern s16 D_800D583C;
extern s16 D_800D583E;
extern s16 D_800D5840;
extern s16 D_800D5842;
extern s16 D_800D5844;
extern s16 D_800D5846;
extern s16 D_800D5848;
extern s16 D_800D584A;
extern s16 D_800D584C;
extern s16 D_800D584E;
extern s16 D_800D5850;
extern s32 D_800D5854;
extern s32 D_800D5858;
extern s32 D_800D585C;
extern s32 D_800D5860;
extern u8 D_800D5864[];
extern s16 D_800D586C;
extern s16 D_800D586E;
extern s16 D_800D5870;
extern s16 D_800D5872;
extern s8 D_800D5875;
extern u8 D_800D5878[];
extern s16 D_800D5880;
extern s16 D_800D5882;
extern s16 D_800D5884;
extern s16 D_800D5886;
extern s8 D_800D5889;
extern u8 D_8007CC7C[];
extern s32 D_8007CC80;
extern s32 D_8007CC84;
extern s32 D_8007CC88;
extern s32 D_8007CC8C;
extern s32 func_8005D26C();


void func_8005C9D0(s32 arg0) {
    s32 temp_v0_6;
    s32 var_t0;
    s32 var_t0_2;
    s8 temp_v0_4;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    void *temp_v0_5;

    D_8007CC84 = D_8007CC88;
    DecDCTvlcBuild(D_8007CC8C);
    temp_v0 = M2C_FIELD(arg0, u16 *, 0xE);
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x10);
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 8);
    D_800D5818 = M2C_FIELD(arg0, s16 *, 4);
    D_800D581A = (s16) temp_v0_3;
    D_800D581C = (s16) M2C_FIELD(arg0, u16 *, 0xA);
    D_800D581E = (s16) M2C_FIELD(arg0, u16 *, 0xC);
    D_800D5820 = (s16) temp_v0;
    D_800D5822 = (s16) temp_v0_2;
    D_800D5824 = M2C_FIELD(arg0, s32 *, 0x14);
    D_800D5828 = M2C_FIELD(arg0, u16 *, 0x1C);
    D_800D582C = 0;
    D_800D5848 = 0;
    D_800D584A = 0;
    D_800D584C = func_80017304();
    D_800D584E = 0;
    D_800D5850 = 0;
    SetDefDispEnv((s32) D_800D5864, 0, 0, (s32) (s16) temp_v0_3, /* extra? */ 0x100);
    SetDefDispEnv((s32) D_800D5878, 0, 0x100, (s32) (s16) temp_v0_3, /* extra? */ 0x100);
    D_800D586C = 0;
    D_800D586E = 0x12;
    D_800D5870 = 0;
    D_800D5872 = 0x100;
    D_800D5880 = 0;
    D_800D5882 = 0x12;
    D_800D5884 = 0;
    D_800D5886 = 0x100;
    temp_v0_4 = M2C_FIELD(arg0, s16 *, 4) == 1;
    D_800D5889 = temp_v0_4;
    D_800D5875 = temp_v0_4;
    if ((M2C_FIELD(arg0, s16 *, 6) != 0) || (D_800D5818 != 0)) {
        func_8005C964();
    }
    func_8001626C(0);
    func_8001321C((s32) (&D_800D5818 + (D_800D584C * 0x14) + 0x4C));
    D_800D5830 = 0;
    D_800D5832 = 0;
    D_800D5834 = func_8005D3A0((s16) temp_v0 & 0xFFFF);
    D_800D5836 = (s16) temp_v0_2;
    D_800D5838 = 0;
    D_800D583A = 0x100;
    D_800D583C = func_8005D3A0((s16) temp_v0 & 0xFFFF);
    D_800D583E = (s16) temp_v0_2;
    temp_v0_5 = &D_800D5830 + (D_800D584C * 8);
    D_800D5840 = M2C_FIELD(temp_v0_5, s16 *, 0);
    D_800D5842 = M2C_FIELD(temp_v0_5, s16 *, 2);
    D_800D5844 = M2C_FIELD(temp_v0_5, s16 *, 4);
    D_800D5846 = M2C_FIELD(temp_v0_5, s16 *, 6);
    D_800D5844 = func_8005D3A0(0x10);
    temp_v0_6 = M2C_FIELD(arg0, s32 *, 0x18);
    var_t0 = temp_v0_6;
    if (temp_v0_6 != 0) {

    } else {
        var_t0 = 0x20400;
    }
    D_800D5854 = func_8005D8A0(var_t0);
    D_800D5858 = func_8005D8A0(M2C_ERROR(/* Read from unset register $t0 */));
    var_t0_2 = (s16) temp_v0_2 << 5;
    if (D_800D5818 != 0) {
        var_t0_2 = (s16) temp_v0_2 * 0x30;
    }
    D_800D585C = func_8005D8A0(var_t0_2);
    D_800D5860 = func_8005D8A0(M2C_ERROR(/* Read from unset register $t0 */));
    func_8005DCA0(0);
    DecDCTvlcSize2(0);
    func_8005DDE8((s32) func_8005D26C);
    D_8007CC80 = func_8005D8A0(0x20000);
    StSetRing(D_8007CC80, 0x40);
    StSetStream((s32) D_800D5818, 0, -1, 0, /* extra? */ 0);
    SsGetSerialVol(0, (s32) D_8007CC7C);
    SsSetSerialVol(0, (s32) (s16) D_800D5828, (s32) (s16) D_800D5828);
    func_8005D3DC();
}
