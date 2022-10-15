/*****************************************************************************
    System Name : TVoutColor_NTSC
    File Name   : defPort.h
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
                with pullup --> input mode and write "1"
                
                I/O pullup
    Port B      ----------------------------------------
        PB_5    out w/o         LED         Port
        PB_4    x
        PB_3    x
        PB_2    x
        PB_1    out w/o         Sync_Out    OC1A/Port
        PB_0    x

    Port C      ----------------------------------------
        PC_5    x
        PC_4    out             CRT_Sig_A4  port
        PC_3    out             CRT_Sig_A3  Port
        PC_2    out             CRT_Sig_A2  Port
        PC_1    out             CRT_Sig_A1  Port
        PC_0    out             CRT_Sig_A0  Port

    Port D      ----------------------------------------
        PD_7    out             Debug Port2 Port
        PD_6    x
        PD_5    x
        PD_4    x
        PD_3    x               Sound_Out   OC2B        *1
        PD_2    out w/o         Debug Port1 Port
        PD_1    x               TXD
        PD_0    x               RXD

    *1 futral option

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define P_LED1_ON       asm volatile("cbi 0x05,5"::)    /* PORTB.5          */
#define P_LED1_OFF      asm volatile("sbi 0x05,5"::)
#define P_DBG1_ON       asm volatile("cbi 0x0B,2"::)    /* PORTD.2          */
#define P_DBG1_OFF      asm volatile("sbi 0x0B,2"::)
#define P_DBG2_ON       asm volatile("cbi 0x0B,7"::)    /* PORTD.7          */
#define P_DBG2_OFF      asm volatile("sbi 0x0B,7"::)

/*  --- pullup -------------------------------------------------------------
    PUD PullUp Disable  initial Value = 0 -> pull up enable
    the PUD bit in the MCUCR Register can be set to disable all pull-ups 
    in all ports.
    DDxn    Portxn  PUD     in/out  pullup
    0       0       x       in      without
    0       1       0       in      with
    0       1       1       in      without
    1       0       x       out     without
    1       1       x       out     without
    ------------------------------------------------------------------------*/
    
/* --- in/out/data ---------------------------------------------------------*/
#define INI_DDRB    0x22        /*                              0010_0010B  */
#define OR_DDRB     0x22        /*                              0010_0010B  */
#define INI_PORTB   0x00        /*                              0000_0000B  */
#define AND_PORTB   0xDD        /*                              1101_1101B  */

#define INI_DDRC    0x1F        /*                              0001_1111B  */
#define OR_DDRC     0x1F        /*                              0001_1111B  */
#define INI_PORTC   0x00        /*                              0000_0000B  */
#define AND_PORTC   0           /*                              1110_0000B  */

#define INI_DDRD    0x8C        /*                              1000_1100B  */
#define OR_DDRD     0x84        /*                              1000_0100B  */
#define INI_PORTD   0x00        /*                              0000_0000B  */
#define AND_PORTD   0x7B        /*                              0111_1011B  */
                            
