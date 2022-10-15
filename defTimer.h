/*****************************************************************************
    System Name : TVoutColor_NTSC
    File Name   : defTimer.h
    Content     : 
    Version     : 0.0
    CPU board   : Arduino UNO/Duemilanove
    Compiler    : Arduino 1.0.4
    History     : 2013/10/04
*****************************************************************************/
/*----------------------------------------------------------------------------
;  Copyleft @Nabe_RMC
;---------------------------------------------------------------------------*/
/*==========================================================================*/
/*  DEFINE                                                                  */
/*==========================================================================*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Timer1
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define CRT_TCCR1A      0xC2        /* inv.,fast PWM            1100_xx10B  */
#define CRT_TCCR1A_P    0x02        /* cut OC1-normal Port out  0000_xx10B  */
#define CRT_TCCR1B      0x19        /* non divide               xx-1_1001B  */
                                    /* WGM 13 12 11 10                      */
                                    /*      1  1  1  0 - high PWM           */
#define CRT_TCCR1C      0x00        /* initial value            00--_----B  */
#define CRT_TCNT1       0x0000      /* initial value  0000_0000_0000_0000B  */
#define CRT_OCR1B       0x0000      /* initial value  0000_0000_0000_0000B  */

#define   XTAL1431818

#ifdef XTAL1431818

#define CRT_ICR1        907        /* 4*227-1,(1/14.318MHz)*(907+1)=63.416us*/
#define CRT_OCR1A_HS    67         /* (1/14.31818MHz)×67 = 4.679us         */
#define CRT_OCR1A_VS    (907- 67)

#else

#define CRT_ICR1        1017        /* (1/16MHz) × (1017+1) = 63.625us     */
#define CRT_OCR1A_HS    75          /* (1/16MHz)×75 = 4.6875us             */
#define CRT_OCR1A_VS    (1017- 75)

#endif


