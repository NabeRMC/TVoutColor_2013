/*****************************************************************************
    System Name : TVoutColor_NTSC
    File Name   : defSYS.h
    Content     : 
    Version     : 0.0
    CPU board   : Arduino UNO/Duemilanove
    Compiler    : Arduino 1.0.4
    History     : 2013/10/04
*****************************************************************************/
/*----------------------------------------------------------------------------
;  Copyleft @Nabe_RMC
;---------------------------------------------------------------------------*/
#ifdef      SYS_INCLUDE
#define     SYS_EXT 
#else
#define     SYS_EXT extern
#endif

/*==========================================================================*/
/*  Includes                                                                */
/*==========================================================================*/
#ifndef     COMMON_H
#include    "nabe_common.h"
#endif

#include    "defPort.h"
#include    "defTimer.h"

/*==========================================================================*/
/*  DEFINE                                                                  */
/*==========================================================================*/
//#define LCD_Display

/* ----- interrupt ---------------------------------------------------------*/
#define INI_TIMSK1  0x20    /* Timer/Counter1 Interrupt Mask Register       */
                            /* enable ICE1                      0010_0000B  */


/*==========================================================================*/
/*                                                                          */
/*==========================================================================*/
class CSYS
{
public:
    CSYS();                 //コンストラクタの宣言 名前はクラスと同じになる。
                            //ここでは引数無し
    void Ini();
    void delay132(UB);
    void IniUART();
private:
    static void IniPort();
    static void IniTimer();
    static void IniINT();
};

