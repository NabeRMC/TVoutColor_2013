/*****************************************************************************
    System Name : TVoutColor_NTSC
    File Name   : TVoutColor_xxxxxxxx.ino
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
#include <avr/pgmspace.h>

/*==========================================================================*/
/*                                                                          */
/*==========================================================================*/

/*                               01234567890123456789                       */
prog_char string_0[] PROGMEM =  " You can check and  ";     /* 1    */
prog_char string_1[] PROGMEM =  "adjust each color.  ";     /* 2    */
prog_char string_2[] PROGMEM =  " 0:White            ";     /* 3    */
prog_char string_3[] PROGMEM =  " 1:Green            ";     /* 4    */
prog_char string_4[] PROGMEM =  " 2:Blue             ";     /* 5    */
prog_char string_5[] PROGMEM =  " 3:Magenta          ";     /* 6    */
prog_char string_6[] PROGMEM =  " 4:Cyan             ";     /* 6    */
prog_char string_7[] PROGMEM =  " 5:Yellow           ";     /* 7    */
prog_char string_8[] PROGMEM =  " 6:Red              ";     /* 8    */
prog_char string_9[] PROGMEM =  " 7:Black            ";     /* 9    */
prog_char string_10[] PROGMEM = "up:Q,W,E,P          ";     /* 10   */
prog_char string_11[] PROGMEM = "down:A,S,D,F        ";     /* 11   */

PROGMEM const char *string_table[] =
{
    string_0,
    string_1,
    string_2,
    string_3,
    string_4,
    string_5,
    string_6,
    string_7,
    string_8,
    string_9,
    string_10,
    string_11
};


/*==========================================================================*/
/*  Program                                                                 */
/*==========================================================================*/
CSYS objSYS;
CCRT objCRT;
CCSL objCSL;
CINT IobjINT;

void Ini_PT_TXT(void);
void Ini_PT_BLK(void);
void Ini_PT_FSC(void);
void Clear_BLK(void);
void Set_TestColor_A(void);
void Set_Color( UB );
void Put_Block(void);
void Change_Color(void);
void Change_Color_Menu(void);
void Clear_Block(void);
void Disp_INV_A(void);
void Disp_INV_B(void);
void Disp_INV_C(void);
void Set_INV_A1( UB );
void Set_INV_A1toA2( UB );
void Set_INV_A2toA1( UB );
void Set_INV_B1( UB );
void Set_INV_B2( UB );
void Set_INV_C1( UB );
void Set_INV_C2( UB );
void Demo_Text_A(void);
void Set_TestColor_TXT( UB );
void Set_TestColor_TXT_ODD( UB );
void Set_FSC_Color( UB );
void AdjustColor( UB );
void PrintAdjMenu(void);
void PrintAdjMenu_CRT(void);

void setup()
{
    cli();
    objSYS.Ini();                   /* re-initialize for Arduini IDE init() */
    Ini_PT_BLK();
    randomSeed(analogRead(0));
    Serial.begin(9600);
    objSYS.IniUART();               /* for Crystal 16MHz ->14.31818NHz      */
    sei();                          /* interrupt enable                     */
}

void loop() 
{
    unsigned char   k;
    unsigned char   ReadData;

    Ini_PT_TXT();                   /* Initializatioin for Text Display     */
    Demo_Text_A();                  /* Demo Program for Text Mode           */
    objSYS.delay132( 10 );          /* Delay about 132ms * 10               */
    
    Ini_PT_BLK();                   /* Initialization for Block Display     */
    Set_TestColor_A();              /* Set Line Color                       */
    Put_Block();                    /* Put Block one by one                 */

    Change_Color();                 /* Change Block Color every about 132ms */
    Clear_Block();                  /* Clear Block at random                */
    Disp_INV_A();               /* Display Invader type A random position   */
    Disp_INV_B();               /* Display Invader type B random position   */
    Disp_INV_C();               /* Displya Invader type C random position   */

    Ini_PT_FSC();               /* Initializatioin for Full Screen display  */
    for( k = 0; k <= 6; k++ ){
        Set_FSC_Color( k );         /* change color                         */
        objSYS.delay132( 20 );      /* delay about 132ms * 20               */
    }
    PrintAdjMenu_CRT();         /* Display Menu for check color and adjust  */
    objSYS.delay132( 50 );
    PrintAdjMenu();             /* Menu send to Serial Monitor              */
    ReadData = 0;
                                /* Check Key in                             */
    while( ( ReadData!='z')&&( ReadData!='Z') ){    /* Z:exit               */
        while( Serial.available() <= 0 ){ 
            Change_Color_Menu();
        
        }   
        ReadData = Serial.read();
        
        if( (ReadData >= '0')&&(ReadData <= '7') ){ /* 0 - 7:Set Color      */
            Ini_PT_FSC();
            Set_FSC_Color(ReadData-0x30);   /* Set Color correspond key in  */
            PrintAdjMenu();         /* Menu send to Serial Monitor          */
        }
        else if( (ReadData == 0x0A)||(ReadData== 0x0D) ){   
                                    /* nothing do if 'CR' or 'LF'           */
        }
        else{
            AdjustColor(ReadData);  /* Change Color signal level            */
        }
    }

}



/*----------------------------------------------------------------------------
    Set Color for Full Screen Display
    default Color data
        
        In this project
        Color signal made from only 4 signals.
            Sig1 - at 0degree
            Sig2 - at 90degree
            Sig3 - at 180degree
            Sig4 - at 270degree
----------------------------------------------------------------------------*/
void Set_FSC_Color( UB color )
{
    switch( color ){
        case COL_WHI:
            UB_Sig1 = 25;
            UB_Sig2 = 25;
            UB_Sig3 = 25;
            UB_Sig4 = 25;
            break;
        
        case COL_GRN:
            UB_Sig1 = 9;
            UB_Sig2 = 13;
            UB_Sig3 = 27;
            UB_Sig4 = 23;
            break;
        
        case COL_BLU:
            UB_Sig1 = 8;
            UB_Sig2 = 18;
            UB_Sig3 = 12;
            UB_Sig4 = 2;
            break;
        
        case COL_MAG:
            UB_Sig1 = 24;
            UB_Sig2 = 20;
            UB_Sig3 = 6;
            UB_Sig4 = 10;
            break;
        
        case COL_CYN:
            UB_Sig1 = 9;
            UB_Sig2 = 23;
            UB_Sig3 = 31;
            UB_Sig4 = 17;
            break;
        
        case COL_YEL:
            UB_Sig1 = 25;
            UB_Sig2 = 15;
            UB_Sig3 = 21;
            UB_Sig4 = 31;
            break;
        
        case COL_RED:
            UB_Sig1 = 24;
            UB_Sig2 = 10;
            UB_Sig3 = 2;
            UB_Sig4 = 16;
            break;
        
    case COL_BLK:
            UB_Sig1 = 7;
            UB_Sig2 = 7;
            UB_Sig3 = 7;
            UB_Sig4 = 7;
            break;

    deafult:
            UB_Sig1 = 25;
            UB_Sig2 = 25;
            UB_Sig3 = 25;
            UB_Sig4 = 25;
        
    }
}


/*----------------------------------------------------------------------------
    Adjust Color for Full Screen Display            
    
        In this project
        Color signal made from only 4 signals.
            Sig1 - at 0degree
            Sig2 - at 90degree
            Sig3 - at 180degree
            Sig4 - at 270degree
----------------------------------------------------------------------------*/
void AdjustColor( UB key )
{
    if( (key=='q')||(key=='Q') ){
        UB_Sig1++;
        if( UB_Sig1 > 31 ){ 
            UB_Sig1 = 31;   
        }
    }
    else if( (key=='a')||(key=='A') ){
        UB_Sig1--;
        if( UB_Sig1 < 1 ){
            UB_Sig1 = 1;
        }
    }
    else if( (key=='w')||(key=='W') ){
        UB_Sig2++;
        if( UB_Sig2 > 31 ){ 
            UB_Sig2 = 31;   
        }
    }
    else if( (key=='s')||(key=='s') ){
        UB_Sig2--;
        if( UB_Sig2 < 1 ){
            UB_Sig2 = 1;
        }
    }   
    
    else if(( key=='e')||(key=='e') ){
        UB_Sig3++;
        if( UB_Sig3 > 31 ){ 
            UB_Sig3 = 31;   
        }
    }
    else if( (key=='d')||(key=='d') ){
        UB_Sig3--;
        if( UB_Sig3 < 1 ){
            UB_Sig3 = 1;
        }
    }
    else if( (key=='r')||(key=='r') ){
        UB_Sig4++;
        if( UB_Sig4 > 31 ){ 
            UB_Sig4 = 31;   
        }
    }
    else if( (key=='f')||(key=='f') ){
        UB_Sig4--;
        if( UB_Sig4 < 1 ){
            UB_Sig4 = 1;
        }
    }
    else{
        PrintAdjMenu();
    }
    
    Serial.print("Sig1:");
    Serial.print(UB_Sig1);
    Serial.print(" ");
    Serial.print("Sig2:");
    Serial.print(UB_Sig2);
    Serial.print(" ");  
    Serial.print("Sig3:");
    Serial.print(UB_Sig3);
    Serial.print(" ");
    Serial.print("Sig4:");
    Serial.print(UB_Sig4);
    Serial.println(""); 
    
}


/*  ----------------------------------------------------
    -   Display Menu on CRT                             -
    -----------------------------------------------------   */
void PrintAdjMenu_CRT(void)

{
    int i,k;
    unsigned char data;
    
    Ini_PT_TXT();
    UB_ColorN[0] = COL_WHI;     UB_ColorN_ODD[0] = COL_WHI;
    UB_ColorN[1] = COL_WHI;     UB_ColorN_ODD[1] = COL_WHI;
    UB_ColorN[2] = COL_WHI;     UB_ColorN_ODD[2] = COL_WHI;
    UB_ColorN[3] = COL_GRN;     UB_ColorN_ODD[3] = COL_GRN;
    UB_ColorN[4] = COL_BLU;     UB_ColorN_ODD[4] = COL_BLU;
    UB_ColorN[5] = COL_MAG;     UB_ColorN_ODD[5] = COL_MAG;
    UB_ColorN[6] = COL_CYN;     UB_ColorN_ODD[6] = COL_CYN;
    UB_ColorN[7] = COL_YEL;     UB_ColorN_ODD[7] = COL_YEL;
    UB_ColorN[8] = COL_RED;     UB_ColorN_ODD[8] = COL_RED;
    UB_ColorN[9] = COL_WHI;     UB_ColorN_ODD[9] = COL_WHI;
    UB_ColorN[10] = COL_YEL;    UB_ColorN_ODD[10] = COL_YEL;
    UB_ColorN[11] = COL_YEL;    UB_ColorN_ODD[11] = COL_YEL;
    
    i = 0;
    k = 0;
    while( k < TXT_SIZE_TXT ){
        data = pgm_read_byte( (UH)(string_table[0]+i) );
        if( data != 0 ){
            vram_data[k] = data;
            k++;
        }
        i++;
    }


}


/*  ----------------------------------------------------
    -   Menu send to serial monitoe                     -
    -----------------------------------------------------   */
void PrintAdjMenu(void)
{
    Serial.println(""); 
    Serial.print("0:WHI 1:GRN 2:BLU 3:MAG 4:CYN 5:YEL 6:RED 7:BLK");
    Serial.println(""); 
    Serial.print("[Sig Up/Down] Q/W:Sig1 W/S:Sig2 E/D:Sig3 R/F:Sig4");
    Serial.println("");
    Serial.print("Z:Exit");
    Serial.println("");
}


/*  ----------------------------------------------------
    -   Initialize Full Screen Display Mode             -
    -----------------------------------------------------   */
void Ini_PT_FSC( void )
{
    cli();
    UB_ModePTN = FSC_MODE;
    UB_ModePLS = FRM_OFF;
    Set_FSC_Color( COL_WHI );
    sei();
}


/*  ----------------------------------------------------
    -   Initialize Text Display Mode                   -
    -----------------------------------------------------   */
void Ini_PT_TXT( void )
{
    cli();
    UB_ModePTN = TEXT_MODE;
    UB_ModePLS = FRM_OFF;
    IobjINT.ClearLineData();
    UH_AddrData_n = (UH)(&vram_line[0]);
    Set_TestColor_A();
    objCSL.clear_screen();
    sei();
}


/*  ----------------------------------------------------
    -   Initialize Block Display Mode                  -
    -----------------------------------------------------   */
void Ini_PT_BLK( void )
{
    cli();
    UB_ModePTN_BF = 4;
    UB_ModePTN = 4;
    UB_CMD_SetVram = BLOCK_MODE;
    UB_ModePLS = FRM_OFF;
    IobjINT.ClearLineData();
    UH_AddrData_n = (UH)(&vram_line[0]);
    UH_AddrData_n_ODD = (UH)(&vram_line[COL_MAX_BLK*ROW_MAX_BLK]);
    Set_TestColor_A();
    Clear_BLK();
    sei();
}


/*----------------------------------------------------------------------------
    Demo for Text Display
    
        How to use objCSL.put_char , objSYS.delay132
----------------------------------------------------------------------------*/
void Demo_Text_A( void )
{
    unsigned char i, k, row, column, chr, color;
    unsigned char rnd_color, rnd_line, rnd_odd; 

    unsigned short UH_position;
    unsigned char  UB_char;
    
    objCSL.put_char( 0, 0, 'A' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 1, 0, 'r' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 2, 0, 'd' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 3, 0, 'u' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 4, 0, 'i' );  objSYS.delay132( 4 );    
    objCSL.put_char( 5, 0, 'n' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 6, 0, 'o' );  objSYS.delay132( 4 ); 
    
    objCSL.put_char( 0, 1, 'T' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 1, 1, 'V' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 2, 1, 'o' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 3, 1, 'u' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 4, 1, 't' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 5, 1, '_' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 6, 1, 'C' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 7, 1, 'o' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 8, 1, 'l' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 9, 1, 'o' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 10, 1, 'r' ); objSYS.delay132( 4 ); 
    
    objCSL.put_char( 0, 2, '@' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 1, 2, 'N' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 2, 2, 'a' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 3, 2, 'b' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 4, 2, 'e' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 5, 2, '_' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 6, 2, 'R' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 7, 2, 'M' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 8, 2, 'C' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 9, 2, ' ' );  objSYS.delay132( 4 ); 
    objCSL.put_char( 10, 2, '2' ); objSYS.delay132( 4 ); 
    objCSL.put_char( 11, 2, '0' ); objSYS.delay132( 4 ); 
    objCSL.put_char( 12, 2, '1' ); objSYS.delay132( 4 ); 
    objCSL.put_char( 13, 2, '3' ); objSYS.delay132( 4 ); 
    
    
    /*  --- charcter code 0 - 0x7F write on line4(row3) - line12(row11)     */
    
    UH_position = FL_COL_MAX_TXT *3;
    UB_char = 0;
    while( UH_position < TXT_SIZE_TXT ){
        vram_data[UH_position] = ( UB_char & 0x7F );
        UH_position++;
        UB_char++;
        objSYS.delay132( 1 ); 
    }
    
    /* --- scroll                                                           */
    for( k = 0; k < 100; k++ ){
        for( i = FL_COL_MAX_TXT*3; i < TXT_SIZE_TXT; i++ ){
            vram_data[i] = vram_data[i+1];
        }
        vram_data[TXT_SIZE_TXT-1] = vram_data[FL_COL_MAX_TXT*3 +51];
        objSYS.delay132( 1 ); 
    }
    
    /*  --- scroll and random color change                                  */
    for( k = 0; k < 100; k++ ){
        for( i = FL_COL_MAX_TXT*3; i < TXT_SIZE_TXT; i++ ){
            vram_data[i] = vram_data[i+1];
        }
        vram_data[TXT_SIZE_TXT-1] = vram_data[FL_COL_MAX_TXT*3 +51];
        objSYS.delay132( 1 ); 
        if( (k%4)==0 ){
            rnd_color = (unsigned char)random( 0, 6 );
            Set_TestColor_TXT( rnd_color );
            rnd_color = (unsigned char)random( 0, 6 );
            Set_TestColor_TXT_ODD( rnd_color ); 
        }
    }   
    
    objCSL.clear_screen();
    
}


/*----------------------------------------------------------------------------
    Set Color for Test
        
        Changeable for every even number and odd number
        Changeable for every line
----------------------------------------------------------------------------*/
void Set_TestColor_A(void)
{
    UB_ColorN[0] = COL_RED;     UB_ColorN_ODD[0] = COL_RED;
    UB_ColorN[1] = COL_GRN;     UB_ColorN_ODD[1] = COL_GRN;
    UB_ColorN[2] = COL_BLU;     UB_ColorN_ODD[2] = COL_BLU;
    UB_ColorN[3] = COL_MAG;     UB_ColorN_ODD[3] = COL_MAG;
    UB_ColorN[4] = COL_CYN;     UB_ColorN_ODD[4] = COL_CYN;
    UB_ColorN[5] = COL_YEL;     UB_ColorN_ODD[5] = COL_YEL;
    UB_ColorN[6] = COL_RED;     UB_ColorN_ODD[6] = COL_RED;
    UB_ColorN[7] = COL_WHI;     UB_ColorN_ODD[7] = COL_WHI;
    UB_ColorN[8] = COL_GRN;     UB_ColorN_ODD[8] = COL_GRN;
    UB_ColorN[9] = COL_BLU;     UB_ColorN_ODD[9] = COL_BLU;
    UB_ColorN[10] = COL_MAG;    UB_ColorN_ODD[10] = COL_MAG;
    UB_ColorN[11] = COL_CYN;    UB_ColorN_ODD[11] = COL_CYN;
    UB_ColorN[12] = COL_YEL;    UB_ColorN_ODD[12] = COL_YEL;
    UB_ColorN[13] = COL_RED;    UB_ColorN_ODD[13] = COL_RED;
    UB_ColorN[14] = COL_WHI;    UB_ColorN_ODD[14] = COL_WHI;
    UB_ColorN[15] = COL_GRN;    UB_ColorN_ODD[15] = COL_GRN;
    UB_ColorN[16] = COL_BLU;    UB_ColorN_ODD[16] = COL_BLU;
    UB_ColorN[17] = COL_MAG;    UB_ColorN_ODD[17] = COL_MAG;
    UB_ColorN[18] = COL_CYN;    UB_ColorN_ODD[18] = COL_CYN;
    UB_ColorN[19] = COL_YEL;    UB_ColorN_ODD[19] = COL_YEL;
}



/*  ----------------------------------------------------
    -   Set Color Line 1 - 12 for Text Display          -
    -----------------------------------------------------   */
void Set_TestColor_TXT( UB color )
{
    UB i;
    
    for( i = 3; i < 12; i++ ){
        UB_ColorN[i] = color;
        color++;
        if( color > 6 ){
            color = 0;
        }
    }
}

void Set_TestColor_TXT_ODD( UB color )
{
    UB i;
    
    for( i = 3; i < 12; i++ ){
        UB_ColorN_ODD[i] = color;
        color++;
        if( color > 6 ){
            color = 0;
        }
    }
}
    

/*  ----------------------------------------------------
    -   Block Clear                                    -
    -----------------------------------------------------   */
void Clear_BLK( void )
{
    UH i;
    
    for( i=0; i < TXT_SIZE; i++ ){
        vram_data[i] = 0x00;        /* blank data at MoePTN = 4 or 5        */
    }
    for( i=0; i < LINE_SIZE; i++ ){
        vram_line[i] = 0x00;
    }
}


/*  ----------------------------------------------------
    -   Set Color of Screen                            -
    -----------------------------------------------------   */
void Set_Color( UB color )
{
    UB i;
    
    for( i = 0; i < ROW_MAX_BLK ; i++ ){
        UB_ColorN[i] = color;
        UB_ColorN_ODD[i] = color;
    }
}


/*  ----------------------------------------------------
    -   Put Block                                      -
    -----------------------------------------------------   */
void Put_Block( void )
{
    UH i;
    
    for( i = 0; i < (TXT_SIZE_BLK); i++ ){
        vram_data[i] = 0x1F;
        UB_CMD_SetVram = BLOCK_MODE;
        objCSL.SetVram();
        objSYS.delay132( 1 ); 
    }
}


/*  ----------------------------------------------------
    -   Change Color of Block                           -
    -----------------------------------------------------   */
void Change_Color( void )
{
    UH i,k;
    UB c_data1,c_data2;
    
    for( i = 0; i < 50; i++ ){
        c_data1 = UB_ColorN[0];
        c_data2 = UB_ColorN_ODD[0];
        for( k = 0; k < (ROW_MAX_BLK-1); k++ ){
            UB_ColorN[k] = UB_ColorN[k+1];
            UB_ColorN_ODD[k] = UB_ColorN_ODD[k+1];
        }
        UB_ColorN[ROW_MAX_BLK-1] = c_data1;
        UB_ColorN_ODD[ROW_MAX_BLK-1] = c_data2;
        objSYS.delay132( 1 );
    }
}


/*  ----------------------------------------------------
    -   Change Color at Display Menu                    -
    -----------------------------------------------------   */
void Change_Color_Menu( void )
{
    UB i;
    static UB k = 2;

    for( i = 2; i <=9; i++ ){
        UB_ColorN[i] = COL_BLK; UB_ColorN_ODD[i] = COL_BLK;
    }
    
    switch( k ){
        case 2: UB_ColorN[2] = COL_WHI; UB_ColorN_ODD[2] = COL_WHI; break;
        case 3: UB_ColorN[3] = COL_GRN; UB_ColorN_ODD[3] = COL_GRN; break;
        case 4: UB_ColorN[4] = COL_BLU; UB_ColorN_ODD[4] = COL_BLU; break;
        case 5: UB_ColorN[5] = COL_MAG; UB_ColorN_ODD[5] = COL_MAG; break;
        case 6: UB_ColorN[6] = COL_CYN; UB_ColorN_ODD[6] = COL_CYN; break;
        case 7: UB_ColorN[7] = COL_YEL; UB_ColorN_ODD[7] = COL_YEL; break;
        case 8: UB_ColorN[8] = COL_RED; UB_ColorN_ODD[8] = COL_RED; break;
        case 9: UB_ColorN[9] = COL_WHI; UB_ColorN_ODD[9] = COL_WHI; break;
    }
    
    UB_ColorN[10] = k-2; UB_ColorN_ODD[10] = k-2;
    UB_ColorN[11] = k-2; UB_ColorN_ODD[11] = k-2;
    
    k++;
    if( k > 9 ){
        k = 2;
    }
    objSYS.delay132( 10 );
}


/*  ----------------------------------------------------
    -   Clear Block Random                             -
    -----------------------------------------------------   */
void Clear_Block( void )
{
    UH i;
    
    for( i = 0; i < 500; i++ ){
        vram_data[(unsigned short)random( 0, FL_COL_MAX_BLK * ROW_MAX_BLK )] = 0x00;
        UB_CMD_SetVram = BLOCK_MODE;
        objCSL.SetVram();
    }
    Clear_BLK();                        /* Clear All Block                  */
}


/*  ----------------------------------------------------
    -   Display Invader Type A                          -
    -----------------------------------------------------   */
void Disp_INV_A( void )
{
    UB i,k;
    UH s_data1;
    
    for( k = 0; k <= 2; k++ ){          /* Put Invader Type A               */
        Set_Color( k &0x07 );
        s_data1 =(unsigned short)random( 0, FL_COL_MAX_BLK *(ROW_MAX_BLK-9) );
        Set_INV_A1( s_data1 );
        UB_CMD_SetVram = BLOCK_MODE;
        objCSL.SetVram();
        for( i = 0; i < 5; i++ ){
            objSYS.delay132( 2 );
            Set_INV_A1toA2( s_data1 );
            UB_CMD_SetVram = BLOCK_MODE;
            objCSL.SetVram();
            objSYS.delay132( 2 );
            Set_INV_A2toA1( s_data1 );
            UB_CMD_SetVram = BLOCK_MODE;
            objCSL.SetVram();
        }
        Clear_BLK( );
    }
}


/*  ----------------------------------------------------
    -   Display Invader Type B                          -
    -----------------------------------------------------   */
void Disp_INV_B( void )
{
    UB i,k;
    UH s_data1;
    
    for( k = 2; k <= 4; k++ ){          /* Put Invader Type B               */
        Set_Color( k &0x07 );
        s_data1 =(unsigned short)random( 0, FL_COL_MAX_BLK *(ROW_MAX_BLK-9) );
        for( i = 0; i < 5; i++ ){
            objSYS.delay132( 2 );
            Set_INV_B1( s_data1 );
            UB_CMD_SetVram = BLOCK_MODE;
            objCSL.SetVram();
            objSYS.delay132( 2 );
            Set_INV_B2( s_data1 );
            UB_CMD_SetVram = BLOCK_MODE;
            objCSL.SetVram();
        }
        Clear_BLK( );
    }
}


/*  ----------------------------------------------------
    -   Display Invader Type C                          -
    -----------------------------------------------------   */  
void Disp_INV_C( void )
{
    UB i,k;
    UH s_data1;
    
    for( k = 4; k < 7; k++ ){           /* Put Invader Type C               */
        Set_Color( k &0x07 );
        s_data1 =(unsigned short)random( 0, FL_COL_MAX_BLK *(ROW_MAX_BLK-9) );
        for( i = 0; i < 5; i++ ){
            objSYS.delay132( 2 );
            Set_INV_C1( s_data1 );
            UB_CMD_SetVram = BLOCK_MODE;
            objCSL.SetVram();
            objSYS.delay132( 2 );
            Set_INV_C2( s_data1 );
            UB_CMD_SetVram = BLOCK_MODE;
            objCSL.SetVram();
        }
        Clear_BLK( );
    }
}


/*  ----------------------------------------------------
    -   Invader Type A                                 -
    -----------------------------------------------------   */
void Set_INV_A1( UB zerop )
{
    vram_data[zerop+INV_A1_1] = 0x1F;
    vram_data[zerop+INV_A1_2] = 0x1F;
    vram_data[zerop+INV_A1_3] = 0x1F;
    vram_data[zerop+INV_A1_4] = 0x1F;
    vram_data[zerop+INV_A1_5] = 0x1F;
    vram_data[zerop+INV_A1_6] = 0x1F;
    vram_data[zerop+INV_A1_7] = 0x1F;
    vram_data[zerop+INV_A1_8] = 0x1F;
    vram_data[zerop+INV_A1_9] = 0x1F;
    vram_data[zerop+INV_A1_10] = 0x1F;
    vram_data[zerop+INV_A1_11] = 0x1F;
    vram_data[zerop+INV_A1_12] = 0x1F;
    vram_data[zerop+INV_A1_13] = 0x1F;
    vram_data[zerop+INV_A1_14] = 0x1F;
    vram_data[zerop+INV_A1_15] = 0x1F;
    vram_data[zerop+INV_A1_16] = 0x1F;
    vram_data[zerop+INV_A1_17] = 0x1F;
    vram_data[zerop+INV_A1_18] = 0x1F;
    vram_data[zerop+INV_A1_19] = 0x1F;
    vram_data[zerop+INV_A1_20] = 0x1F;
    vram_data[zerop+INV_A1_21] = 0x1F;
    vram_data[zerop+INV_A1_22] = 0x1F;
    vram_data[zerop+INV_A1_23] = 0x1F;
    vram_data[zerop+INV_A1_24] = 0x1F;
    vram_data[zerop+INV_A1_25] = 0x1F;
    vram_data[zerop+INV_A1_26] = 0x1F;
    vram_data[zerop+INV_A1_27] = 0x1F;
    vram_data[zerop+INV_A1_28] = 0x1F;
    vram_data[zerop+INV_A1_29] = 0x1F;
    vram_data[zerop+INV_A1_30] = 0x1F;
    vram_data[zerop+INV_A1_31] = 0x1F;
    vram_data[zerop+INV_A1_32] = 0x1F;
    vram_data[zerop+INV_A1_33] = 0x1F;
    vram_data[zerop+INV_A1_34] = 0x1F;
    vram_data[zerop+INV_A1_35] = 0x1F;
    vram_data[zerop+INV_A1_36] = 0x1F;
}


void Set_INV_A1toA2( UB zerop )
{
    vram_data[zerop+INV_A1_27] = 0x00;
    vram_data[zerop+INV_A1_28] = 0x00;
    vram_data[zerop+INV_A1_29] = 0x00;
    vram_data[zerop+INV_A1_30] = 0x00;
    vram_data[zerop+INV_A1_31] = 0x00;
    vram_data[zerop+INV_A1_32] = 0x00;
    vram_data[zerop+INV_A1_33] = 0x00;
    vram_data[zerop+INV_A1_34] = 0x00;
    vram_data[zerop+INV_A1_35] = 0x00;
    vram_data[zerop+INV_A1_36] = 0x00;
    
    vram_data[zerop+INV_A2_27] = 0x1F;
    vram_data[zerop+INV_A2_28] = 0x1F;
    vram_data[zerop+INV_A2_29] = 0x1F;
    vram_data[zerop+INV_A2_30] = 0x1F;
    vram_data[zerop+INV_A2_31] = 0x1F;
    vram_data[zerop+INV_A2_32] = 0x1F;
    vram_data[zerop+INV_A2_33] = 0x1F;
    vram_data[zerop+INV_A2_34] = 0x1F;
    vram_data[zerop+INV_A2_35] = 0x1F;
    vram_data[zerop+INV_A2_36] = 0x1F;
    
}   
    
void Set_INV_A2toA1( UB zerop )
{
    vram_data[zerop+INV_A2_27] = 0x00;
    vram_data[zerop+INV_A2_28] = 0x00;
    vram_data[zerop+INV_A2_29] = 0x00;
    vram_data[zerop+INV_A2_30] = 0x00;
    vram_data[zerop+INV_A2_31] = 0x00;
    vram_data[zerop+INV_A2_32] = 0x00;
    vram_data[zerop+INV_A2_33] = 0x00;
    vram_data[zerop+INV_A2_34] = 0x00;
    vram_data[zerop+INV_A2_35] = 0x00;
    vram_data[zerop+INV_A2_36] = 0x00;
    
    vram_data[zerop+INV_A1_27] = 0x1F;
    vram_data[zerop+INV_A1_28] = 0x1F;
    vram_data[zerop+INV_A1_29] = 0x1F;
    vram_data[zerop+INV_A1_30] = 0x1F;
    vram_data[zerop+INV_A1_31] = 0x1F;
    vram_data[zerop+INV_A1_32] = 0x1F;
    vram_data[zerop+INV_A1_33] = 0x1F;
    vram_data[zerop+INV_A1_34] = 0x1F;
    vram_data[zerop+INV_A1_35] = 0x1F;
    vram_data[zerop+INV_A1_36] = 0x1F;
}   


/*  ----------------------------------------------------
    -   Invader Type B                                 -
    -----------------------------------------------------   */
void Set_INV_B1( UB zerop )
{
    vram_data[zerop+INV_B2_1] = 00;
    vram_data[zerop+INV_B2_2] = 00;
    vram_data[zerop+INV_B2_3] = 00;
    vram_data[zerop+INV_B2_4] = 00;
    vram_data[zerop+INV_B2_5] = 00;
    vram_data[zerop+INV_B2_6] = 00;
    vram_data[zerop+INV_B2_7] = 00;
    vram_data[zerop+INV_B2_8] = 00;
    vram_data[zerop+INV_B2_9] = 00;
    vram_data[zerop+INV_B2_10] = 00;
    vram_data[zerop+INV_B2_11] = 00;
    vram_data[zerop+INV_B2_12] = 00;
    vram_data[zerop+INV_B2_13] = 00;
    vram_data[zerop+INV_B2_14] = 00;
    vram_data[zerop+INV_B2_15] = 00;
    vram_data[zerop+INV_B2_16] = 00;
    vram_data[zerop+INV_B2_17] = 00;
    vram_data[zerop+INV_B2_18] = 00;
    vram_data[zerop+INV_B2_19] = 00;
    vram_data[zerop+INV_B2_20] = 00;
    vram_data[zerop+INV_B2_21] = 00;
    vram_data[zerop+INV_B2_22] = 00;
    vram_data[zerop+INV_B2_23] = 00;
    vram_data[zerop+INV_B2_24] = 00;
    vram_data[zerop+INV_B2_25] = 00;
    vram_data[zerop+INV_B2_26] = 00;
    vram_data[zerop+INV_B2_27] = 00;
    vram_data[zerop+INV_B2_28] = 00;
    vram_data[zerop+INV_B2_29] = 00;
    vram_data[zerop+INV_B2_30] = 00;
    vram_data[zerop+INV_B2_31] = 00;
    vram_data[zerop+INV_B2_32] = 00;
    vram_data[zerop+INV_B2_33] = 00;
    vram_data[zerop+INV_B2_34] = 00;
    vram_data[zerop+INV_B2_35] = 00;
    vram_data[zerop+INV_B2_36] = 00;
    vram_data[zerop+INV_B2_37] = 00;
    vram_data[zerop+INV_B2_38] = 00;
    vram_data[zerop+INV_B2_39] = 00;
    vram_data[zerop+INV_B2_40] = 00;
    vram_data[zerop+INV_B2_41] = 00;
    vram_data[zerop+INV_B2_42] = 00;
    vram_data[zerop+INV_B2_43] = 00;
    vram_data[zerop+INV_B2_44] = 00;
    vram_data[zerop+INV_B2_45] = 00;
    vram_data[zerop+INV_B2_46] = 00;
    vram_data[zerop+INV_B2_47] = 00;

    vram_data[zerop+INV_B1_1] = 0x1F;
    vram_data[zerop+INV_B1_2] = 0x1F;
    vram_data[zerop+INV_B1_3] = 0x1F;
    vram_data[zerop+INV_B1_4] = 0x1F;
    vram_data[zerop+INV_B1_5] = 0x1F;
    vram_data[zerop+INV_B1_6] = 0x1F;
    vram_data[zerop+INV_B1_7] = 0x1F;
    vram_data[zerop+INV_B1_8] = 0x1F;
    vram_data[zerop+INV_B1_9] = 0x1F;
    vram_data[zerop+INV_B1_10] = 0x1F;
    vram_data[zerop+INV_B1_11] = 0x1F;
    vram_data[zerop+INV_B1_12] = 0x1F;
    vram_data[zerop+INV_B1_13] = 0x1F;
    vram_data[zerop+INV_B1_14] = 0x1F;
    vram_data[zerop+INV_B1_15] = 0x1F;
    vram_data[zerop+INV_B1_16] = 0x1F;
    vram_data[zerop+INV_B1_17] = 0x1F;
    vram_data[zerop+INV_B1_18] = 0x1F;
    vram_data[zerop+INV_B1_19] = 0x1F;
    vram_data[zerop+INV_B1_20] = 0x1F;
    vram_data[zerop+INV_B1_21] = 0x1F;
    vram_data[zerop+INV_B1_22] = 0x1F;
    vram_data[zerop+INV_B1_23] = 0x1F;
    vram_data[zerop+INV_B1_24] = 0x1F;
    vram_data[zerop+INV_B1_25] = 0x1F;
    vram_data[zerop+INV_B1_26] = 0x1F;
    vram_data[zerop+INV_B1_27] = 0x1F;
    vram_data[zerop+INV_B1_28] = 0x1F;
    vram_data[zerop+INV_B1_29] = 0x1F;
    vram_data[zerop+INV_B1_30] = 0x1F;
    vram_data[zerop+INV_B1_31] = 0x1F;
    vram_data[zerop+INV_B1_32] = 0x1F;
    vram_data[zerop+INV_B1_33] = 0x1F;
    vram_data[zerop+INV_B1_34] = 0x1F;
    vram_data[zerop+INV_B1_35] = 0x1F;
    vram_data[zerop+INV_B1_36] = 0x1F;
    vram_data[zerop+INV_B1_37] = 0x1F;
    vram_data[zerop+INV_B1_38] = 0x1F;
    vram_data[zerop+INV_B1_39] = 0x1F;
    vram_data[zerop+INV_B1_40] = 0x1F;
    vram_data[zerop+INV_B1_41] = 0x1F;
    vram_data[zerop+INV_B1_42] = 0x1F;
    vram_data[zerop+INV_B1_43] = 0x1F;
    vram_data[zerop+INV_B1_44] = 0x1F;
    vram_data[zerop+INV_B1_45] = 0x1F;
}


void Set_INV_B2( UB zerop )
{
    vram_data[zerop+INV_B1_1] = 00;
    vram_data[zerop+INV_B1_2] = 00;
    vram_data[zerop+INV_B1_3] = 00;
    vram_data[zerop+INV_B1_4] = 00;
    vram_data[zerop+INV_B1_5] = 00;
    vram_data[zerop+INV_B1_6] = 00;
    vram_data[zerop+INV_B1_7] = 00;
    vram_data[zerop+INV_B1_8] = 00;
    vram_data[zerop+INV_B1_9] = 00;
    vram_data[zerop+INV_B1_10] = 00;
    vram_data[zerop+INV_B1_11] = 00;
    vram_data[zerop+INV_B1_12] = 00;
    vram_data[zerop+INV_B1_13] = 00;
    vram_data[zerop+INV_B1_14] = 00;
    vram_data[zerop+INV_B1_15] = 00;
    vram_data[zerop+INV_B1_16] = 00;
    vram_data[zerop+INV_B1_17] = 00;
    vram_data[zerop+INV_B1_18] = 00;
    vram_data[zerop+INV_B1_19] = 00;
    vram_data[zerop+INV_B1_20] = 00;
    vram_data[zerop+INV_B1_21] = 00;
    vram_data[zerop+INV_B1_22] = 00;
    vram_data[zerop+INV_B1_23] = 00;
    vram_data[zerop+INV_B1_24] = 00;
    vram_data[zerop+INV_B1_25] = 00;
    vram_data[zerop+INV_B1_26] = 00;
    vram_data[zerop+INV_B1_27] = 00;
    vram_data[zerop+INV_B1_28] = 00;
    vram_data[zerop+INV_B1_29] = 00;
    vram_data[zerop+INV_B1_30] = 00;
    vram_data[zerop+INV_B1_31] = 00;
    vram_data[zerop+INV_B1_32] = 00;
    vram_data[zerop+INV_B1_33] = 00;
    vram_data[zerop+INV_B1_34] = 00;
    vram_data[zerop+INV_B1_35] = 00;
    vram_data[zerop+INV_B1_36] = 00;
    vram_data[zerop+INV_B1_37] = 00;
    vram_data[zerop+INV_B1_38] = 00;
    vram_data[zerop+INV_B1_39] = 00;
    vram_data[zerop+INV_B1_40] = 00;
    vram_data[zerop+INV_B1_41] = 00;
    vram_data[zerop+INV_B1_42] = 00;
    vram_data[zerop+INV_B1_43] = 00;
    vram_data[zerop+INV_B1_44] = 00;
    vram_data[zerop+INV_B1_45] = 00;

    vram_data[zerop+INV_B2_1] = 0x1F;
    vram_data[zerop+INV_B2_2] = 0x1F;
    vram_data[zerop+INV_B2_3] = 0x1F;
    vram_data[zerop+INV_B2_4] = 0x1F;
    vram_data[zerop+INV_B2_5] = 0x1F;
    vram_data[zerop+INV_B2_6] = 0x1F;
    vram_data[zerop+INV_B2_7] = 0x1F;
    vram_data[zerop+INV_B2_8] = 0x1F;
    vram_data[zerop+INV_B2_9] = 0x1F;
    vram_data[zerop+INV_B2_10] = 0x1F;
    vram_data[zerop+INV_B2_11] = 0x1F;
    vram_data[zerop+INV_B2_12] = 0x1F;
    vram_data[zerop+INV_B2_13] = 0x1F;
    vram_data[zerop+INV_B2_14] = 0x1F;
    vram_data[zerop+INV_B2_15] = 0x1F;
    vram_data[zerop+INV_B2_16] = 0x1F;
    vram_data[zerop+INV_B2_17] = 0x1F;
    vram_data[zerop+INV_B2_18] = 0x1F;
    vram_data[zerop+INV_B2_19] = 0x1F;
    vram_data[zerop+INV_B2_20] = 0x1F;
    vram_data[zerop+INV_B2_21] = 0x1F;
    vram_data[zerop+INV_B2_22] = 0x1F;
    vram_data[zerop+INV_B2_23] = 0x1F;
    vram_data[zerop+INV_B2_24] = 0x1F;
    vram_data[zerop+INV_B2_25] = 0x1F;
    vram_data[zerop+INV_B2_26] = 0x1F;
    vram_data[zerop+INV_B2_27] = 0x1F;
    vram_data[zerop+INV_B2_28] = 0x1F;
    vram_data[zerop+INV_B2_29] = 0x1F;
    vram_data[zerop+INV_B2_30] = 0x1F;
    vram_data[zerop+INV_B2_31] = 0x1F;
    vram_data[zerop+INV_B2_32] = 0x1F;
    vram_data[zerop+INV_B2_33] = 0x1F;
    vram_data[zerop+INV_B2_34] = 0x1F;
    vram_data[zerop+INV_B2_35] = 0x1F;
    vram_data[zerop+INV_B2_36] = 0x1F;
    vram_data[zerop+INV_B2_37] = 0x1F;
    vram_data[zerop+INV_B2_38] = 0x1F;
    vram_data[zerop+INV_B2_39] = 0x1F;
    vram_data[zerop+INV_B2_40] = 0x1F;
    vram_data[zerop+INV_B2_41] = 0x1F;
    vram_data[zerop+INV_B2_42] = 0x1F;
    vram_data[zerop+INV_B2_43] = 0x1F;
    vram_data[zerop+INV_B2_44] = 0x1F;
    vram_data[zerop+INV_B2_45] = 0x1F;
    vram_data[zerop+INV_B2_46] = 0x1F;
    vram_data[zerop+INV_B2_47] = 0x1F;
}


/*  ----------------------------------------------------
    -   Invader Type C                                 -
    -----------------------------------------------------   */
void Set_INV_C1( UB zerop )
{
    vram_data[zerop+INV_C2_1] = 00;
    vram_data[zerop+INV_C2_2] = 00;
    vram_data[zerop+INV_C2_3] = 00;
    vram_data[zerop+INV_C2_4] = 00;
    vram_data[zerop+INV_C2_5] = 00;
    vram_data[zerop+INV_C2_6] = 00;
    vram_data[zerop+INV_C2_7] = 00;
    vram_data[zerop+INV_C2_8] = 00;
    vram_data[zerop+INV_C2_9] = 00;
    vram_data[zerop+INV_C2_10] = 00;
    vram_data[zerop+INV_C2_11] = 00;
    vram_data[zerop+INV_C2_12] = 00;
    vram_data[zerop+INV_C2_13] = 00;
    vram_data[zerop+INV_C2_14] = 00;
    vram_data[zerop+INV_C2_15] = 00;
    vram_data[zerop+INV_C2_16] = 00;
    vram_data[zerop+INV_C2_17] = 00;
    vram_data[zerop+INV_C2_18] = 00;
    vram_data[zerop+INV_C2_19] = 00;
    vram_data[zerop+INV_C2_20] = 00;
    vram_data[zerop+INV_C2_21] = 00;
    vram_data[zerop+INV_C2_22] = 00;
    vram_data[zerop+INV_C2_23] = 00;
    vram_data[zerop+INV_C2_24] = 00;
    vram_data[zerop+INV_C2_25] = 00;
    vram_data[zerop+INV_C2_26] = 00;
    vram_data[zerop+INV_C2_27] = 00;
    vram_data[zerop+INV_C2_28] = 00;
    vram_data[zerop+INV_C2_29] = 00;
    vram_data[zerop+INV_C2_30] = 00;
    vram_data[zerop+INV_C2_31] = 00;
    vram_data[zerop+INV_C2_32] = 00;
    vram_data[zerop+INV_C2_33] = 00;
    vram_data[zerop+INV_C2_34] = 00;
    vram_data[zerop+INV_C2_35] = 00;
    vram_data[zerop+INV_C2_36] = 00;
    vram_data[zerop+INV_C2_37] = 00;
    vram_data[zerop+INV_C2_38] = 00;
    vram_data[zerop+INV_C2_39] = 00;
    vram_data[zerop+INV_C2_40] = 00;
    vram_data[zerop+INV_C2_41] = 00;
    vram_data[zerop+INV_C2_42] = 00;
    vram_data[zerop+INV_C2_43] = 00;
    vram_data[zerop+INV_C2_44] = 00;
    vram_data[zerop+INV_C2_45] = 00;
    vram_data[zerop+INV_C2_46] = 00;
    vram_data[zerop+INV_C2_47] = 00;
    vram_data[zerop+INV_C2_48] = 00;
    vram_data[zerop+INV_C2_49] = 00;
    vram_data[zerop+INV_C2_50] = 00;
    vram_data[zerop+INV_C2_51] = 00;
    vram_data[zerop+INV_C2_52] = 00;
    vram_data[zerop+INV_C2_53] = 00;
    vram_data[zerop+INV_C2_54] = 00;
    vram_data[zerop+INV_C2_55] = 00;
    vram_data[zerop+INV_C2_56] = 00;
    vram_data[zerop+INV_C2_57] = 00;
    vram_data[zerop+INV_C2_58] = 00;
    vram_data[zerop+INV_C2_59] = 00;
    vram_data[zerop+INV_C2_60] = 00;
    vram_data[zerop+INV_C2_61] = 00;
    vram_data[zerop+INV_C2_62] = 00;
    vram_data[zerop+INV_C2_63] = 00;
    vram_data[zerop+INV_C2_64] = 00;    
    
    vram_data[zerop+INV_C1_1] = 0x1F;
    vram_data[zerop+INV_C1_2] = 0x1F;
    vram_data[zerop+INV_C1_3] = 0x1F;
    vram_data[zerop+INV_C1_4] = 0x1F;
    vram_data[zerop+INV_C1_5] = 0x1F;
    vram_data[zerop+INV_C1_6] = 0x1F;
    vram_data[zerop+INV_C1_7] = 0x1F;
    vram_data[zerop+INV_C1_8] = 0x1F;
    vram_data[zerop+INV_C1_9] = 0x1F;
    vram_data[zerop+INV_C1_10] = 0x1F;
    vram_data[zerop+INV_C1_11] = 0x1F;
    vram_data[zerop+INV_C1_12] = 0x1F;
    vram_data[zerop+INV_C1_13] = 0x1F;
    vram_data[zerop+INV_C1_14] = 0x1F;
    vram_data[zerop+INV_C1_15] = 0x1F;
    vram_data[zerop+INV_C1_16] = 0x1F;
    vram_data[zerop+INV_C1_17] = 0x1F;
    vram_data[zerop+INV_C1_18] = 0x1F;
    vram_data[zerop+INV_C1_19] = 0x1F;
    vram_data[zerop+INV_C1_20] = 0x1F;
    vram_data[zerop+INV_C1_21] = 0x1F;
    vram_data[zerop+INV_C1_22] = 0x1F;
    vram_data[zerop+INV_C1_23] = 0x1F;
    vram_data[zerop+INV_C1_24] = 0x1F;
    vram_data[zerop+INV_C1_25] = 0x1F;
    vram_data[zerop+INV_C1_26] = 0x1F;
    vram_data[zerop+INV_C1_27] = 0x1F;
    vram_data[zerop+INV_C1_28] = 0x1F;
    vram_data[zerop+INV_C1_29] = 0x1F;
    vram_data[zerop+INV_C1_30] = 0x1F;
    vram_data[zerop+INV_C1_31] = 0x1F;
    vram_data[zerop+INV_C1_32] = 0x1F;
    vram_data[zerop+INV_C1_33] = 0x1F;
    vram_data[zerop+INV_C1_34] = 0x1F;
    vram_data[zerop+INV_C1_35] = 0x1F;
    vram_data[zerop+INV_C1_36] = 0x1F;
    vram_data[zerop+INV_C1_37] = 0x1F;
    vram_data[zerop+INV_C1_38] = 0x1F;
    vram_data[zerop+INV_C1_39] = 0x1F;
    vram_data[zerop+INV_C1_40] = 0x1F;
    vram_data[zerop+INV_C1_41] = 0x1F;
    vram_data[zerop+INV_C1_42] = 0x1F;
    vram_data[zerop+INV_C1_43] = 0x1F;
    vram_data[zerop+INV_C1_44] = 0x1F;
    vram_data[zerop+INV_C1_45] = 0x1F;
    vram_data[zerop+INV_C1_46] = 0x1F;
    vram_data[zerop+INV_C1_47] = 0x1F;
    vram_data[zerop+INV_C1_48] = 0x1F;
    vram_data[zerop+INV_C1_49] = 0x1F;
    vram_data[zerop+INV_C1_50] = 0x1F;
    vram_data[zerop+INV_C1_51] = 0x1F;
    vram_data[zerop+INV_C1_52] = 0x1F;
    vram_data[zerop+INV_C1_53] = 0x1F;
    vram_data[zerop+INV_C1_54] = 0x1F;
    vram_data[zerop+INV_C1_55] = 0x1F;
    vram_data[zerop+INV_C1_56] = 0x1F;
    vram_data[zerop+INV_C1_57] = 0x1F;
    vram_data[zerop+INV_C1_58] = 0x1F;
    vram_data[zerop+INV_C1_59] = 0x1F;
    vram_data[zerop+INV_C1_60] = 0x1F;
    vram_data[zerop+INV_C1_61] = 0x1F;
}

void Set_INV_C2( UB zerop )
{
    vram_data[zerop+INV_C1_1] = 00;
    vram_data[zerop+INV_C1_2] = 00;
    vram_data[zerop+INV_C1_3] = 00;
    vram_data[zerop+INV_C1_4] = 00;
    vram_data[zerop+INV_C1_5] = 00;
    vram_data[zerop+INV_C1_6] = 00;
    vram_data[zerop+INV_C1_7] = 00;
    vram_data[zerop+INV_C1_8] = 00;
    vram_data[zerop+INV_C1_9] = 00;
    vram_data[zerop+INV_C1_10] = 00;
    vram_data[zerop+INV_C1_11] = 00;
    vram_data[zerop+INV_C1_12] = 00;
    vram_data[zerop+INV_C1_13] = 00;
    vram_data[zerop+INV_C1_14] = 00;
    vram_data[zerop+INV_C1_15] = 00;
    vram_data[zerop+INV_C1_16] = 00;
    vram_data[zerop+INV_C1_17] = 00;
    vram_data[zerop+INV_C1_18] = 00;
    vram_data[zerop+INV_C1_19] = 00;
    vram_data[zerop+INV_C1_20] = 00;
    vram_data[zerop+INV_C1_21] = 00;
    vram_data[zerop+INV_C1_22] = 00;
    vram_data[zerop+INV_C1_23] = 00;
    vram_data[zerop+INV_C1_24] = 00;
    vram_data[zerop+INV_C1_25] = 00;
    vram_data[zerop+INV_C1_26] = 00;
    vram_data[zerop+INV_C1_27] = 00;
    vram_data[zerop+INV_C1_28] = 00;
    vram_data[zerop+INV_C1_29] = 00;
    vram_data[zerop+INV_C1_30] = 00;
    vram_data[zerop+INV_C1_31] = 00;
    vram_data[zerop+INV_C1_32] = 00;
    vram_data[zerop+INV_C1_33] = 00;
    vram_data[zerop+INV_C1_34] = 00;
    vram_data[zerop+INV_C1_35] = 00;
    vram_data[zerop+INV_C1_36] = 00;
    vram_data[zerop+INV_C1_37] = 00;
    vram_data[zerop+INV_C1_38] = 00;
    vram_data[zerop+INV_C1_39] = 00;
    vram_data[zerop+INV_C1_40] = 00;
    vram_data[zerop+INV_C1_41] = 00;
    vram_data[zerop+INV_C1_42] = 00;
    vram_data[zerop+INV_C1_43] = 00;
    vram_data[zerop+INV_C1_44] = 00;
    vram_data[zerop+INV_C1_45] = 00;
    vram_data[zerop+INV_C1_46] = 00;
    vram_data[zerop+INV_C1_47] = 00;
    vram_data[zerop+INV_C1_48] = 00;
    vram_data[zerop+INV_C1_49] = 00;
    vram_data[zerop+INV_C1_50] = 00;
    vram_data[zerop+INV_C1_51] = 00;
    vram_data[zerop+INV_C1_52] = 00;
    vram_data[zerop+INV_C1_53] = 00;
    vram_data[zerop+INV_C1_54] = 00;
    vram_data[zerop+INV_C1_55] = 00;
    vram_data[zerop+INV_C1_56] = 00;
    vram_data[zerop+INV_C1_57] = 00;
    vram_data[zerop+INV_C1_58] = 00;
    vram_data[zerop+INV_C1_59] = 00;
    vram_data[zerop+INV_C1_60] = 00;
    vram_data[zerop+INV_C1_61] = 00;

    vram_data[zerop+INV_C2_1] = 0x1F;
    vram_data[zerop+INV_C2_2] = 0x1F;
    vram_data[zerop+INV_C2_3] = 0x1F;
    vram_data[zerop+INV_C2_4] = 0x1F;
    vram_data[zerop+INV_C2_5] = 0x1F;
    vram_data[zerop+INV_C2_6] = 0x1F;
    vram_data[zerop+INV_C2_7] = 0x1F;
    vram_data[zerop+INV_C2_8] = 0x1F;
    vram_data[zerop+INV_C2_9] = 0x1F;
    vram_data[zerop+INV_C2_10] = 0x1F;
    vram_data[zerop+INV_C2_11] = 0x1F;
    vram_data[zerop+INV_C2_12] = 0x1F;
    vram_data[zerop+INV_C2_13] = 0x1F;
    vram_data[zerop+INV_C2_14] = 0x1F;
    vram_data[zerop+INV_C2_15] = 0x1F;
    vram_data[zerop+INV_C2_16] = 0x1F;
    vram_data[zerop+INV_C2_17] = 0x1F;
    vram_data[zerop+INV_C2_18] = 0x1F;
    vram_data[zerop+INV_C2_19] = 0x1F;
    vram_data[zerop+INV_C2_20] = 0x1F;
    vram_data[zerop+INV_C2_21] = 0x1F;
    vram_data[zerop+INV_C2_22] = 0x1F;
    vram_data[zerop+INV_C2_23] = 0x1F;
    vram_data[zerop+INV_C2_24] = 0x1F;
    vram_data[zerop+INV_C2_25] = 0x1F;
    vram_data[zerop+INV_C2_26] = 0x1F;
    vram_data[zerop+INV_C2_27] = 0x1F;
    vram_data[zerop+INV_C2_28] = 0x1F;
    vram_data[zerop+INV_C2_29] = 0x1F;
    vram_data[zerop+INV_C2_30] = 0x1F;
    vram_data[zerop+INV_C2_31] = 0x1F;
    vram_data[zerop+INV_C2_32] = 0x1F;
    vram_data[zerop+INV_C2_33] = 0x1F;
    vram_data[zerop+INV_C2_34] = 0x1F;
    vram_data[zerop+INV_C2_35] = 0x1F;
    vram_data[zerop+INV_C2_36] = 0x1F;
    vram_data[zerop+INV_C2_37] = 0x1F;
    vram_data[zerop+INV_C2_38] = 0x1F;
    vram_data[zerop+INV_C2_39] = 0x1F;
    vram_data[zerop+INV_C2_40] = 0x1F;
    vram_data[zerop+INV_C2_41] = 0x1F;
    vram_data[zerop+INV_C2_42] = 0x1F;
    vram_data[zerop+INV_C2_43] = 0x1F;
    vram_data[zerop+INV_C2_44] = 0x1F;
    vram_data[zerop+INV_C2_45] = 0x1F;
    vram_data[zerop+INV_C2_46] = 0x1F;
    vram_data[zerop+INV_C2_47] = 0x1F;
    vram_data[zerop+INV_C2_48] = 0x1F;
    vram_data[zerop+INV_C2_49] = 0x1F;
    vram_data[zerop+INV_C2_50] = 0x1F;
    vram_data[zerop+INV_C2_51] = 0x1F;
    vram_data[zerop+INV_C2_52] = 0x1F;
    vram_data[zerop+INV_C2_53] = 0x1F;
    vram_data[zerop+INV_C2_54] = 0x1F;
    vram_data[zerop+INV_C2_55] = 0x1F;
    vram_data[zerop+INV_C2_56] = 0x1F;
    vram_data[zerop+INV_C2_57] = 0x1F;
    vram_data[zerop+INV_C2_58] = 0x1F;
    vram_data[zerop+INV_C2_59] = 0x1F;
    vram_data[zerop+INV_C2_60] = 0x1F;
    vram_data[zerop+INV_C2_61] = 0x1F;
    vram_data[zerop+INV_C2_62] = 0x1F;
    vram_data[zerop+INV_C2_63] = 0x1F;
    vram_data[zerop+INV_C2_64] = 0x1F;
}





