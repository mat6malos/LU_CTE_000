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
//
// Global variables and definitions
//
#define ADC_BUF_LEN         50
uint16_t DEBUG_TOGGLE = 1;    // Used for real-time mode
uint16_t AdcBuf[ADC_BUF_LEN];  // ADC buffer allocation
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
    Interrupt_clearACKGroup(INT_myADCA_1_INTERRUPT_ACK_GROUP);
    ADC_clearInterruptStatus(myADCA_BASE, ADC_INT_NUMBER1);
} // End of ADC ISR

//
// End of File
//
