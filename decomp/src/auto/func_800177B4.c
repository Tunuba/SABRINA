#include "juego.h"
#include "m2c_macros.h"
#include "m2c_ajustes.h"

extern s32 D_800653C0;


void func_800177B4(void) {
    D_800653C0 = saved_reg_ra;
    func_80017BC0();
    M2C_ERROR(/* mtc0 $v0, $12 */);
    M2C_ERROR(/* unknown instruction: ctc2 $t0, $29 */);
    M2C_ERROR(/* unknown instruction: ctc2 $t0, $30 */);
    M2C_ERROR(/* unknown instruction: ctc2 $t0, $26 */);
    M2C_ERROR(/* unknown instruction: ctc2 $t0, $27 */);
    M2C_ERROR(/* unknown instruction: ctc2 $t0, $28 */);
    M2C_ERROR(/* unknown instruction: ctc2 $zero, $24 */);
    M2C_ERROR(/* unknown instruction: ctc2 $zero, $25 */);
}
