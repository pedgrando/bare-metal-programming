#include "../headers/irq.h"
#include "../CMSIS/Include/core_cm4.h"

// Define default handlers for each interrupt
// These macros generate weak -> can be overridden

MAKE_DEFAULT_HANDLER(NMI_Handler)
MAKE_DEFAULT_HANDLER(HardFault_Handler)
MAKE_DEFAULT_HANDLER(MemManage_Handler)
MAKE_DEFAULT_HANDLER(UsageFault_Handler)
MAKE_DEFAULT_HANDLER(BusFault_Handler)
MAKE_DEFAULT_HANDLER(SVC_Handler)
MAKE_DEFAULT_HANDLER(PendSV_Handler)
MAKE_DEFAULT_HANDLER(SysTick_Handler)
MAKE_DEFAULT_HANDLER(WWDG_IRQHandler)
MAKE_DEFAULT_HANDLER(PVD_PVM_IRQHandler)
MAKE_DEFAULT_HANDLER(TAMP_STAMP_IRQHandler)
MAKE_DEFAULT_HANDLER(RTC_WKUP_IRQHandler)
MAKE_DEFAULT_HANDLER(FLASH_IRQHandler)
MAKE_DEFAULT_HANDLER(RCC_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI0_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI1_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI2_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI3_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI4_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_Channel1_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_Channel2_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_Channel3_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_Channel4_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_Channel5_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_Channel6_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_Channel7_IRQHandler)
MAKE_DEFAULT_HANDLER(ADC1_2_IRQHandler)
MAKE_DEFAULT_HANDLER(CAN1_TX_IRQHandler)
MAKE_DEFAULT_HANDLER(CAN1_RX0_IRQHandler)
MAKE_DEFAULT_HANDLER(CAN1_RX1_IRQHandler)
MAKE_DEFAULT_HANDLER(CAN1_SCE_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI9_5_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM1_BRK_TIM15_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM1_UP_TIM16_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM1_TRG_COM_TIM17_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM1_CC_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM2_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM3_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM4_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C1_EV_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C1_ER_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C2_EV_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C2_ER_IRQHandler)
MAKE_DEFAULT_HANDLER(SPI1_IRQHandler)
MAKE_DEFAULT_HANDLER(SPI2_IRQHandler)
MAKE_DEFAULT_HANDLER(USART1_IRQHandler)
MAKE_DEFAULT_HANDLER(USART2_IRQHandler)
MAKE_DEFAULT_HANDLER(USART3_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI15_10_IRQHandler)
MAKE_DEFAULT_HANDLER(RTC_Alarm_IRQHandler)
MAKE_DEFAULT_HANDLER(DFSDM1_FLT3_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM8_BRK_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM8_UP_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM8_TRG_COM_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM8_CC_IRQHandler)
MAKE_DEFAULT_HANDLER(ADC3_IRQHandler)
MAKE_DEFAULT_HANDLER(FMC_IRQHandler)
MAKE_DEFAULT_HANDLER(SDMMC1_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM5_IRQHandler)
MAKE_DEFAULT_HANDLER(SPI3_IRQHandler)
MAKE_DEFAULT_HANDLER(UART4_IRQHandler)
MAKE_DEFAULT_HANDLER(UART5_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM6_DAC_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM7_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_Channel1_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_Channel2_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_Channel3_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_Channel4_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_Channel5_IRQHandler)
MAKE_DEFAULT_HANDLER(DFSDM1_FLT0_IRQHandler)
MAKE_DEFAULT_HANDLER(DFSDM1_FLT1_IRQHandler)
MAKE_DEFAULT_HANDLER(DFSDM1_FLT2_IRQHandler)
MAKE_DEFAULT_HANDLER(COMP_IRQHandler)
MAKE_DEFAULT_HANDLER(LPTIM1_IRQHandler)
MAKE_DEFAULT_HANDLER(LPTIM2_IRQHandler)
MAKE_DEFAULT_HANDLER(OTG_FS_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_Channel6_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_Channel7_IRQHandler)
MAKE_DEFAULT_HANDLER(LPUART1_IRQHandler)
MAKE_DEFAULT_HANDLER(QUADSPI_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C3_EV_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C3_ER_IRQHandler)
MAKE_DEFAULT_HANDLER(SAI1_IRQHandler)
MAKE_DEFAULT_HANDLER(SAI2_IRQHandler)
MAKE_DEFAULT_HANDLER(SWPMI1_IRQHandler)
MAKE_DEFAULT_HANDLER(TSC_IRQHandler)
MAKE_DEFAULT_HANDLER(RNG_IRQHandler)
MAKE_DEFAULT_HANDLER(FPU_IRQHandler)

// Define the vector table as a const pointer array 
__attribute__((section(".isr_vector"))) void * const vector_table[] = {
    // Stack and Reset Handler
    &_sstack,               /* Top of stack (initial value of the SP register) */
    _start,                /* Reset handler (initial value of the PC register) */

    // ARM Cortex-M4 processor exceptions
    NMI_Handler,            /* -14: Non-Maskable Interrupt */
    HardFault_Handler,      /* -13: Hard Fault Interrupt */
    MemManage_Handler,      /* -12: Memory Management Interrupt */
    BusFault_Handler,       /* -11: Bus Fault Interrupt */
    UsageFault_Handler,     /* -10: Usage Fault Interrupt */
    0,                      /* Reserved */
    0,                      /* Reserved */
    0,                      /* Reserved */
    0,                      /* Reserved */
    SVC_Handler,            /* -5: SVCall Interrupt */
    0,                      /* Reserved */
    0,                      /* Reserved */
    PendSV_Handler,         /* -2: PendSV Interrupt */
    SysTick_Handler,        /* -1: SysTick Interrupt */

    // STM32L475 specific external interrupts
    WWDG_IRQHandler,        /* 0: Window WatchDog Interrupt */
    PVD_PVM_IRQHandler,     /* 1: PVD/PVM through EXTI Line detection Interrupts */
    TAMP_STAMP_IRQHandler,  /* 2: Tamper and TimeStamp interrupts through EXTI */
    RTC_WKUP_IRQHandler,    /* 3: RTC Wakeup interrupt through EXTI */
    FLASH_IRQHandler,       /* 4: FLASH global Interrupt */
    RCC_IRQHandler,         /* 5: RCC global Interrupt */
    EXTI0_IRQHandler,       /* 6: EXTI Line0 Interrupt */
    EXTI1_IRQHandler,       /* 7: EXTI Line1 Interrupt */
    EXTI2_IRQHandler,       /* 8: EXTI Line2 Interrupt */
    EXTI3_IRQHandler,       /* 9: EXTI Line3 Interrupt */
    EXTI4_IRQHandler,       /* 10: EXTI Line4 Interrupt */
    DMA1_Channel1_IRQHandler, /* 11: DMA1 Channel 1 global Interrupt */
    DMA1_Channel2_IRQHandler, /* 12: DMA1 Channel 2 global Interrupt */
    DMA1_Channel3_IRQHandler, /* 13: DMA1 Channel 3 global Interrupt */
    DMA1_Channel4_IRQHandler, /* 14: DMA1 Channel 4 global Interrupt */
    DMA1_Channel5_IRQHandler, /* 15: DMA1 Channel 5 global Interrupt */
    DMA1_Channel6_IRQHandler, /* 16: DMA1 Channel 6 global Interrupt */
    DMA1_Channel7_IRQHandler, /* 17: DMA1 Channel 7 global Interrupt */
    ADC1_2_IRQHandler,      /* 18: ADC1, ADC2 SAR global Interrupts */
    CAN1_TX_IRQHandler,     /* 19: CAN1 TX Interrupt */
    CAN1_RX0_IRQHandler,    /* 20: CAN1 RX0 Interrupt */
    CAN1_RX1_IRQHandler,    /* 21: CAN1 RX1 Interrupt */
    CAN1_SCE_IRQHandler,    /* 22: CAN1 SCE Interrupt */
    EXTI9_5_IRQHandler,     /* 23: External Line[9:5] Interrupts */
    TIM1_BRK_TIM15_IRQHandler, /* 24: TIM1 Break and TIM15 global interrupt */
    TIM1_UP_TIM16_IRQHandler, /* 25: TIM1 Update and TIM16 global interrupt */
    TIM1_TRG_COM_TIM17_IRQHandler, /* 26: TIM1 Trigger/Commutation and TIM17 global interrupt */
    TIM1_CC_IRQHandler,     /* 27: TIM1 Capture Compare Interrupt */
    TIM2_IRQHandler,        /* 28: TIM2 global Interrupt */
    TIM3_IRQHandler,        /* 29: TIM3 global Interrupt */
    TIM4_IRQHandler,        /* 30: TIM4 global Interrupt */
    I2C1_EV_IRQHandler,     /* 31: I2C1 Event Interrupt */
    I2C1_ER_IRQHandler,     /* 32: I2C1 Error Interrupt */
    I2C2_EV_IRQHandler,     /* 33: I2C2 Event Interrupt */
    I2C2_ER_IRQHandler,     /* 34: I2C2 Error Interrupt */
    SPI1_IRQHandler,        /* 35: SPI1 global Interrupt */
    SPI2_IRQHandler,        /* 36: SPI2 global Interrupt */
    USART1_IRQHandler,      /* 37: USART1 global Interrupt */
    USART2_IRQHandler,      /* 38: USART2 global Interrupt */
    USART3_IRQHandler,      /* 39: USART3 global Interrupt */
    EXTI15_10_IRQHandler,   /* 40: External Line[15:10] Interrupts */
    RTC_Alarm_IRQHandler,   /* 41: RTC Alarm through EXTI Line Interrupt */
    DFSDM1_FLT3_IRQHandler, /* 42: DFSDM1 Filter 3 global Interrupt */
    TIM8_BRK_IRQHandler,    /* 43: TIM8 Break Interrupt */
    TIM8_UP_IRQHandler,     /* 44: TIM8 Update Interrupt */
    TIM8_TRG_COM_IRQHandler, /* 45: TIM8 Trigger/Commutation Interrupt */
    TIM8_CC_IRQHandler,     /* 46: TIM8 Capture Compare Interrupt */
    ADC3_IRQHandler,        /* 47: ADC3 global Interrupt */
    FMC_IRQHandler,         /* 48: FMC global Interrupt */
    SDMMC1_IRQHandler,      /* 49: SDMMC1 global Interrupt */
    TIM5_IRQHandler,        /* 50: TIM5 global Interrupt */
    SPI3_IRQHandler,        /* 51: SPI3 global Interrupt */
    UART4_IRQHandler,       /* 52: UART4 global Interrupt */
    UART5_IRQHandler,       /* 53: UART5 global Interrupt */
    TIM6_DAC_IRQHandler,    /* 54: TIM6 global and DAC1&2 underrun error interrupts */
    TIM7_IRQHandler,        /* 55: TIM7 global Interrupt */
    DMA2_Channel1_IRQHandler, /* 56: DMA2 Channel 1 global Interrupt */
    DMA2_Channel2_IRQHandler, /* 57: DMA2 Channel 2 global Interrupt */
    DMA2_Channel3_IRQHandler, /* 58: DMA2 Channel 3 global Interrupt */
    DMA2_Channel4_IRQHandler, /* 59: DMA2 Channel 4 global Interrupt */
    DMA2_Channel5_IRQHandler, /* 60: DMA2 Channel 5 global Interrupt */
    DFSDM1_FLT0_IRQHandler, /* 61: DFSDM1 Filter 0 global Interrupt */
    DFSDM1_FLT1_IRQHandler, /* 62: DFSDM1 Filter 1 global Interrupt */
    DFSDM1_FLT2_IRQHandler, /* 63: DFSDM1 Filter 2 global Interrupt */
    COMP_IRQHandler,        /* 64: COMP1 and COMP2 Interrupts */
    LPTIM1_IRQHandler,      /* 65: LP TIM1 interrupt */
    LPTIM2_IRQHandler,      /* 66: LP TIM2 interrupt */
    OTG_FS_IRQHandler,      /* 67: USB OTG FS global Interrupt */
    DMA2_Channel6_IRQHandler, /* 68: DMA2 Channel 6 global interrupt */
    DMA2_Channel7_IRQHandler, /* 69: DMA2 Channel 7 global interrupt */
    LPUART1_IRQHandler,     /* 70: LP UART1 interrupt */
    QUADSPI_IRQHandler,     /* 71: Quad SPI global interrupt */
    I2C3_EV_IRQHandler,     /* 72: I2C3 event interrupt */
    I2C3_ER_IRQHandler,     /* 73: I2C3 error interrupt */
    SAI1_IRQHandler,        /* 74: Serial Audio Interface 1 global interrupt */
    SAI2_IRQHandler,        /* 75: Serial Audio Interface 2 global interrupt */
    SWPMI1_IRQHandler,      /* 76: Serial Wire Interface 1 global interrupt */
    TSC_IRQHandler,         /* 77: Touch Sense Controller global interrupt */
    RNG_IRQHandler,         /* 80: RNG global interrupt */
    FPU_IRQHandler          /* 81: FPU global interrupt */
};

// Init of the interruption vector in SCB
void irq_init(void){
	SCB->VTOR = (uint32_t)vector_table ;	
}
