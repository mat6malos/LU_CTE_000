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
#include "board.h"
//
// Global variables and definitions
//
#define ADC_BUF_LEN         50
uint16_t DEBUG_TOGGLE = 1;    // Used for real-time mode
uint16_t AdcBuf[ADC_BUF_LEN];  // ADC buffer allocation
//
// DAC global variables
//
uint16_t DacOutput;                       
uint16_t DacOffset;                       
uint16_t SINE_ENABLE = 0;                
// quadrature look-up table: contains 4 quadrants of sinusoidal data points
#define SINE_PTS 25
int QuadratureTable[SINE_PTS] = {
        0x0000,         // [0]  0.0
        0x1FD4,         // [1]  14.4
        0x3DA9,         // [2]  28.8
        0x579E,         // [3]  43.2
        0x6C12,         // [4]  57.6
        0x79BB,         // [5]  72.0
        0x7FBE,         // [6]  86.4
        0x7DBA,         // [7]  100.8
        0x73D0,         // [8]  115.2
        0x629F,         // [9]  129.6
        0x4B3B,         // [10] 144.0
        0x2F1E,         // [11] 158.4
        0x100A,         // [12] 172.8
        0xEFF6,         // [13] 187.2
        0xD0E2,         // [14] 201.6
        0xB4C5,         // [15] 216.0
        0x9D61,         // [16] 230.4
        0x8C30,         // [17] 244.8
        0x8246,         // [18] 259.2
        0x8042,         // [19] 273.6
        0x8645,         // [20] 288.0
        0x93EE,         // [21] 302.4
        0xA862,         // [22] 316.8
        0xC257,         // [23] 331.2
        0xE02C          // [24] 345.6
        };
//
// Function Declarations
//
__interrupt void INT_myADCA_1_ISR(void);
//
// Main
//
void main(void)
{
    // CPU Initialization
    Device_init();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    // Configure the GPIOs/ADC/PWM through SysConfig generated function found within
    // board.c
    Board_init();
    // Enable global interrupts and real-time debug
    EINT;
    ERTM;
    // Main Loop
    while(1){}
}
interrupt void INT_myADCA_1_ISR(void)
{
    static uint16_t *AdcBufPtr = AdcBuf;
    static volatile uint16_t LED_count = 0;
    // Read the ADC Result
    *AdcBufPtr++ = ADC_readResult(myADCA_RESULT_BASE, myADCA_SOC0);
    // Brute Force the circular buffer
    if (AdcBufPtr == (AdcBuf + ADC_BUF_LEN))
    {
        AdcBufPtr = AdcBuf;
    }
    // Toggle the pin
    if(DEBUG_TOGGLE == 1)
    {
        GPIO_togglePin(myGPIOToggle);             
    }
    if(LED_count++ > 25000)                      // Toggle slowly to see the LED blink
    {
        GPIO_togglePin(myBoardLED0_GPIO);                   // Toggle the pin
        LED_count = 0;                           // Reset the counter
    }
    // Write to DAC-B to create input to ADC-A0
    static uint16_t iQuadratureTable = 0;        // Quadrature table index
    if(SINE_ENABLE == 1)
    {
        DacOutput = DacOffset + ((QuadratureTable[iQuadratureTable++] ^ 0x8000) >> 5);
    }
    else
    {
        DacOutput = DacOffset;
    }
    if(iQuadratureTable > (SINE_PTS - 1))        // Wrap the index
    {
        iQuadratureTable = 0;
    }
    DAC_setShadowValue(myDACB_BASE, DacOutput);

    Interrupt_clearACKGroup(INT_myADCA_1_INTERRUPT_ACK_GROUP);
    ADC_clearInterruptStatus(myADCA_BASE, ADC_INT_NUMBER1);
} // End of ADC ISR

//
// End of File
//
