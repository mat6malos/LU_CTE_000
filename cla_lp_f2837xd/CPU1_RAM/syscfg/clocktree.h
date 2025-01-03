//#############################################################################
//
// FILE:   clockTree.h
//
// TITLE:  Setups device clocking for examples.
//
//#############################################################################
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

#ifndef CLOCKTREE_H
#define CLOCKTREE_H

//*****************************************************************************
//
// Summary of SYSPLL related clock configuration
//
//*****************************************************************************
//
// Input Clock to SYSPLL (OSCCLK)	= 10 MHz    (XTAL provides OSCCLK)
//
//##### SYSPLL ENABLED #####
//
// PLLRAWCLK				= 400 MHz   (Output of SYSPLL if enabled) 
// PLLSYSCLK				= 200 MHz
// CPU1CLK					= 200 MHz
// CPU2CLK					= 200 MHz 
// CPU1_SYSCLK				= 200 MHz
// CPU2_SYSCLK 				= 200 MHz
// LSPCLK					= 100 MHz 
// EPWMCLK 					= 100 MHz	
	
//*****************************************************************************
//
// Macro definitions used in device.c (SYSPLL / LSPCLK)
//
//*****************************************************************************
//
//	Input Clock to SYSPLL (OSCCLK) = XTAL = 10 MHz
//
#define DEVICE_OSCSRC_FREQ          10000000U
//
// Define to pass to SysCtl_setClock(). Will configure the clock as follows:
// SYSPLL ENABLED
// SYSCLK = 200 MHz = 10 MHz (OSCCLK) * (40 (IMULT) + 0 (FMULT)) / 2 (SYSCLKDIVSEL)	
#define DEVICE_SYSCLK_FREQ          ((DEVICE_OSCSRC_FREQ * (40 + 0)) / 2)
//
#define DEVICE_SETCLOCK_CFG         (SYSCTL_OSCSRC_XTAL | SYSCTL_IMULT(40) | \
									 SYSCTL_FMULT_NONE | SYSCTL_SYSDIV(2)| \
									 SYSCTL_PLL_ENABLE)

//
// Define to pass to SysCtl_setLowSpeedClock().
// Low Speed Clock (LSPCLK) = 200 MHz / 2 = 100 MHz
//
#define DEVICE_LSPCLK_CFG  			SYSCTL_LSPCLK_PRESCALE_2

#define DEVICE_LSPCLK_FREQ          (DEVICE_SYSCLK_FREQ / 2)

//*****************************************************************************
//
// Summary of AUXPLL related clock configuration
//
//*****************************************************************************
//
// Input Clock to AUXOSCCLK	= 10 MHz (XTAL provides AUXOSCCLK)  
//
//##### AUXPLL DISABLED #####
//
// AUXPLLRAWCLK				= 200 MHz (Output of AUXPLL if enabled)
// AUXPLLCLK				= 5 MHz 
//
//*****************************************************************************
//
// Macro definitions used in device.c (AUXPLL)
//
//*****************************************************************************
//
//	Input Clock to AUXPLL (AUXOSCCLK) = XTAL = 10 MHz
//
#define DEVICE_AUXOSCSRC_FREQ 		10000000U
//
// Define to pass to SysCtl_setAuxClock(). Will configure the clock as follows:
// AUXPLL DISABLED
// AUXPLLCLK = 5 MHz = 10 MHz (XTAL) / 2 (AUXCLKDIVSEL)
#define DEVICE_AUXCLK_FREQ			(DEVICE_AUXOSCSRC_FREQ  / 2) 
//
#define DEVICE_SETAUXCLOCK_CFG      (SYSCTL_AUXPLL_OSCSRC_XTAL | SYSCTL_AUXPLL_IMULT(20) | \
									 SYSCTL_AUXPLL_FMULT_NONE | SYSCTL_AUXPLL_DIV_2 | \
									 SYSCTL_AUXPLL_DISABLE)

	
//*****************************************************************************
//
// CPU1CLK / CPU2CLK Domain (200 MHz)
//
//*****************************************************************************
// VCU
// TMU
// FPU
// Flash
// BOOTROM
// Mx/DxRAM
//	

//*****************************************************************************
//
// CPU1 SYSCLK Domain (200 MHz)
//
//*****************************************************************************
// EPIE
// LSxRAMs
// CLAMessageRAM
// DCSM
//	

/////////////////////	
// Gated CPU1 SYSCLK
/////////////////////
// CPU1_CLA1
// CPU1_DMA
// CPU1_Timer
// EMIF2
// uPP
//

//*****************************************************************************
//
// CPU2 SYSCLK Domain (200 MHz)
//
//*****************************************************************************
// EPIE
// LSxRAMs
// CLAMessageRAM
// DCSM
//
	
/////////////////////	
// Gated CPU2 SYSCLK
/////////////////////
// CPU2_CLA1
// CPU2_DMA
// CPU2_Timer
//
//*****************************************************************************
//
// Gated Peripheral EPWM Domain (100 MHz) 
//
//*****************************************************************************
// EPWM
// HRPWM
//
//*****************************************************************************
//
// Gated Peripheral SYSCLK Domain (200 MHz) 
//
//*****************************************************************************
// ADC
// CMPSS
// DAC
// EPWM
// ECAP
// EQEP
// I2C
// SDFM
// EMIF
//	
//*****************************************************************************
//
// Gated LSPCLK Domain (100 MHz) 
//
//*****************************************************************************
// SCI
// SPI
// McBSP

#endif // CLOCKTREE_H
