/*****************************************************************************
    System Name : TVoutColor_NTSC
    File Name   : INT_Ini.cpp
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
#define INT_INCLUDE
#include "defSYS.h"
#include "defINT.h"
#include "defCRT.h"

/*==========================================================================*/
/*  Program                                                                 */
/*==========================================================================*/
CINT::CINT()
{
    Ini();
}

UB CINT::UBf_132ms_req = 0;

void CINT::Ini( void )
{
    int i,k;
    UB_ModePTN = 0;
    UB_ModePLS = FRM_OFF;
    UH_hline = 0;
    UB_scanline = 0;
    UB_cg_line = 0;
    UB_row = 0;
    UH_AddrDataNow = 0;
    UBf_132ms_req = 0;
}


UB  CINT::Check132ms()  
{
    if( UBf_132ms_req ==0 ){
        return( 0 );
    }
    else{
        UBf_132ms_req =0;
        return( 1 );
    }
}

