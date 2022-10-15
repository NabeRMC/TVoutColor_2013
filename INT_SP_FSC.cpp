/*****************************************************************************
    System Name : TVoutColor_NTSC
    File Name   : INT_SP_FSC.cpp
    Content     : 
    Version     : 0.0
    CPU board   : Arduino UNO/Duemilanove
    Compiler    : Arduino 1.0.4
    History     : 2013/10/04
*****************************************************************************/
/*----------------------------------------------------------------------------
;  Copyright (C) 2013 Masami Watanabe
;
;  This program is free software; you can redistribute it and/or modify it
;  under the terms of the GNU General Public License as published by the Free
;  Software Foundation; either version 3 of the License, or (at your option)
;  any later version.
;
;  This program is distributed in the hope that it will be useful, but
;  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
;  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
;  for more details.
;
;  You should have received a copy of the GNU General Public License along
;  with this program. If not, see <http://www.gnu.org/licenses/>.
;---------------------------------------------------------------------------*/
;/*=========================================================================*/
;/* Includes                                                                */
;/*=========================================================================*/
#include "defSYS.h"
#include "defINT.h"

;/*==========================================================================*/
;/* Program                                                                  */
;/*==========================================================================*/

/*----- Memo ------------------------------------------------------------------

 ●C言語から呼び出されるアセンブラ関数
    r0/r18-25/X/Z   自由に使用可能
    ZH :R31
    ZL :R30
    XH :R27
    XL :R26
    
    r2-17/Y(r1)     変更する時は保存、復帰

 ●引数の渡し方
    r8～r25が使用される。レジスタ2個ずつセットになっていて9セット使える。
    大きな番号のレジスタペアから順番に使われる。
    ZH :R31     IJM時の飛び先間接指定
    ZL :R30
    
    -----------------------------------------------------------------------
    rjmp    2byte   2cycle  jump enable -> PC -2047WORD/PC +2048WORD
    jmp     4byte   3cycle  jump enable -> 128kbyte
    


    r26     H-Sync [0](-40IRE)  COLBST0 [7](0IRE)       COL_xx0
    r27                         COLBST1 [3](-20IRE)     COL_xx1
    r30                         COLBST2 [7](0IRE)       COL_xx2
    r31                         COLBST3 [11](+20IRE)    COL_xx3
    
    r20     work        loop counter
    
    r21     argument %5 Signal Data at 270degree    
    r22     argument %4 Signal Data at 180degree
    r23     argument %3 Signal Data at 90degree
    r24     argument %2 Signal Data at 0degree
    
    r25     argument %1 Display Mode 0:out, 1:in Frame, 2:V-sync

    r26     XL
    r27     XH
    r30     ZL
    r31     ZH
----------------------------------------------------------------------------*/

#define OutBurst\
        "out 0x08,r26\n\t"\
        "out 0x08,r27\n\t"\
        "out 0x08,r30\n\t"\
        "out 0x08,r31\n\t"\
        
#define OutBlack\
        "out 0x08,r26\n\t"\
        "out 0x08,r26\n\t"\
        "out 0x08,r26\n\t"\
        "out 0x08,r26\n\t"\
        
#define OutColor\
        "out 0x08,r24\n\t"\
        "out 0x08,r23\n\t"\
        "out 0x08,r22\n\t"\
        "out 0x08,r21\n\t"\

void CINT::SP_FSC( UB Mode, UB Sig0, UB Sig90, UB Sig180, UB Sig270 )
{
    __asm__ __volatile(
        "mov r25,%0\n\t"        // r25:Mode                             |
        "mov r24,%1\n\t"        // r24:Sig_0deg                         |
        "cpi r25,2\n\t"         // V-sync timing?   1cycle              |
        "brne NEXT\n\t"         // if not V-sync    1cycle/2cycle       |
        "jmp EXIT3\n\t"         // now V-sync
"NEXT:"
        "ldi r26,7\n\t"         // COLBST0                              |
        "out 0x08,r18\n\t"      // 0IRE                                     |   1
        "ldi r27,3\n\t"         // COLBST1                                  |   2
        "ldi r30,7\n\t"         // COLBST2                                  |   3
        "ldi r31,11\n\t"        // COLBST3                                  |   4
        "mov r23,%2\n\t"        // r23:Sig_90deg                            |   5
        "mov r22,%3\n\t"        // r22:Sig_180deg                           |   6
        "mov r21,%4\n\t"        // r21:Sig_270deg                           |   7
//      "nop \n\t"              //                                          |   8
//      "nop \n\t"              //                                          |   9
        "cbi 0x0B,2\n\t"        // for debug trigger PORTD.2                |   8,9
        
        OutBurst                // No.1 Color Burst                        --
        OutBurst                // No.2                                    --
        OutBurst                // No.3                                    --
        OutBurst                // No.4                                    --
        OutBurst                // No.5                                    --
        OutBurst                // No.6                                    --
        OutBurst                // No.7                                    --
        OutBurst                // No.8                                    --
        OutBurst                // No.9                                    --
        "out 0x08,r26\n\t"      // 0IRE                                     |   1
        
        "ldi r20,6\n\t"         //                                          |   2
"BP_LOOP:"                      // for Back Porch delay
        "dec r20\n\t"           // 1cycle                                  ||
        "brne BP_LOOP\n\t"      // 1/2      (1+2)*5+(1+1)=17               ||   19
        "ldi r26,7\n\t"         // 7:0IRE                                   |   20
        "cpi r25,0\n\t"         // r25:Mode         1cycle                  |   21
        "brne DISP\n\t"         //if display frame  1cycle/2cycle           |   22/23
        "jmp EXIT\n\t"          //out of frame then exit
"DISP:"
        "nop \n\t"              //                                          |   24
        OutBlack                //                                          |   25
        OutBlack
        OutBlack
        OutBlack
        OutBlack
        OutBlack
        OutBlack
        OutBlack
        OutBlack
//      OutBlack
        "nop \n\t"
        "nop \n\t"
        "sbi 0x0B,2\n\t"        // for debug trigger PORTD.2
        
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor
        OutColor

        
"EXIT:" 

"EXIT2:"    
        "out 0x08,r26\n\t"      // 0IRE
"EXIT3:"
        :
        : "r"(Mode) ,"r"(Sig0) ,"r"(Sig90),"r"(Sig180) ,"r"(Sig270)
        :
    );

}



