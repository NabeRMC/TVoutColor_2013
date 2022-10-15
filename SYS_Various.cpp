/*****************************************************************************
    System Name : TVoutColor_NTSC
    File Name   : SYS_Various.cpp
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
/*  Includes                                                                */
/*==========================================================================*/
#define SYS_INCLUDE
#include "defSYS.h"
#include "defCRT.h"
#include "defINT.h"
#include "defPort.h"
#include "defCSL.h"

/*==========================================================================*/
/*  Program                                                                 */
/*==========================================================================*/
/*----------------------------------------------------------------------------
* Function : 
* Descr    : 
* Inputs   : 
* Outputs  : 
* Return   : 
*---------------------------------------------------------------------------*/
CINT    SobjINT;
CCSL    SobjCSL;

CSYS::CSYS()    //コンストラクタの定義 宣言はSYS.defの中で行っている。
{               //オブジェクトの初期化時に自動的に呼び出される関数
                //本来は初期化子を使用して初期化する。
                //理解していないのでとりあえず代入処理で済ませる。
}   

void CSYS::Ini()
{
    IniPort();
    IniTimer();
    IniINT();
}

/*----------------------------------------------------------------------------
    initializing Port
----------------------------------------------------------------------------*/
void CSYS::IniPort(void)
{
    PORTB   &= AND_PORTB;
    DDRB    |= OR_DDRB;
    PORTC   &= AND_PORTC;
    DDRC    |= OR_DDRC;
    PORTD   &= AND_PORTD;
    DDRD    |= OR_DDRD;
    
}

/*----------------------------------------------------------------------------
    initializing Timer
----------------------------------------------------------------------------*/
void CSYS::IniTimer(void)
{
    TCCR1A = CRT_TCCR1A;
    TCCR1B = CRT_TCCR1B;
    OCR1A  = CRT_OCR1A_HS;
    ICR1   = CRT_ICR1;
}

/*----------------------------------------------------------------------------
    initializing interrupt
----------------------------------------------------------------------------*/
void CSYS::IniINT(void){
    TIMSK1 = INI_TIMSK1;
    TIMSK0 = 0;                 /* Stop Timer0 interrupt                    */
}


/*----------------------------------------------------------------------------
    initializing UART   9600bps
        XTAL 14.31818MHz
        UBRRn = (14318180/(8*9600))-1 = 186.4 -1
        UBRR0H = 0x00
        UBRR0L = 0xB9
----------------------------------------------------------------------------*/
void CSYS::IniUART(void)
{
    UBRR0H = 0x00;
    UBRR0L = 0xB9;
}



/*----------------------------------------------------------------------------
    Delay 132ms
----------------------------------------------------------------------------*/
void CSYS::delay132( UB count )
{
    while( count != 0 ){
        while( SobjINT.Check132ms() == 0 ){
            SobjCSL.SetVram();
        }
        count--;
    }

}
