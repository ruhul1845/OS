/*
 * Copyright (c) 2022 
 * Computer Science and Engineering, University of Dhaka
 * Credit: CSE Batch 25 (starter) and Prof. Mosaddek Tushar
 */

#include <stm32_startup.h>
#include <stdint.h>     // 
#include "../../syscall/syscall.h"   //

/* Stack start (top of SRAM) */
const uintptr_t STACK_START = (uintptr_t)SRAM_END;

/*
 * Vector table placed in .isr_vector section.
 * Use uintptr_t instead of uint32_t for portability.
 */
__attribute__((section(".isr_vector")))
const uintptr_t NVIC_VECTOR[] = {
    STACK_START,
    (uintptr_t)&Reset_Handler,
    (uintptr_t)&NMI_Handler,
    (uintptr_t)&HardFault_Handler,
    (uintptr_t)&MemManage_Handler,
    (uintptr_t)&BusFault_Handler,
    (uintptr_t)&UsageFault_Handler,
    0, 0, 0, 0,
    (uintptr_t)&SVCall_Handler,
    (uintptr_t)&DebugMonitor_Handler,
    0,
    (uintptr_t)&PendSV_Handler,
    (uintptr_t)&SysTick_Handler,

    /* Peripheral interrupt handlers */
    (uintptr_t)&WWDG_Handler,
    (uintptr_t)&PVD_Handler,
    (uintptr_t)&TAMP_STAMP_Handler,
    (uintptr_t)&RTC_WKUP_Handler,
    (uintptr_t)&FLASH_Handler,
    (uintptr_t)&RCC_Handler,
    (uintptr_t)&EXTI0_Handler,
    (uintptr_t)&EXTI1_Handler,
    (uintptr_t)&EXTI2_Handler,
    (uintptr_t)&EXTI3_Handler,
    (uintptr_t)&EXTI4_Handler,
    (uintptr_t)&DMA1_Stream0_Handler,
    (uintptr_t)&DMA1_Stream1_Handler,
    (uintptr_t)&DMA1_Stream2_Handler,
    (uintptr_t)&DMA1_Stream3_Handler,
    (uintptr_t)&DMA1_Stream4_Handler,
    (uintptr_t)&DMA1_Stream5_Handler,
    (uintptr_t)&DMA1_Stream6_Handler,
    (uintptr_t)&ADC_Handler,
    (uintptr_t)&CAN1_TX_Handler,
    (uintptr_t)&CAN1_RX0_Handler,
    (uintptr_t)&CAN1_RX1_Handler,
    (uintptr_t)&CAN1_SCE_Handler,
    (uintptr_t)&EXTI9_5_Handler,
    (uintptr_t)&TIM1_BRK_TIM9_Handler,
    (uintptr_t)&TIM1_UP_TIM10_Handler,
    (uintptr_t)&TIM1_TRG_COM_TIM11_Handler,
    (uintptr_t)&TIM1_CC_Handler,
    (uintptr_t)&TIM2_Handler,
    (uintptr_t)&TIM3_Handler,
    (uintptr_t)&TIM4_Handler,
    (uintptr_t)&I2C1_EV_Handler,
    (uintptr_t)&I2C1_ER_Handler,
    (uintptr_t)&I2C2_EV_Handler,
    (uintptr_t)&I2C2_ER_Handler,
    (uintptr_t)&SPI1_Handler,
    (uintptr_t)&SPI2_Handler,
    (uintptr_t)&USART1_Handler,
    (uintptr_t)&USART2_Handler,
    (uintptr_t)&USART3_Handler,
    (uintptr_t)&EXTI15_10_Handler,
    (uintptr_t)&RTC_Alarm_Handler,
    (uintptr_t)&OTG_FS_WKUP_Handler,
    (uintptr_t)&TIM8_BRK_TIM12_Handler,
    (uintptr_t)&TIM8_UP_TIM13_Handler,
    (uintptr_t)&TIM8_TRG_COM_TIM14_Handler,
    (uintptr_t)&TIM8_CC_Handler,
    (uintptr_t)&DMA1_Stream7_Handler,
    (uintptr_t)&FMC_Handler,
    (uintptr_t)&SDIO_Handler,
    (uintptr_t)&TIM5_Handler,
    (uintptr_t)&SPI3_Handler,
    (uintptr_t)&UART4_Handler,
    (uintptr_t)&UART5_Handler,
    (uintptr_t)&TIM6_DAC_Handler,
    (uintptr_t)&TIM7_Handler,
    (uintptr_t)&DMA2_Stream0_Handler,
    (uintptr_t)&DMA2_Stream1_Handler,
    (uintptr_t)&DMA2_Stream2_Handler,
    (uintptr_t)&DMA2_Stream3_Handler,
    (uintptr_t)&DMA2_Stream4_Handler,
    0, 0,
    (uintptr_t)&CAN2_TX_Handler,
    (uintptr_t)&CAN2_RX0_Handler,
    (uintptr_t)&CAN2_RX1_Handler,
    (uintptr_t)&CAN2_SCE_Handler,
    (uintptr_t)&OTG_FS_Handler,
    (uintptr_t)&DMA2_Stream5_Handler,
    (uintptr_t)&DMA2_Stream6_Handler,
    (uintptr_t)&DMA2_Stream7_Handler,
    (uintptr_t)&USART6_Handler,
    (uintptr_t)&I2C3_EV_Handler,
    (uintptr_t)&I2C3_ER_Handler,
    (uintptr_t)&OTG_HS_EP1_OUT_Handler,
    (uintptr_t)&OTG_HS_EP1_IN_Handler,
    (uintptr_t)&OTG_HS_WKUP_Handler,
    (uintptr_t)&OTG_HS_Handler,
    (uintptr_t)&DCMI_Handler,
    0, 0,
    (uintptr_t)&FPU_Handler,
    0, 0,
    (uintptr_t)&SPI4_Handler,
    0, 0,
    (uintptr_t)&SAI1_Handler,
    0, 0, 0,
    (uintptr_t)&SAI2_Handler,
    (uintptr_t)&QuadSPI_Handler,
    (uintptr_t)&HDMI_CEC_Handler,
    (uintptr_t)&SPDIF_Rx_Handler,
    (uintptr_t)&FMPI2C1_Handler,
    (uintptr_t)&FMPI2C1_ERR_Handler
};

/* ---------------------------------------------------------------------- */

void Reset_Handler(void)
{
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *pDst = (uint8_t*)&_sdata;
    uint8_t *pSrc = (uint8_t*)&_la_data;
    for(uint32_t i=0; i<size; i++)
        *pDst++ = *pSrc++;

    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDst = (uint8_t*)&_sbss;
    for(uint32_t i=0; i<size; i++)
        *pDst++ = 0;

    _text_size = (uint32_t)&_etext - (uint32_t)&_stext;
    _data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
    _bss_size  = (uint32_t)&_ebss - (uint32_t)&_sbss;

    kmain();   // jump to kernel main
}

void Default_Handler(void)
{
    while(1);
}

/* Fault handlers */
void HardFault_Handler(void) { while(1); }
void MemManage_Handler(void) { while(1); }
void BusFault_Handler(void)  { while(1); }

/* ---------------------------------------------------------------------- */

void SVCall_Handler(void)
{
    __asm volatile (
        "TST LR, #4\n"
        "ITE EQ\n"
        "MRSEQ R0, MSP\n"
        "MRSNE R0, PSP\n"
        "B SVC_Handler_C\n"
    );
}
