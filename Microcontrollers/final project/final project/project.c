//*****************************************************************************
//
// project.c - Simple project to use as a starting point for more complex
//             projects.
//
// Copyright (c) 2013-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
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
// 
// This is part of revision 2.1.0.12573 of the Tiva Firmware Development Package.
//
//*****************************************************************************

//*****************************************************************************
// Additional Credits:
// Ronan Higgins - Advice regarding audio production

//why do i need to do this? I don't know, but I do. 
#define PART_TM4C123GH6PM

#include <stdbool.h>
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"

#include "driverlib/pwm.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/adc.h"
#include "driverlib/pin_map.h"


#include "audio.h"

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

const uint32_t adcCountdown = 2000; //sample rate for ADC
const uint32_t audioSampleRate = 8000; //hz 
const uint32_t audioCountdown = 2000; //cycles between audio update
uint16_t audioPointer = -1;
uint8_t* audioSample;
uint16_t audioSampleLength = 0;
uint16_t latestADCSample = 0;



void intADC(void);
void intAudio(void);
void intAudioStart(void);

int main(void)
{
	//SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
	//SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
	
	//SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); //probably activates the adc and pin?
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0); //for interrupts

	//enale gpio buttons for usage
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD); 

	//enable pwm modules
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	
	// Configure ADC
	//I want to set it so the adc has oversampling to slow it down
	//ADCSoftwareOversampleConfigure(ADC0_BASE, 64);



	// Configure Timer
	//timer a controls audio playback, timer b controls adc/pwm translation + audio volume (somehow without flops)
	TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC | TIMER_CFG_B_PERIODIC);
	
	//set so ADC triggers on timer b timeout
	//bad idea, just trigger it on the timeout 
	//TimerADCEventSet(ADC0_BASE, TIMER_ADC_TIMEOUT_B);
	
	//int on timer a and b timeout
	TimerIntEnable(TIMER0_BASE, TIMER_A);
	TimerIntEnable(TIMER0_BASE, TIMER_B);

	//maybe activate at the same time?
	//register timer a
	TimerIntRegister(TIMER0_BASE, INT_TIMER0A, intAudio);
	//register timer b
	TimerIntRegister(TIMER0_BASE, INT_TIMER0B, intADC);

	//start the timers' periods
	TimerLoadSet(TIMER0_BASE, TIMER_A, audioCountdown);
	TimerLoadSet(TIMER0_BASE, TIMER_B, adcCountdown);



	//Configuring PWM Buzzer
	GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_4);
	GPIOPinConfigure(GPIO_PC4_M0PWM6);


	SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

	//Set Generator 3 to count down
	PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);

	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, audioCountdown);
		

	//configuring gpio button push to start audio
	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_RISING_EDGE);
	GPIOIntEnable(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	GPIOIntRegister(GPIO_PORTD_BASE, intAudioStart);


	IntEnable(INT_TIMER0A);
	IntEnable(INT_TIMER0B);
	IntEnable(INT_GPIOD);

	IntMasterEnable();
	

	while(1);
	return 0;
}

//to be called when a new ADC value is to be read, update motor controller
//vestigial, in case audio controller isn't enough
void intADC(void){
	TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
	return;

	
}


void intAudio(void){
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	if(audioPointer >= audioSampleLength){
		PWMGenDisable(PWM0_BASE, PWM_GEN_3);
		return;
	}
	//change audio modulation

	uint32_t nextAmplitude = ( audioCountdown * audioSample[audioPointer++]) >> 8;
	//Apply to PWM
	PWMPulseWidthSet(PWM0_BASE, PWM_GEN_3, nextAmplitude);
	PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, true);
	PWMGenEnable(PWM0_BASE, PWM_GEN_3);
}

void intAudioStart(void){
	uint32_t pins = GPIOIntStatus(GPIO_PORTD_BASE, true);
	GPIOIntClear(GPIO_PORTD_BASE, pins);
	if(pins & GPIO_INT_PIN_0){
		audioSample = (uint8_t*)helloAudio;
		audioSampleLength = helloAudioLength;
	} else if(pins & GPIO_INT_PIN_1){
		audioSample = (uint8_t*)screamAudio;
		audioSampleLength = screamAudioLength;
	} else{
		return;
	}
	audioPointer = 0;
	return;
}
