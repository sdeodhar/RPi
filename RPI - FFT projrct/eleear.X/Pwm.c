#include "MAIN.h"

void Init_PWM( void )
{
    CCP1CON = 0b00001100;   // Enable PWM on CCP1
    CCP2CON = 0b00001100;   // Enable PWM on CCP2
    TRISC2 = 0;TRISC1 = 0;     // Make pin 17 (RC1/CCP2) an output
    T2CON = 0b00000100;     // Enable TMR2 with prescaler = 1
    PR2 = 249;   // PWM period = (PR2+1) * prescaler * Tcy = 1ms
    CCPR1L = 25; // pulse width = CCPR1L * prescaler * Tcy = 100us
    CCPR2L = 25;
    CCPR1L = 0; CCPR2L = 0;
}

void Set_PWM_Duty( void )
{
    CCPR1L = 250/(100/dutyvolt);      //CCP1CON = dutyvolt;
    CCPR2L = 250/(100/dutycurrent);   //CCP2CON = dutycurrent;
}

int8u ICalc_DutyCyc(int8u voltop, int8u currentop)
{
    dutyvolt = voltop;    //?? process accordingly
    dutycurrent = currentop;
    return 0;
}
