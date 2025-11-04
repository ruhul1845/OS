#include <stdint.h>
#include <scheduler.h>

extern tcb_t *current_tcb;

void PendSV_Handler(void)
{
    __asm volatile (
        "MRS   R0, PSP                      \n" /* R0 = current PSP */
        "STMDB R0!, {R4-R11}                \n" /* push r4-r11 onto task stack */
        "LDR   R1, =current_tcb             \n" /* address of current_tcb pointer */
        "LDR   R2, [R1]                     \n" /* R2 = current_tcb */
        "STR   R0, [R2]                     \n" /* current_tcb->stack_ptr = R0 */
        "PUSH  {LR}                         \n"
        "BL    schedule_next                \n"
        "POP   {LR}                         \n"
        "LDR   R1, =current_tcb             \n"
        "LDR   R2, [R1]                     \n" /* R2 = current_tcb (now next task) */
        "LDR   R0, [R2]                     \n" /* R0 = next->stack_ptr */
        "LDMIA R0!, {R4-R11}                \n" /* pop r4-r11 from next task stack */
        "MSR   PSP, R0                      \n" /* set PSP to new stack_ptr */
        "BX    LR                           \n"
    );
}
