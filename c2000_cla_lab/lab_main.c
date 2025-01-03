//#############################################################################
//
// FILE:   lab_main.c
//
// TITLE:  C2000 Academy Lab Startup Project
//
//
// This example is a startup project for C2000 Academy lab.
//
//#############################################################################
//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#define BUF_BITS    7                           // Buffer bits <= 16.
#define BUF_LEN     (1 << BUF_BITS)             // Buffer length.
#define BUF_MASK    ((uint16_t)(BUF_LEN - 1))   // Buffer mask.

float       ClaBuf[BUF_LEN];                    // Buffer to store filtered samples.
float       AdcBuf[BUF_LEN];                    // Buffer for un-filtered samples.
uint16_t    ClaBufIdx   = 0;                    // Buffer index for ClaBuf.
uint16_t    AdcBufIdx   = 0;                    // Buffer index for AdcBufIdx.
uint16_t    LedCtr      = 0;

#pragma DATA_SECTION(filter_out,"Cla1ToCpuMsgRAM");
float filter_out;

#pragma DATA_SECTION(filter_in,"Cla1ToCpuMsgRAM");
float filter_in;


__interrupt void cla1Isr1(void)
{
    // Clear interrupt flags.
    ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);
    Interrupt_clearACKGroup(INT_myCLA01_INTERRUPT_ACK_GROUP);
    // Store raw ADC sample in AdcBuf.
    AdcBuf[AdcBufIdx++] = filter_in;
    AdcBufIdx &= BUF_MASK;
    // Store filtered output in ClaBuf.
    ClaBuf[ClaBufIdx++] = filter_out;
    ClaBufIdx &= BUF_MASK;
    // Toggle LED1 at a rate of 1Hz.
    if (LedCtr++ >= 8000) {
        GPIO_togglePin(myBoardLED0_GPIO);
        LedCtr = 0;
    }
}

//
// Main
//
void main(void)
{
    // Configure system clock and PLL, enable peripherals, and configure
    // flash if used.
    Device_init();
    // Initialize the PIE module and vector table.
    Interrupt_initModule();
    Interrupt_initVectorTable();
	Board_init();
    // Enable global interrupts.
    EINT;
    // Enable real-time debug.
    ERTM;
    for(;;) {
        NOP;  // Do nothing.
    }
}

//
// End of File
//
