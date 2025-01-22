#include "Peripheral_Setup.h"
#define PI 3.141592653
#define PI2 (3.141592653/2.0)
#define PI3 (3.141592653/3.0)
#define PI6 (3.141592653/6.0)

__interrupt void isr_cpu_timer0(void);
__interrupt void isr_adc(void);


typedef enum {SPWM = 0, SVPWM = 1, DPWM1, DPWM2} en_pwm;

uint16_t counter = 0;
float dutya, dutyb, dutyc;
float theta;
float M;

en_pwm type_pwm = SPWM;

int main(void){
    InitSysCtrl();                              // Initialize System Control:
    InitGpio();
    DINT;                                       // Disable CPU interrupts
    InitPieCtrl();                              // Initialize the PIE control registers to their default state
    IER = 0x0000;                               // Disable CPU interrupts
    IFR = 0x0000;                               // Clear all CPU interrupt flags:
    InitPieVectTable();                         // Initialize the PIE vector table

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.CPUTIMER0 = 1;       // Enable timer clock
    PieVectTable.TIMER0_INT = &isr_cpu_timer0;  // Redirect function to interruption
    PieVectTable.ADCA1_INT = &isr_adc;          // Redirect function to interruption
    EDIS;

    // pg. 102 PIE Channel Mapping spruhm8i.pdf - Technical reference
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;          // Enable PieVector to Timer 0 interrupt
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;          // Enable PieVector to ADCA1 interrupt
    IER |= (M_INT1);                            // Enable lines of interrupt

    InitCpuTimers();                            // Initializae cpu timer
    ConfigCpuTimer(&CpuTimer0, 200, 1000000);   // Configure cpu timer0 with 200MHz and 1s
    CpuTimer0Regs.TCR.all = 0x4000;             // Enable timer 0

    Setup_GPIO();                               // Configure GPIOs
    Setup_ePWM();                               // Configure ePWM
    Setup_ADC_A();                              // Configure ADC A em 12bits

    dutya = dutyb = dutyc = 0;
    theta = 0;
    M = 0;
    theta = 0;

    EINT;                                       // Enable Global interrupt INTM
    ERTM;                                       // Enable Global realtime interrupt DBGM
    GpioDataRegs.GPADAT.bit.GPIO31 = 0;         // Turn off LED

    while(1){
        counter++;
    }// Infinite loop
    return 0;
}

// Interruptions
__interrupt void isr_cpu_timer0(void){
    GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

__interrupt void isr_adc(void){
    static float theta = 0;
    float temp;
    //((int)AdcaResultRegs.ADCRESULT0)) - 2047;

    theta += 6.2831853072/400.0;
    if(theta > 6.2831853071 ) theta -= 6.2831853071;
    else if(theta < -6.2831853071 ) theta += 6.2831853071;

    temp = M*__sqrt(3);

    if(type_pwm == 0){
        //SPMW
        dutya = M*__sin(theta);
        dutyb = M*__sin(theta + 2.0*PI3);
        dutyc = M*__sin(theta - 2.0*PI3);
    }else if(type_pwm == 1){
        //SVPWM
        if((theta >= 0) && (theta < PI3)){
            //#1
            dutya = M*__cos(theta + PI6) + M*__cos(theta - PI2);
            dutyb = M*__cos(theta - PI2) - M*__cos(theta + PI6);
            dutyc = -dutya;
        }else if((theta >= PI3) && (theta < 2.0*PI3)){
            //#2
            dutya = M*__cos(theta - PI6) -  M*__cos(theta - 5*PI6);
            dutyb = M*__cos(theta - PI6) +  M*__cos(theta - 5*PI6);
            dutyc = -dutyb;
        }else if((theta >= 2.0*PI3) && (theta < PI)){
            //#3
            dutyb =  M*__cos(theta - PI2) +  M*__cos(theta - 7*PI6);
            dutyc =  M*__cos(theta - 7*PI6) - M*__cos(theta - PI2);
            dutya = -dutyb;
        }else if((theta >= PI) && (theta < 4.0*PI3)){
            //#4
            dutyb =  M*__cos(theta - 5.0*PI6) - M*__cos(theta - 3.0*PI2);
            dutyc =  M*__cos(theta - 5.0*PI6) + M*__cos(theta - 3.0*PI2);
            dutya = -dutyc;
        }else if((theta >= 4.0*PI3) && (theta < 5.0*PI3)){
            //#5
            dutya = M*__cos(theta - 11.0*PI6) - M*__cos(theta - 7.0*PI6);
            dutyc = M*__cos(theta - 7.0*PI6) + M*__cos(theta - 11.0*PI6);
            dutyb = -dutyc;
        }else if((theta >= 5.0*PI3) && (theta < 2.0*PI)){
            //#6
            dutya = M*__cos(theta - 3.0*PI2) + M*__cos(theta - PI6);
            dutyc = M*__cos(theta - 3.0*PI2) - M*__cos(theta - PI6);
            dutyb = -dutya;
        }

    }else if(type_pwm == 2){
        //DPWM1
        if( ((theta >= 0) && (theta < PI6)) || ((theta >= 11.0*PI6) && (theta <2.0*PI))){
            //#1
            dutya = 1.0;
            dutyb = 1.0 - temp*__cos(theta + PI6);
            dutyc = 1.0 + temp*__cos(theta + 5.0*PI6);
        }else if((theta >= PI6) && (theta < PI2)){
            //#2
            dutya = -1.0 - temp*__cos(theta + 5.0*PI6);
            dutyb = -1.0 + temp*__cos(theta - PI2);
            dutyc = -1.0;
        }else if((theta >= PI2) && (theta < 5.0*PI6)){
            //#3
            dutya = 1.0 + temp*__cos(theta + PI6);
            dutyb = 1.0;
            dutyc = 1.0 - temp*__cos(theta - PI2);
        }else if((theta >= 5.0*PI6) && (theta < 7.0*PI6)){
            //#4
            dutya = -1.0;
            dutyb = -1.0 - temp*__cos(theta + PI6);;
            dutyc = -1.0 + temp*__cos(theta + 5.0*PI6);
        }else if((theta >= 7.0*PI6) && (theta < 3.0*PI2)){
            //#5
            dutya = 1.0 - temp*__cos(theta + 5.0*PI6);
            dutyb = 1.0 + temp*__cos(theta - PI2);
            dutyc = 1.0;
        }else if((theta >= 3.0*PI2) && (theta < 11.0*PI6)){
            //#6
            dutya = -1.0 + temp*__cos(theta + PI6);
            dutyb = -1.0;
            dutyc = -1.0 - temp*__cos(theta - PI2);
        }

    }else if(type_pwm == 3){
        //DPWM2

        if((theta >= 0) && (theta < PI3)){
            //#1
            dutya = 1.0;
            dutyb = 1.0 - temp*__cos(theta + PI6);
            dutyc = 1.0 + temp*__cos(theta + 5.0*PI6);
        }else if((theta >= PI3) && (theta < 2.0*PI3)){
            //#2
            dutya = -1.0 - temp*__cos(theta + 5.0*PI6);
            dutyb = -1.0 + temp*__cos(theta - PI2);
            dutyc = -1.0;
        }else if((theta >= 2.0*PI3) && (theta < PI)){
            //#3
            dutya = 1.0 + temp*__cos(theta + PI6);
            dutyb = 1.0;
            dutyc = 1.0 - temp*__cos(theta - PI2);
        }else if((theta >= PI) && (theta < 4.0*PI3)){
            //#4
            dutya = -1.0;
            dutyb = -1.0 - temp*__cos(theta + PI6);;
            dutyc = -1.0 + temp*__cos(theta + 5.0*PI6);
        }else if((theta >= 4.0*PI3) && (theta < 5.0*PI3)){
            //#5
            dutya = 1.0 - temp*__cos(theta + 5.0*PI6);
            dutyb = 1.0 + temp*__cos(theta - PI2);
            dutyc = 1.0;
        }else if((theta >= 5.0*PI3) && (theta < 2.0*PI)){
            //#6
            dutya = -1.0 + temp*__cos(theta + PI6);
            dutyb = -1.0;
            dutyc = -1.0 - temp*__cos(theta - PI2);
        }
    }

    //
    EPwm1Regs.CMPA.bit.CMPA =  (uint16_t)((dutya+1.0)* 0.5*((float)PWM_PERIOD));
    EPwm2Regs.CMPA.bit.CMPA =  (uint16_t)((dutyb+1.0)* 0.5*((float)PWM_PERIOD));
    EPwm3Regs.CMPA.bit.CMPA =  (uint16_t)((dutyc+1.0)* 0.5*((float)PWM_PERIOD));


    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
