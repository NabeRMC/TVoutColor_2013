/*****************************************************************************
    System Name : TVoutColor_NTSC
    File Name   : CSL_various.cpp
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
#define CSL_INCLUDE
#include "defSYS.h"
#include "defCSL.h"
#include "defINT.h"

/*==========================================================================*/
/*  Program                                                                 */
/*==========================================================================*/
CCSL::CCSL()
{
    Ini();
}

void CCSL::Ini()
{
//    clear_screen();
}


/*  ----------------------------------------------------
    -   Clear Screen                                    -
    -----------------------------------------------------   */
void CCSL::clear_screen()
{
    int i;
    for( i = 0; i < TXT_SIZE; i++ ){
        vram_data[i] = 0x20;
    }
}


/*  ----------------------------------------------------
    -   Set Cursor                                     -
    -----------------------------------------------------   */
UB CCSL::set_cursor( UB x, UB y)
{
    if( (x>=FL_COL_MAX_TXT)||(y>=ROW_MAX) ){
        return( EOF );
    }
    else{
        cursor_x = x;
        cursor_y = y;
    }
}


/*  ----------------------------------------------------
    -   Put_Char with posion argument                   -
    -----------------------------------------------------   */

UB CCSL::put_char( UB c )
{
    UB i;
    
    if( c==0x0D ){              /* 0x0D : CR    */
        cursor_x = 0;
    }
    else if( c==0x0A ){         /* 0x0A : NL    */
        if( cursor_y < 13 ){    /* not line end */
            cursor_x = 0;
            cursor_y++;
        }
        else{                   /* end line     */
            for( i=0 ; i< FL_COL_MAX_TXT*(ROW_MAX-1) ; i++ ){
                vram_data[i] = vram_data[i+FL_COL_MAX_TXT];
            }
        }
    }
    else{
        if( (cursor_x == (FL_COL_MAX_TXT-1)) && (cursor_y==(ROW_MAX-1)) ){
            for( i=0; i< (FL_COL_MAX_TXT*ROW_MAX-1); i++ ){
                vram_data[i] = vram_data[i+1];
            }
            vram_data[FL_COL_MAX_TXT*ROW_MAX-1] = c;
        }
        else{
            vram_data[FL_COL_MAX_TXT*cursor_y + cursor_x] = c;
            cursor_x++;
            if(cursor_x >= FL_COL_MAX_TXT ){
                cursor_x = 0;
                cursor_y++;
                if(cursor_y >=ROW_MAX){
                    cursor_y = ROW_MAX-1;
                }
            }
        }
    }

    return(c);
}


/*  ----------------------------------------------------
    -   Put_Char with posion argument                   -
    -----------------------------------------------------   */
UB CCSL::put_char( UB x, UB y, UB c )
{
    UH line,column,row;
    UH row_top,line_top;
    UH data_row_top;
    UH tmp1,tmp2,tmp3;
    UH offset;
    
    if( (c > 0x7F)||(x >=FL_COL_MAX_TXT)||(y >= ROW_MAX) ){
        return( EOF );
    }
    else{
        vram_data[FL_COL_MAX_TXT*y+x] = c;
        offset = FL_COL_MAX_TXT*y+x;
        data_row_top = y * FL_COL_MAX_TXT;
        row_top = y * COL_MAX_TXT * 7;
        return( 0 );
    }
}

/*  ----------------------------------------------------
    -   Print                                           -
    -----------------------------------------------------   */
void CCSL::print(const char *str)
{
    while(*str){
        put_char(*str++);
    }
}


/*  ----------------------------------------------------
    -   set font code to V-RAM                          -
    -----------------------------------------------------   */
void CCSL::SetVram()
{
    UH line,column,row;
    UH row_top,line_top;
    UH data_row_top;
    UH tmp1,tmp2,tmp3;
    UB col_evn, col_odd;
    
    
    UH i,j,k;
    
    /* --- Block Display MOde --------------------------------------------- */
    j = 0;
    k = COL_MAX_BLK*ROW_MAX_BLK;

    if( UB_CMD_SetVram == BLOCK_MODE ){
        P_DBG2_ON;
                                                
        for( i = 0; i < TXT_SIZE; i++ ){
            if( (i%2) == 0 ){
                vram_line[j] = vram_data[i];
                j++;
            }
            else{
                vram_line[k] = vram_data[i];
                k++;
            }
        }
        
        P_DBG2_OFF;    
    }
    
    
    UB_CMD_SetVram = 0;
        
}




/*  ----------------------------------------------------
    -   Set_Line_Color                                  -
    -----------------------------------------------------   */
UB CCSL::set_line_color( UB line, UB color, UB odd_even )
{
    if( (line >= ROW_MAX)||(color >=8) ){
        return( EOF );
    }
    else if( odd_even == 0 ){
        UB_ColorN[line] = color;
    }
    else{
        UB_ColorN_ODD[line] = color;
    }
    return( 0 );
    
}




