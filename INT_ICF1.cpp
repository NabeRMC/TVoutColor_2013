/*****************************************************************************
    System Name : TVoutColor_NTSC
    File Name   : INT_ICF1.cpp
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
#include "defSYS.h"
#include "defCRT.h"
#include "defINT.h"
#include "defCSL.h"

PROGMEM const UB CINT::cg_code[ (0x7F +1)*8 ] = { 
#include "CG_NTSC_20130603.h"
};


/*==========================================================================*/
/*  Program                                                                 */
/*==========================================================================*/
/*  ----------------------------------------------------
    -   function pointer                                -
    ----------------------------------------------------*/
void ( CINT::*TBL_int_icf1[] )(void) = {
    &CINT::Int_Txt,                 /*  0                                   */
    &CINT::Int_Txt_ODD,             /*  1                                   */
    &CINT::Int_Txt_B,               /*  2   Character Even Column           */
    &CINT::Int_Txt_B_ODD,           /*  3   Charavter Odd  Column           */
    &CINT::Int_Txt_C,               /*  4   Block Even Column               */
    &CINT::Int_Txt_C_ODD,           /*  5   Block Odd  Column               */
    &CINT::Int_FSC,                 /*  6   Full Screen                     */
    
#ifdef LCD_Display
    &CINT::Int_Txt_B_2,             /*  7   Character Even Column           */
    &CINT::Int_Txt_B_ODD_2,         /*  8   Charavter Odd  Column           */
#endif
    
};

void CINT::ExecFunc( UB nIndex )
{
    (this->*TBL_int_icf1[nIndex])();
};


/*----------------------------------------------------------------------------
    interrupt ICF1
*---------------------------------------------------------------------------*/
CINT    objINT;

ISR (TIMER1_CAPT_vect)
{
    objINT.FitDelay( TCNT1L );      /* 割り込み遅延ばらつきの合わせ込み     */
                    /* Compensation of the variration in delay of interrupt */
    PORTC = 0;                      /* -40IRE data    need at V-sync        */
    
    objINT.ExecFunc( UB_ModePTN );
}


/*  ----------------------------------------------------
    -   index:0 Text Even column                        -
    -----------------------------------------------------   */
void CINT::Int_Txt( void )
{
    SP_Txt( (UH)(UH_AddrDataNow), UB_ModePLS, UB_Color );
    
    P_DBG2_OFF;
    
    UH_hline++;
    if( UH_hline == V_SYNC_END ){       /* end of timing of V-sync pulse    */
        OCR1A = CRT_OCR1A_HS;           
        UB_ModePLS = FRM_OFF;
        P_DBG1_OFF;
    }       
    else if( (UH_hline >= V_FRM_TOP) && (UH_hline < V_FRM_END) ){
        
        if( UH_hline < V_TXT_END ){
            UB_cg_line = (UB_scanline & 0x0F); /* 0 - 15                    */
            if( UB_cg_line < 7 ){
                UH_AddrDataNow += COL_MAX;
                UB_ModePLS = FRM_ON;
            }
            else if(UB_cg_line == 9 ){
                UB_Color = UB_ColorN[UB_row];
                UB_row++;
                UB_ModePLS = FRM_OFF;
            }
            else{
                UB_ModePLS = FRM_OFF;
            }           
        UB_scanline++;
        }
        else{
            UB_ModePLS = FRM_OFF;
        }
    }
    else if( UH_hline == H_LINE_END ){
        UB_ModePLS = FRM_OFF;
        UH_hline = 0;
        UB_scanline = 0;
        JobAsy();
        if( UB_ModePTN_BF >=2 ){
            UB_ModePTN = UB_ModePTN_BF;
        }
        else{
            UB_ModePTN = 1;
        }
    }
    else if( UH_hline == V_SYNC_START ){     /* start of timing of V-sync   */
        OCR1A  = CRT_OCR1A_VS;
        TCCR1A = CRT_TCCR1A;
        UB_ModePLS = FRM_OFF;
        P_DBG1_ON;
        UH_AddrDataNow = UH_AddrData_n;
        UB_row = 0;
    }
    if( UH_hline == V_START_VRAM ){
        if( UB_CMD_SetVram ==0 ){
            UB_CMD_SetVram = 0x01;
        }
    }
}


/*  ----------------------------------------------------
    -   index:1 Text Odd column                        -
    -----------------------------------------------------   */
void CINT::Int_Txt_ODD( void )
{
    SP_Txt_ODD( (UH)(UH_AddrDataNow), UB_ModePLS, UB_Color );
    
    P_DBG2_OFF; 

    UH_hline++;
    if( UH_hline == V_SYNC_END ){       /* end of timing of V-sync pulse    */
        OCR1A = CRT_OCR1A_HS;
        UB_ModePLS = FRM_OFF;
        P_DBG1_OFF;
    }       
    else if( (UH_hline >= V_FRM_TOP) && (UH_hline < V_FRM_END) ){
        if( UH_hline < V_TXT_END ){
            UB_cg_line = (UB_scanline & 0x0F); /* 0 - 15                    */
            if( UB_cg_line < 7 ){
                UH_AddrDataNow += COL_MAX;
                UB_ModePLS = FRM_ON;
            }
            else if(UB_cg_line == 9 ){
                UB_Color = UB_ColorN_ODD[UB_row];
                UB_row++;
                UB_ModePLS = FRM_OFF;
            }
            else{
                UB_ModePLS = FRM_OFF;
            }           
        UB_scanline++;
        }
        else{
            UB_ModePLS = FRM_OFF;
        }
    }
    else if( UH_hline == H_LINE_END ){
        UB_ModePLS = FRM_OFF;
        UH_hline = 0;
        UB_scanline = 0;
        JobAsy();
        UB_ModePTN = 0;
    }
    else if( UH_hline == V_SYNC_START ){    /* start of timing of V-sync    */
        OCR1A  = CRT_OCR1A_VS;
        TCCR1A = CRT_TCCR1A;
        UB_ModePLS = FRM_OFF;
        P_DBG1_ON;
        UH_AddrDataNow = UH_AddrData_n;
        UB_row = 0;
    }
    if( UH_hline == V_START_VRAM ){
        if( UB_CMD_SetVram == 0 ){ 
            UB_CMD_SetVram = 0x02;
        }
    }   
    P_DBG2_ON;  
}


/*  ----------------------------------------------------
    -   index:0 Text Even column                        -
    -----------------------------------------------------   */
void CINT::Int_Txt_B( void )
{
    static UB p_line = 0;
    static UB p_data = 0;
    
    SP_Txt_B( (UH)(UH_AddrDataNow), UB_ModePLS, UB_Color );
    
    UH_hline++;
    if( (UH_hline >= V_TXT_START_B) && (UH_hline < V_TXT_END_B) ){
        
        if( UB_cg_line <= 6 ){
            p_line = UB_cg_line * COL_MAX_TXT;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[0 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[2 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[4 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[6 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[8 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[10 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[12 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[14 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[16 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[18 +p_data])*8+UB_cg_line] ); p_line++;
            
            if( UB_cg_line == 6 ){
                UB_ModePLS = FRM_ON;
            }
            
        }
        else if( UB_cg_line == 13 ){
            UB_cg_line = 0xFF;
            UB_ModePLS = FRM_OFF;
            UH_AddrDataNow = UH_AddrData_n;
            UB_row++;
            p_data = FL_COL_MAX_TXT * UB_row;
            UB_Color = UB_ColorN[UB_row];
        }
        else{
            UH_AddrDataNow += COL_MAX_TXT;
        }
        UB_cg_line++;
        
    }
    
    else if( UH_hline == V_SYNC_END ){       /* end of timing of V-sync pulse    */
        OCR1A = CRT_OCR1A_HS;           
        UB_ModePLS = FRM_OFF;
        UB_Color = UB_ColorN[0];
        P_DBG1_OFF;
    }
    else if( UH_hline == H_LINE_END ){
        UH_hline = 0;
        UB_cg_line = 0;
        p_line = 0;
        p_data = 0;
        JobAsy();

#ifdef LCD_Display
        UB_ModePTN = 7;
#else
        UB_ModePTN = 3;
#endif
        
    }
    else if( UH_hline == V_SYNC_START ){     /* start of timing of V-sync   */
        OCR1A  = CRT_OCR1A_VS;
        TCCR1A = CRT_TCCR1A;
        UB_ModePLS = FRM_VSYNC;     
        UH_AddrDataNow = UH_AddrData_n;
        UB_row = 0;
        P_DBG1_ON;
    }
    else if( UH_hline == V_TXT_END_B ){
        UB_ModePLS = FRM_OFF;
    }
    
}


/*  ----------------------------------------------------
    -   index:1 Text Odd column                        -
    -----------------------------------------------------   */
void CINT::Int_Txt_B_ODD( void )
{
    static UB p_line = 0;
    static UB p_data = 0;
    
    SP_Txt_B_ODD( (UH)(UH_AddrDataNow), UB_ModePLS, UB_Color ); 

    UH_hline++;
    if( (UH_hline >= V_TXT_START_B) && (UH_hline < V_TXT_END_B) ){

        if( UB_cg_line <= 6 ){
            p_line = UB_cg_line * COL_MAX_TXT;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[1 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[3 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[5 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[7 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[9 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[11 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[13 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[15 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[17 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[19 +p_data])*8+UB_cg_line] ); p_line++;
            
            if( UB_cg_line == 6 ){
                UB_ModePLS = FRM_ON;
            }           
            
        }
        else if( UB_cg_line == 13 ){
            UB_cg_line = 0xFF;
            UB_ModePLS = FRM_OFF;
            UH_AddrDataNow = UH_AddrData_n;
            UB_row++;
            p_data = FL_COL_MAX_TXT * UB_row;
            UB_Color = UB_ColorN_ODD[UB_row];
        }
        else{
            UH_AddrDataNow += COL_MAX_TXT;
        }
        UB_cg_line++;
        
    }
    
    else if( UH_hline == V_SYNC_END ){       /* end of timing of V-sync pulse    */
        OCR1A = CRT_OCR1A_HS;           
        UB_ModePLS = FRM_OFF;
        UB_Color = UB_ColorN_ODD[0];
        P_DBG1_OFF;
    }
    else if( UH_hline == H_LINE_END ){
        UH_hline = 0;
        UB_cg_line = 0;
        p_line = 0;
        p_data = 0;
        JobAsy();
        

#ifdef LCD_Display
        UB_ModePTN = 8;
#else
        UB_ModePTN = 2;
#endif      
        
    }
    else if( UH_hline == V_SYNC_START ){     /* start of timing of V-sync   */
        OCR1A  = CRT_OCR1A_VS;
        TCCR1A = CRT_TCCR1A;
        UB_ModePLS = FRM_VSYNC;     
        UH_AddrDataNow = UH_AddrData_n;
        UB_row = 0;
        P_DBG1_ON;
    }
    else if( UH_hline == V_TXT_END_B ){
        UB_ModePLS = FRM_OFF;
    }

}


/*  ----------------------------------------------------
    -   index:0 Text Even column                        -
    -----------------------------------------------------   */
void CINT::Int_Txt_C( void )
{
    SP_Txt_C( (UH)(UH_AddrDataNow), UB_ModePLS, UB_Color );
    
    UH_hline++;
    if( (UH_hline >= V_TXT_ST_C) && (UH_hline < V_TXT_END_C-1 ) ){
        UB_scanline++;
        UB_cg_line = (UB_scanline &0x07);   /* 0 - 7                    */
        if(UB_cg_line == 7 ){
            UB_row++;
            UH_AddrDataNow += COL_MAX_BLK;
            UB_Color = UB_ColorN[UB_row];
        }
    }
    else if( UH_hline == (V_TXT_ST_C-1) ){  //ここでONした方が上の処理時間を減らせる
        UB_ModePLS = FRM_ON;
    }
    else if( UH_hline == V_TXT_END_C-1 ){
        UB_ModePLS = FRM_OFF;           
    }
    else if( UH_hline == V_SYNC_END ){       /* end of timing of V-sync pulse    */
        OCR1A = CRT_OCR1A_HS;           
        UB_ModePLS = FRM_OFF;               //FRM_OFF ← FRM_VSYNC
        UB_Color = UB_ColorN[0];
        P_DBG1_OFF;
    }
    else if( UH_hline == H_LINE_END ){
        UH_hline = 0;
        UB_scanline = 0;
        UB_cg_line = 0;
        JobAsy();
        UB_ModePTN = 5;
    }
    else if( UH_hline == V_SYNC_START ){    /* start of timing of V-sync   */
        OCR1A  = CRT_OCR1A_VS;
        TCCR1A = CRT_TCCR1A;
        UB_ModePLS = FRM_VSYNC;
        UH_AddrDataNow = UH_AddrData_n;
        UB_row = 0;
        P_DBG1_ON;      
    } 
}


/*  ----------------------------------------------------
    -   index:1 Text Odd column                        -
    -----------------------------------------------------   */
void CINT::Int_Txt_C_ODD( void )
{
    SP_Txt_C_ODD( (UH)(UH_AddrDataNow_ODD), UB_ModePLS, UB_Color );
    
    UH_hline++;
    if( (UH_hline >= V_TXT_ST_C) && (UH_hline < V_TXT_END_C-1 ) ){
        UB_scanline++;
        UB_cg_line = (UB_scanline &0x07);   /* 0 - 7                    */
        if(UB_cg_line == 7 ){
            UB_row++;
            UH_AddrDataNow_ODD += COL_MAX_BLK;
            UB_Color = UB_ColorN_ODD[UB_row];
        }
    }
    else if( UH_hline == (V_TXT_ST_C-1) ){  //ここでONした方が上の処理時間を減らせる
        UB_ModePLS = FRM_ON;
    }
    else if( UH_hline == V_TXT_END_C-1 ){
        UB_ModePLS = FRM_OFF;           
    }
    else if( UH_hline == V_SYNC_END ){       /* end of timing of V-sync pulse    */
        OCR1A = CRT_OCR1A_HS;           
        UB_ModePLS = FRM_OFF;               //FRM_OFF ← FRM_VSYNC
        UB_Color = UB_ColorN_ODD[0];
        P_DBG1_OFF;
    }
    else if( UH_hline == H_LINE_END ){
        UH_hline = 0;
        UB_scanline = 0;
        UB_cg_line = 0;
        JobAsy();
        UB_ModePTN = 4;
    }
    else if( UH_hline == V_SYNC_START ){    /* start of timing of V-sync   */
        OCR1A  = CRT_OCR1A_VS;
        TCCR1A = CRT_TCCR1A;
        UB_ModePLS = FRM_VSYNC;
        UH_AddrDataNow_ODD = UH_AddrData_n_ODD;
        UB_row = 0;
        P_DBG1_ON;
    } 
}


/*  ----------------------------------------------------
    -   index:0 Full SCreen                            -
    -----------------------------------------------------   */
void CINT::Int_FSC( void )
{
    SP_FSC( UB_ModePLS, UB_Sig1, UB_Sig2, UB_Sig3, UB_Sig4 );
    
    UH_hline++;

    if( UH_hline == (V_TXT_ST_C-1) ){
        UB_ModePLS = FRM_ON;
    }
    else if( UH_hline == V_TXT_END_C-1 ){
        UB_ModePLS = FRM_OFF;           
    }
    else if( UH_hline == V_SYNC_END ){       /* end of timing of V-sync pulse    */
        OCR1A = CRT_OCR1A_HS;           
        UB_ModePLS = FRM_OFF;               //FRM_OFF ← FRM_VSYNC
    }
    else if( UH_hline == H_LINE_END ){
        UH_hline = 0;
        JobAsy();
        UB_ModePTN = 6;
    }
    else if( UH_hline == V_SYNC_START ){    /* start of timing of V-sync   */
        OCR1A  = CRT_OCR1A_VS;
        TCCR1A = CRT_TCCR1A;
        UB_ModePLS = FRM_VSYNC;     
    } 
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef LCD_Display
/*  ----------------------------------------------------
    -   index:0 Text Even column                        -
    -----------------------------------------------------   */
void CINT::Int_Txt_B_2( void )
{
    static UB p_line = 0;
    static UB p_data = 0;
    
    SP_Txt_B( (UH)(UH_AddrDataNow), UB_ModePLS, UB_Color );
    
    UH_hline++;
    if( (UH_hline >= V_TXT_START_B) && (UH_hline < V_TXT_END_B) ){
        
        if( UB_cg_line <= 6 ){
            p_line = UB_cg_line * COL_MAX_TXT;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[0 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[2 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[4 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[6 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[8 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[10 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[12 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[14 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[16 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[18 +p_data])*8+UB_cg_line] ); p_line++;
            
            if( UB_cg_line == 6 ){
                UB_ModePLS = FRM_ON;
            }
            
        }
        else if( UB_cg_line == 13 ){
            UB_cg_line = 0xFF;
            UB_ModePLS = FRM_OFF;
            UH_AddrDataNow = UH_AddrData_n;
            UB_row++;
            p_data = FL_COL_MAX_TXT * UB_row;
            UB_Color = UB_ColorN[UB_row];
        }
        else{
            UH_AddrDataNow += COL_MAX_TXT;
        }
        UB_cg_line++;
        
    }
    
    else if( UH_hline == V_SYNC_END ){       /* end of timing of V-sync pulse    */
        OCR1A = CRT_OCR1A_HS;           
        UB_ModePLS = FRM_OFF;
        UB_Color = UB_ColorN[0];
        P_DBG1_OFF;
    }
    else if( UH_hline == H_LINE_END ){
        UH_hline = 0;
        UB_cg_line = 0;
        p_line = 0;
        p_data = 0;
        JobAsy();
        UB_ModePTN = 3;
    }
    else if( UH_hline == V_SYNC_START ){     /* start of timing of V-sync   */
        OCR1A  = CRT_OCR1A_VS;
        TCCR1A = CRT_TCCR1A;
        UB_ModePLS = FRM_VSYNC;     
        UH_AddrDataNow = UH_AddrData_n;
        UB_row = 0;
        P_DBG1_ON;
    }
    else if( UH_hline == V_TXT_END_B ){
        UB_ModePLS = FRM_OFF;
    }
    
}


/*  ----------------------------------------------------
    -   index:1 Text Odd column                        -
    -----------------------------------------------------   */
void CINT::Int_Txt_B_ODD_2( void )
{
    static UB p_line = 0;
    static UB p_data = 0;
    
    SP_Txt_B_ODD( (UH)(UH_AddrDataNow), UB_ModePLS, UB_Color ); 

    UH_hline++;
    if( (UH_hline >= V_TXT_START_B) && (UH_hline < V_TXT_END_B) ){

        if( UB_cg_line <= 6 ){
            p_line = UB_cg_line * COL_MAX_TXT;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[1 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[3 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[5 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[7 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[9 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[11 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[13 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[15 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[17 +p_data])*8+UB_cg_line] ); p_line++;
            vram_line[p_line] = pgm_read_byte( &cg_code[(UH)(vram_data[19 +p_data])*8+UB_cg_line] ); p_line++;
            
            if( UB_cg_line == 6 ){
                UB_ModePLS = FRM_ON;
            }           
            
        }
        else if( UB_cg_line == 13 ){
            UB_cg_line = 0xFF;
            UB_ModePLS = FRM_OFF;
            UH_AddrDataNow = UH_AddrData_n;
            UB_row++;
            p_data = FL_COL_MAX_TXT * UB_row;
            UB_Color = UB_ColorN_ODD[UB_row];
        }
        else{
            UH_AddrDataNow += COL_MAX_TXT;
        }
        UB_cg_line++;
        
    }
    
    else if( UH_hline == V_SYNC_END ){       /* end of timing of V-sync pulse   */
        OCR1A = CRT_OCR1A_HS;           
        UB_ModePLS = FRM_OFF;
        UB_Color = UB_ColorN_ODD[0];
        P_DBG1_OFF;
    }
    else if( UH_hline == H_LINE_END ){
        UH_hline = 0;
        UB_cg_line = 0;
        p_line = 0;
        p_data = 0;
        JobAsy();
        UB_ModePTN = 2;
    }
    else if( UH_hline == V_SYNC_START ){     /* start of timing of V-sync   */
        OCR1A  = CRT_OCR1A_VS;
        TCCR1A = CRT_TCCR1A;
        UB_ModePLS = FRM_VSYNC;     
        UH_AddrDataNow = UH_AddrData_n;
        UB_row = 0;
        P_DBG1_ON;
    }
    else if( UH_hline == V_TXT_END_B ){
        UB_ModePLS = FRM_OFF;
    }

}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif



/*  ----------------------------------------------------
    -   for fixed interval job                          -
    -----------------------------------------------------   */
void CINT::JobAsy()
{
    static UB   UBCT_33ms = 0;
    
    UBCT_33ms++;
    
    if( ( UBCT_33ms %4 ) == 0 ){
        UBf_132ms_req = 1;
    }

}


void CINT::ClearLineData(){
    UH_hline = 0;
    UB_scanline = 0;
    UB_cg_line = 0;
}


