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
#include "board.h"
#include "lab_shared.h"
#include "device.h"
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
#define FIR_LEN     32
const float coeffs[FIR_LEN] = {
    -0.0006103139426196,-0.005592184655005,-0.01292485322836 ,-0.01926532895538,
    -0.01762908502044  ,-0.004303218458627, 0.01563724674838 , 0.02815885544785,
     0.01902562195175  ,-0.01290472511163 ,-0.04827630093442 ,-0.0545188692635,
    -0.006464860729499 , 0.09270744275212 , 0.2064249836238  , 0.2822241125204,
     0.2822241125204   , 0.2064249836238  , 0.09270744275212 ,-0.006464860729499,
    -0.0545188692635   ,-0.04827630093442 ,-0.01290472511163 , 0.01902562195175,
     0.02815885544785  , 0.01563724674838 ,-0.004303218458627,-0.01762908502044,
    -0.01926532895538  ,-0.01292485322836 ,-0.005592184655005,-0.0006103139426196
};
float delay[FIR_LEN];

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
// FIR LP filter task.
__attribute__((interrupt)) void Cla1Task1(void)
{
    int16_t i;
    uint16_t tmpData;
    filter_out = 0.0;
    // Uncomment this to debug the CLA while connected to the debugger
    //__mdebugstop();
    // Read in new sample and subtract off the bias.
    tmpData = ADC_readResult(myADC0_RESULT_BASE, myADC0_SOC0);
    filter_in = ((float)(tmpData) - (float)(1 << (ADC_BITS - 1)))*ADC_VSTEP;
    // Shift the delay line to the right by 1.
    #pragma UNROLL(FIR_LEN - 1)
    for (i = FIR_LEN - 1; i > 0; i--) {
        delay[i] = delay[i-1];
        filter_out += coeffs[i]*delay[i];
    }
    // Add the new ADC sample to the delay line.
    delay[0] = filter_in;
    filter_out += coeffs[0]*delay[0];
}
__attribute__((interrupt)) void Cla1Task8(void)
{
    int16_t i;
    for (i = 0; i < ((int16_t)FIR_LEN); i++) {
        delay[i] = 0.0;
    }
}
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
// End of File
//
