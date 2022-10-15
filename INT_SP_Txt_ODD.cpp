/*****************************************************************************
    System Name : TVoutColor_NTSC
    File Name   : INT_SP_Txt_ODD.cpp
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
    
    r0      MUL result low
    r1      MUL result  high

    r18     H-Sync [0](-40IRE)  COLBST0 [7](0IRE)       COL_xx0
    r19                         COLBST1 [3](-20IRE)     COL_xx1
    r20                         COLBST2 [7](0IRE)       COL_xx2
    r21                         COLBST3 [11](+20IRE)    COL_xx3
    
    r22     work        loop counter
    r23     0IRE    7   Color Black
    r24     argument %2 Select Color
    r25     argument %1 Display Mode 0:out, 1:in Frame, 2:V-sync
    r26(XL) argument %0L
    r27(XH) argument %0H
    
    r30     ZL
    r31     ZH
----------------------------------------------------------------------------*/
#define OutP\
        "out 0x08,r18\n\t"\
        "out 0x08,r19\n\t"\
        "out 0x08,r20\n\t"\
        "out 0x08,r21\n\t"\

#define OutB\
        "out 0x08,r23\n\t"\
        "out 0x08,r23\n\t"\
        "out 0x08,r23\n\t"\
        "out 0x08,r23\n\t"\



#define OutPixel\
        "out 0x08,r18\n\t"\
        "out 0x08,r19\n\t"\
        "out 0x08,r20\n\t"\
        "out 0x08,r21\n\t"\

#define OutBlack\
        "out 0x08,r23\n\t"\
        "out 0x08,r23\n\t"\
        "out 0x08,r23\n\t"\
        "out 0x08,r23\n\t"\

#define OutBurst\
        "out 0x08,r18\n\t"\
        "out 0x08,r19\n\t"\
        "out 0x08,r20\n\t"\
        "out 0x08,r21\n\t"\
        
#define SetColRed\
        "ldi r18,24\n\t"\
        "ldi r19,10\n\t"\
        "ldi r20,2\n\t"\
        "ldi r21,16\n\t"\
        
#define SetColGrn\
        "ldi r18,9\n\t"\
        "ldi r19,13\n\t"\
        "ldi r20,27\n\t"\
        "ldi r21,23\n\t"\
        
#define SetColBlu\
        "ldi r18,8\n\t"\
        "ldi r19,18\n\t"\
        "ldi r20,12\n\t"\
        "ldi r21,2\n\t"\
        
#define SetColMag\
        "ldi r18,24\n\t"\
        "ldi r19,20\n\t"\
        "ldi r20,6\n\t"\
        "ldi r21,10\n\t"\
        
#define SetColCyn\
        "ldi r18,9\n\t"\
        "ldi r19,23\n\t"\
        "ldi r20,31\n\t"\
        "ldi r21,17\n\t"\
        
#define SetColYel\
        "ldi r18,25\n\t"\
        "ldi r19,15\n\t"\
        "ldi r20,21\n\t"\
        "ldi r21,31\n\t"\

#define SetColWhi\
        "ldi r18,25\n\t"\
        "ldi r19,25\n\t"\
        "ldi r20,25\n\t"\
        "ldi r21,25\n\t"\
        
        
#define SetColBlk\
        "ldi r18,7\n\t"\
        "ldi r19,7\n\t"\
        "ldi r20,7\n\t"\
        "ldi r21,7\n\t"\


void CINT::SP_Txt_ODD( UH AddrGRP, UB Mode, UB Color )
{
    __asm__ __volatile(
        "mov r24,%2\n\t"        // r24:select color
        "mov r25,%1\n\t"        //                                          |
        "ldi r18,0\n\t"         // -40IRE                                   |           //V-Sync
        "out 0x08,r18\n\t"      // output H-Sync level (-40RE/0V)       +---+   //H-Synch 4.7us:67cycle
        "cpi r25,2\n\t"         // V-sync timing?   1cycle              |       1       1
        "brne NEXT\n\t"         // if not V-sync    1cycle/2cycle       |       2,3     1
        "jmp EXIT3\n\t"         // now V-sync
"NEXT:"
        "ldi r23,7\n\t"         // 0IRE                                 |       4
        "ldi r18,7\n\t"         // COLBST0                              |       5
        "ldi r19,3\n\t"         // COLBST1                              |       6
        "ldi r20,7\n\t"         // COLBST2                              |       7
        "ldi r21,11\n\t"        // COLBST3                              |       8
        "nop\n\t"               //                                      |       9
        "ldi r22,19\n\t"        // loop count                           |       10
"HS_LOOP:"                      // for H-Sync level keep
        "dec r22\n\t"           // 1cycle                              ||
        "brne HS_LOOP\n\t"      // 2/1      (1+2)*18+(1+1) = 56        ||       66
        
        "out 0x08,r23\n\t"      // 0IRE                                     |   1
        "out 0x08,r23\n\t"      // 0IRE                                     |   2
        "out 0x08,r23\n\t"      // 0IRE                                     |   3
        "out 0x08,r23\n\t"      // 0IRE                                     |   4
        "out 0x08,r23\n\t"      // 0IRE                                     |   5
        "out 0x08,r23\n\t"      // 0IRE                                     |   6

        "push r1\n\t"           //                                          |   7
        "push r16\n\t"          //                                          |   8
        "push r17\n\t"          //                                          |   9
        
        OutBurst                // No.1 Color Burst                        --
        OutBurst                // No.2                                    --
        OutBurst                // No.3                                    --
        OutBurst                // No.4                                    --
        OutBurst                // No.5                                    --
        OutBurst                // No.6                                    --
        OutBurst                // No.7                                    --
        OutBurst                // No.8                                    --
        OutBurst                // No.9                                    --
        
        "ldi r22,6\n\t"         //                                          |   1
"BP_LOOP:"                      // for Back Porch delay
        "dec r22\n\t"           // 1cycle                                  ||
        "brne BP_LOOP\n\t"      // 1/2      (1+2)*5+(1+1)=17               ||   18
        "ldi r23,7\n\t"         // 7:0IRE                                   |   19
        "cpi r25,0\n\t"         // r25:Mode         1cycle                  |   20
        "brne DISP\n\t"         //if display frame  1cycle/2cycle           |   21/22
        "jmp EXIT\n\t"          //out of frame then exit
"DISP:"
        "nop \n\t"              //                                          |   23
        "nop \n\t"              //                                          |   24
        OutBlack                //                                          |   25
        OutBlack
        OutBlack
        OutBlack
        OutBlack
        OutBlack
        OutBlack
        
        OutBlack                // for ODD routine
        OutBlack                //
        OutBlack                //
        OutBlack                //
        OutBlack                //
        OutBlack                //
        
        "ldi r30,5\n\t"         // select table 5data number(WORD)  1       1
        "mul r24,r30\n\t"       //                                  2       2,3
        "mov r30,r0\n\t"        // r30(ZL) <- r0 result low         1       4
        "mov r31,r1\n\t"        // r31(ZH) <- r1 result high        1       5
        
        "addr_top = . +14\n\t"
        "ldi r16,lo8(addr_top)\n\t" //  2byte   1cycle  1,2                 6
        "ldi r17,hi8(addr_top)\n\t" //  2byte   1cycle  3,4                 7
        "lsr r17\n\t"               //  2byte   1cycle  5,6                 8
        "ror r16\n\t"               //  2byte   1cycle  7,8                 9
        "add r30,r16\n\t"           //  2byte   1cycle  9,19                10
        "adc r31,r17\n\t"           //  2byte   1cycle  11,12               11
        "ijmp\n\t"                  //  2byte   2cycle  13,14               16,17
        
"SELECT_COLOR:"
        SetColWhi               //  4   8byte                               18,19,20,21
        "rjmp   EX_SCOLOR\n\t"  //  2   2byte                               22,23
        SetColGrn               //  4   8byte
        "rjmp   EX_SCOLOR\n\t"  //  2   2byte
        SetColBlu               //  4   8byte
        "rjmp   EX_SCOLOR\n\t"  //  2   2byte
        SetColMag               //  4   8byte
        "rjmp   EX_SCOLOR\n\t"  //  2   2byte
    
        SetColCyn               //  4   8byte
        "rjmp   EX_SCOLOR\n\t"  //  2   2byte
        SetColYel               //  4   8byte
        "rjmp   EX_SCOLOR\n\t"  //  2   2byte
        SetColRed               //  4   8byte
        "rjmp   EX_SCOLOR\n\t"  //  2   2byte
        SetColBlk               //  4   8byte
        "rjmp   EX_SCOLOR\n\t"  //  2   2byte
"EX_SCOLOR:"
        
//      "ldi r22,9\n\t"         //  1 8文字ぐらいが限界か？                 24
        "ldi r22,12\n\t"         //  1 (COL_MAX+1)とすること                 24
"LOOP_OUTPUT:"
        
        "nop \n\t"
        "nop \n\t"
        "nop \n\t"
        "nop \n\t"
        
        "nop \n\t"              //  1                                       25          5
        "nop \n\t"              //  1                                       26          6
        "nop \n\t"              //  1                                       27          7
        "dec r22\n\t"           //  1                                       28          8
        "brne OUTPUT_SIG\n\t"   //  1/2                                     29,30       9,10
        "jmp EX_LOOP_OUTPUT\n\t"
        
"OUTPUT_SIG:"
        "ld  r0,x+\n\t"         //  1                                       31          11
        "ldi r30,23\n\t"        //  1 select table xdata number(WORD)       32          12
        "mul r0,r30\n\t"        //  2                                       33,34       13,14
        "mov r30,r0\n\t"        // r30(ZL) <- r0 result low         1       35          15
        "mov r31,r1\n\t"        // r31(ZH) <- r1 result high        1       36          16
        "addr_top = . +14\n\t"
        "ldi r16,lo8(addr_top)\n\t" //  2byte   1cycle  1,2                 37          17
        "ldi r17,hi8(addr_top)\n\t" //  2byte   1cycle  3,4                 38          18
        "lsr r17\n\t"               //  2byte   1cycle  5,6                 39          19
        "ror r16\n\t"               //  2byte   1cycle  7,8                 40          20
        "add r30,r16\n\t"           //  2byte   1cycle  9,19                41          21
        "adc r31,r17\n\t"           //  2byte   1cycle  11,12               42          22
        "ijmp\n\t"                  //  2byte   2cycle  13,14               43,44       23,24
        
"DATA0:"
        OutBlack                //  4   8byte
        OutBlack                //  4   8byte
        OutBlack                //  4   8byte
        OutBlack                //  4   8byte
        OutBlack                //  4   8byte
        "out 0x08,r23\n\t"      //  1   2byte   0IRE                            1
        "jmp LOOP_OUTPUT\n\t"   //  3   4byte                                   2,3,4

"DATA1:"
        OutBlack
        OutBlack
        OutBlack
        OutBlack
        OutPixel
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"
        
"DATA2:"
        OutBlack
        OutBlack
        OutBlack
        OutPixel
        OutBlack
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"
        
"DATA3:"
        OutBlack
        OutBlack
        OutBlack
        OutPixel
        OutPixel
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"
        
"DATA4:"
        OutBlack
        OutBlack
        OutPixel
        OutBlack
        OutBlack
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"

"DATA5:"
        OutB
        OutB
        OutP
        OutB
        OutP
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"

"DATA6:"
        OutB
        OutB
        OutP
        OutP
        OutB
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"

"DATA7:"
        OutB
        OutB
        OutP
        OutP
        OutP
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"

"DATA8:"
        OutB
        OutP
        OutB
        OutB
        OutB
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"
        
"DATA9:"
        OutB
        OutP
        OutB
        OutB
        OutP
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"

"DATA10:"
        OutB
        OutP
        OutB
        OutP
        OutB
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"
        

"DATA11:"
        OutB
        OutP
        OutB
        OutP
        OutP
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"

"DATA12:"
        OutB
        OutP
        OutP
        OutB
        OutB
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"
        
"DATA13:"
        OutB
        OutP
        OutP
        OutB
        OutP
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"

"DATA14:"
        OutB
        OutP
        OutP
        OutP
        OutB
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"
        
"DATA15:"
        OutB
        OutP
        OutP
        OutP
        OutP
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"

"DATA16:"
        OutPixel
        OutBlack
        OutBlack
        OutBlack
        OutBlack
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"

"DATA17:"
        OutPixel
        OutBlack
        OutBlack
        OutBlack
        OutPixel
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"
        
"DATA18:"
        OutPixel
        OutBlack
        OutBlack
        OutPixel
        OutBlack
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"
        
"DATA19:"
        OutPixel
        OutBlack
        OutBlack
        OutPixel
        OutPixel
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"
        
"DATA20:"
        OutPixel
        OutBlack
        OutPixel
        OutBlack
        OutBlack
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"

"DATA21:"
        OutP
        OutB
        OutP
        OutB
        OutP
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"

"DATA22:"
        OutP
        OutB
        OutP
        OutP
        OutB
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"

"DATA23:"
        OutP
        OutB
        OutP
        OutP
        OutP
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"

"DATA24:"
        OutP
        OutP
        OutB
        OutB
        OutB
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"
        
"DATA25:"
        OutP
        OutP
        OutB
        OutB
        OutP
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"

"DATA26:"
        OutP
        OutP
        OutB
        OutP
        OutB
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"
        

"DATA27:"
        OutP
        OutP
        OutB
        OutP
        OutP
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"

"DATA28:"
        OutP
        OutP
        OutP
        OutB
        OutB
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"
        
"DATA29:"
        OutP
        OutP
        OutP
        OutB
        OutP
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"

"DATA30:"
        OutP
        OutP
        OutP
        OutP
        OutB
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"
        
"DATA31:"
        OutP
        OutP
        OutP
        OutP
        OutP
        "out 0x08,r23\n\t"
        "jmp LOOP_OUTPUT\n\t"
        
"EX_LOOP_OUTPUT:"

"EXIT:" 
        "pop r17\n\t"
        "pop r16\n\t"       
        "pop r1\n\t"        
        
"EXIT2:"    
        "out 0x08,r23\n\t"      // 0IRE
"EXIT3:"
        :
        : "x"(AddrGRP) ,"r"(Mode) ,"r"(Color)
        :
    );

}



