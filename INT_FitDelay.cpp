/*****************************************************************************
    System Name : Arduino 2010
    File Name   : INT_Fitdelay.cpp
    Content     : 
    Version     : 0.0
    CPU board   : Arduino Duemilanove
    Compiler    : 
    History     :2010/03/17
*****************************************************************************/
/*----------------------------------------------------------------------------
;  Copyright (C) 2010 Masami Watanabe
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
/*==========================================================================*/
/*  Includes                                                                */
/*==========================================================================*/
#include "defSYS.h"
#include "defINT.h"

/*==========================================================================*/
/*  Program                                                                 */
/*==========================================================================*/
/*----------------------------------------------------------------------------
* Function : 
* Descr    : 
* Inputs   : 
* Outputs  : 
* Return   : 

 ●C言語から呼び出されるアセンブラ関数
    r0/r18-25/X/Z   自由に使用可能
    r2-17/Y(r1)     変更する時は保存、復帰

 ●引数の渡し方
    r8～r25が使用される。レジスタ2個ずつセットになっていて9セット使える。
    大きな番号のレジスタペアから順番に使われる。

    1/16MHz = 62.5ns/clock
    実測遅れ 2.54us 40.64

-----[C++]-------------------------------------------------------------------------
                                                             int. response MIN  [3]???
                                                -----------------------------------
00000014:   940C31AE    JMP       0x000031AE     Jump                           [3]

86:       ISR (TIMER1_CAPT_vect)
+000031AE:   921F        PUSH      R1             Push register on stack        [2]
+000031AF:   920F        PUSH      R0             Push register on stack        [2]
+000031B0:   B60F        IN        R0,0x3F        In from I/O location          [1]
+000031B1:   920F        PUSH      R0             Push register on stack        [2]
+000031B2:   2411        CLR       R1             Clear Register                [1]
+000031B3:   930F        PUSH      R16            Push register on stack        [2]
+000031B4:   931F        PUSH      R17            Push register on stack        [2]
+000031B5:   932F        PUSH      R18            Push register on stack        [2]
+000031B6:   933F        PUSH      R19            Push register on stack        [2]
+000031B7:   934F        PUSH      R20            Push register on stack        [2]
+000031B8:   935F        PUSH      R21            Push register on stack        [2]
+000031B9:   936F        PUSH      R22            Push register on stack        [2]
+000031BA:   937F        PUSH      R23            Push register on stack        [2]
+000031BB:   938F        PUSH      R24            Push register on stack        [2]
+000031BC:   939F        PUSH      R25            Push register on stack        [2]
+000031BD:   93AF        PUSH      R26            Push register on stack        [2]
+000031BE:   93BF        PUSH      R27            Push register on stack        [2]
+000031BF:   93EF        PUSH      R30            Push register on stack        [2]
+000031C0:   93FF        PUSH      R31            Push register on stack        [2]
                                                                        TOTAL   39
                                                -----------------------------------
    
88:         objINT.FitDelay( TCNT1L );            0x0084 : TCNT1L
+000031C1:   91600084    LDS       R22,0x0084     Load direct from data space   [2] /41
                                                              TCNT1L Simulation [44]
    
+000031C3:   EE04        LDI       R16,0xE4       Load immediate
+000031C4:   E011        LDI       R17,0x01       Load immediate
+000031C5:   01C8        MOVW      R24,R16        Copy register pair
+000031C6:   940E31EC    CALL      0x000031EC     Call subroutine   
---------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    asm(code : output operand list : input operand list : clobber list);
    コード部ではオペランドはパーセント文字とそれに続く数字で参照される。
    %0は初めの、そして%1は2番目のオペランド
    ISO99-C関連でアンダースコアを2つつける。
----------------------------------------------------------------------------*/


void CINT::FitDelay( UB UBdelay_time )
{

    __asm__ __volatile__(       //          29      28      27      26      25      24      23      22  
        "cpi    %0,49\n\t"      // [1]      [1/1]   [1/1]   [1/1]   [1/1]   [1/1]   [1/1]   [1/1]   [1/1]
        "breq   L49\n\t"        // [1/2]    [2/3]   [1/2]   [1/2]   [1/2]   [1/2]   [1/2]   [1/2]   [1/2]
        "cpi    %0,48\n\t"      // [1]              [1/3]   [1/3]   [1/3]   [1/3]   [1/3]   [1/3]   [1/3]
        "breq   L48\n\t"        // [1/2]            [2/5]   [1/4]   [1/4]   [1/4]   [1/4]   [1/4]   [1/4]
        "cpi    %0,47\n\t"      // [1]                      [1/5]   [1/5]   [1/5]   [1/5]   [1/5]   [1/5]
        "breq   L47\n\t"        // [1/2]                    [2/7]   [1/6]   [1/6]   [1/6]   [1/6]   [1/6]
        "cpi    %0,46\n\t"      // [1]                              [1/7]   [1/7]   [1/7]   [1/7]   [1/7]
        "breq   L46\n\t"        // [1/2]                            [2/9]   [1/8]   [1/8]   [1/8]   [1/8]
        "cpi    %0,45\n\t"      // [1]                                      [1/9]   [1/9]   [1/9]   [1/9]
        "breq   L45\n\t"        // [1/2]                                    [2/11]  [1/10]  [1/10]  [1/10]
        "cpi    %0,44\n\t"      // [1]                                              [1/11]  [1/11]  [1/11]
        "breq   L44\n\t"        // [1/2]                                            [2/13]  [1/12]  [1/12]
        "cpi    %0,43\n\t"      // [1]                                                      [1/13]  [1/13]
        "breq   L43\n\t"        // [1/2]                                                    [2/15]  [1/14]
        "cpi    %0,42\n\t"      // [1]                                                              [1/15]
        "breq   L42\n\t"        // [1/2]                                                            [2/17]
        
        "L49:\n\t"
        "nop\n\t"               // +8       +3=11
        "L48:\n\t"              //          +29=40
        "nop\n\t"               // +7               +5=12
        "L47:\n\t"              //                  +28=40
        "nop\n\t"               // +6                       +7=13
        "L46:\n\t"              //                          +27=40
        "nop\n\t"               // +5                               +9=14
        "L45:\n\t"              //                                  +26=40
        "nop\n\t"               // +4                                       +11=15
        "L44:\n\t"              //                                          +25=40
        "nop\n\t"               // +3                                               +13=16
        "L43:\n\t"              //                                                  +24=40
        "nop\n\t"               // +2                                                       +15=17
        "L42:\n\t"              //                                                          +23=40
        "nop\n\t"               // +1                                                               +17=18
                                //                                                                  +22=40
        
        :                       // インラインアセンブラから出力する値
        : "r"(UBdelay_time)     // インラインアセンブラへ引き渡すCの値
        :                       // クロバーリスト
                                // コンパイラにアセンブラ内で変更が行われたことを伝える。
                                // この部分は無視して空のままでもよい
    );

}
    
    
    
