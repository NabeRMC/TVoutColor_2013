/*****************************************************************************
    System Name : TVoutColor_NTSC
    File Name   : defCSL.h
    Content     : 
    Version     : 0.0
    CPU board   : Arduino UNO/Duemilanove
    Compiler    : Arduino 1.0.4
    History     : 2013/10/04
*****************************************************************************/
/*----------------------------------------------------------------------------
;  Copyleft @Nabe_RMC
;---------------------------------------------------------------------------*/
#ifdef      CSL_INCLUDE
#define     CSL_EXT 
#else
#define     CSL_EXT extern
#endif

/*==========================================================================*/
/*  Includes                                                                */
/*==========================================================================*/
#ifndef     COMMON_H
#include    "nabe_common.h"
#endif

/*==========================================================================*/
/*  DEFINE                                                                  */
/*==========================================================================*/
#define COL_WHI     0
#define COL_GRN     1
#define COL_BLU     2
#define COL_MAG     3
#define COL_CYN     4
#define COL_YEL     5
#define COL_RED     6
#define COL_BLK     7


#define CLM FL_COL_MAX_BLK

#define INV_A1_1    ( CLM*0 +3 )
#define INV_A1_2    ( CLM*0 +4 )
#define INV_A1_3    ( CLM*1 +2 )
#define INV_A1_4    ( CLM*1 +3 )
#define INV_A1_5    ( CLM*1 +4 )
#define INV_A1_6    ( CLM*1 +5 )
#define INV_A1_7    ( CLM*2 +1 )
#define INV_A1_8    ( CLM*2 +2 )
#define INV_A1_9    ( CLM*2 +3 )
#define INV_A1_10   ( CLM*2 +4 )
#define INV_A1_11   ( CLM*2 +5 )
#define INV_A1_12   ( CLM*2 +6 )
#define INV_A1_13   ( CLM*3 +0 )
#define INV_A1_14   ( CLM*3 +1 )
#define INV_A1_15   ( CLM*3 +3 )
#define INV_A1_16   ( CLM*3 +4 )
#define INV_A1_17   ( CLM*3 +6 )
#define INV_A1_18   ( CLM*3 +7 )
#define INV_A1_19   ( CLM*4 +0 )
#define INV_A1_20   ( CLM*4 +1 )
#define INV_A1_21   ( CLM*4 +2 )
#define INV_A1_22   ( CLM*4 +3 )
#define INV_A1_23   ( CLM*4 +4 )
#define INV_A1_24   ( CLM*4 +5 )
#define INV_A1_25   ( CLM*4 +6 )
#define INV_A1_26   ( CLM*4 +7 )

#define INV_A1_27   ( CLM*5 +2 )
#define INV_A1_28   ( CLM*5 +5 )
#define INV_A1_29   ( CLM*6 +1 )
#define INV_A1_30   ( CLM*6 +3 )
#define INV_A1_31   ( CLM*6 +4 )
#define INV_A1_32   ( CLM*6 +6 )
#define INV_A1_33   ( CLM*7 +0 )
#define INV_A1_34   ( CLM*7 +2 )
#define INV_A1_35   ( CLM*7 +5 )
#define INV_A1_36   ( CLM*7 +7 ) 


#define INV_A2_1    ( CLM*0 +3 )
#define INV_A2_2    ( CLM*0 +4 )
#define INV_A2_3    ( CLM*1 +2 )
#define INV_A2_4    ( CLM*1 +3 )
#define INV_A2_5    ( CLM*1 +4 )
#define INV_A2_6    ( CLM*1 +5 )
#define INV_A2_7    ( CLM*2 +1 )
#define INV_A2_8    ( CLM*2 +2 )
#define INV_A2_9    ( CLM*2 +3 )
#define INV_A2_10   ( CLM*2 +4 )
#define INV_A2_11   ( CLM*2 +5 )
#define INV_A2_12   ( CLM*2 +6 )
#define INV_A2_13   ( CLM*3 +0 )
#define INV_A2_14   ( CLM*3 +1 )
#define INV_A2_15   ( CLM*3 +3 )
#define INV_A2_16   ( CLM*3 +4 )
#define INV_A2_17   ( CLM*3 +6 )
#define INV_A2_18   ( CLM*3 +7 )
#define INV_A2_19   ( CLM*4 +0 )
#define INV_A2_20   ( CLM*4 +1 )
#define INV_A2_21   ( CLM*4 +2 )
#define INV_A2_22   ( CLM*4 +3 )
#define INV_A2_23   ( CLM*4 +4 )
#define INV_A2_24   ( CLM*4 +5 )
#define INV_A2_25   ( CLM*4 +6 )
#define INV_A2_26   ( CLM*4 +7 )

#define INV_A2_27   ( CLM*5 +1 )
#define INV_A2_28   ( CLM*5 +3 )
#define INV_A2_29   ( CLM*5 +3 )
#define INV_A2_30   ( CLM*5 +6 )
#define INV_A2_31   ( CLM*6 +0 )
#define INV_A2_32   ( CLM*6 +3 )
#define INV_A2_33   ( CLM*6 +4 )
#define INV_A2_34   ( CLM*6 +7 )
#define INV_A2_35   ( CLM*7 +1 )
#define INV_A2_36   ( CLM*7 +6 )


#define INV_B1_1    ( CLM*0 +2 )
#define INV_B1_2    ( CLM*0 +8 ) 
#define INV_B1_3    ( CLM*1 +0 )
#define INV_B1_4    ( CLM*1 +2 ) 
#define INV_B1_5    ( CLM*1 +3 )
#define INV_B1_6    ( CLM*1 +7 ) 
#define INV_B1_7    ( CLM*1 +8 )
#define INV_B1_8    ( CLM*1 +10 ) 
#define INV_B1_9    ( CLM*2 +0 )
#define INV_B1_10   ( CLM*2 +3 ) 
#define INV_B1_11   ( CLM*2 +4 )
#define INV_B1_12   ( CLM*2 +5 ) 
#define INV_B1_13   ( CLM*2 +6 )
#define INV_B1_14   ( CLM*2 +7 ) 
#define INV_B1_15   ( CLM*2 +10 )
#define INV_B1_16   ( CLM*3 +0 ) 
#define INV_B1_17   ( CLM*3 +1 ) 
#define INV_B1_18   ( CLM*3 +2 ) 
#define INV_B1_19   ( CLM*3 +4 ) 
#define INV_B1_20   ( CLM*3 +5 ) 
#define INV_B1_21   ( CLM*3 +6 ) 
#define INV_B1_22   ( CLM*3 +8 ) 
#define INV_B1_23   ( CLM*3 +9 ) 
#define INV_B1_23   ( CLM*3 +10 ) 
#define INV_B1_24   ( CLM*4 +0 ) 
#define INV_B1_25   ( CLM*4 +1 ) 
#define INV_B1_26   ( CLM*4 +2 ) 
#define INV_B1_27   ( CLM*4 +3 ) 
#define INV_B1_28   ( CLM*4 +4 ) 
#define INV_B1_29   ( CLM*4 +5 ) 
#define INV_B1_30   ( CLM*4 +6 ) 
#define INV_B1_31   ( CLM*4 +7 ) 
#define INV_B1_32   ( CLM*4 +8 ) 
#define INV_B1_33   ( CLM*4 +9 ) 
#define INV_B1_34   ( CLM*4 +10 ) 
#define INV_B1_35   ( CLM*5 +2 ) 
#define INV_B1_36   ( CLM*5 +3 ) 
#define INV_B1_37   ( CLM*5 +4 ) 
#define INV_B1_38   ( CLM*5 +5 ) 
#define INV_B1_39   ( CLM*5 +6 ) 
#define INV_B1_40   ( CLM*5 +7 ) 
#define INV_B1_41   ( CLM*5 +8 ) 
#define INV_B1_42   ( CLM*6 +2 )
#define INV_B1_43   ( CLM*6 +8 ) 
#define INV_B1_44   ( CLM*7 +1 )
#define INV_B1_45   ( CLM*7 +9 )


#define INV_B2_1    ( CLM*0 +2 )
#define INV_B2_2    ( CLM*0 +8 )
#define INV_B2_3    ( CLM*1 +2 )
#define INV_B2_4    ( CLM*1 +3 )
#define INV_B2_5    ( CLM*1 +7 )
#define INV_B2_6    ( CLM*1 +8 )
#define INV_B2_7    ( CLM*2 +3 )
#define INV_B2_8    ( CLM*2 +4 )
#define INV_B2_9    ( CLM*2 +5 )
#define INV_B2_10   ( CLM*2 +6 )
#define INV_B2_11   ( CLM*2 +7 ) 
#define INV_B2_12   ( CLM*3 +1 ) 
#define INV_B2_13   ( CLM*3 +2 ) 
#define INV_B2_14   ( CLM*3 +4 ) 
#define INV_B2_15   ( CLM*3 +5 ) 
#define INV_B2_16   ( CLM*3 +6 ) 
#define INV_B2_17   ( CLM*3 +8 ) 
#define INV_B2_18   ( CLM*3 +9 ) 
#define INV_B2_19   ( CLM*4 +0 ) 
#define INV_B2_20   ( CLM*4 +1 ) 
#define INV_B2_21   ( CLM*4 +2 ) 
#define INV_B2_22   ( CLM*4 +3 ) 
#define INV_B2_23   ( CLM*4 +4 ) 
#define INV_B2_24   ( CLM*4 +5 ) 
#define INV_B2_25   ( CLM*4 +6 ) 
#define INV_B2_26   ( CLM*4 +7 ) 
#define INV_B2_27   ( CLM*4 +8 ) 
#define INV_B2_28   ( CLM*4 +9 ) 
#define INV_B2_29   ( CLM*4 +10 ) 
#define INV_B2_30   ( CLM*5 +0 ) 
#define INV_B2_31   ( CLM*5 +2 ) 
#define INV_B2_32   ( CLM*5 +3 ) 
#define INV_B2_33   ( CLM*5 +4 ) 
#define INV_B2_34   ( CLM*5 +5 ) 
#define INV_B2_35   ( CLM*5 +6 ) 
#define INV_B2_36   ( CLM*5 +7 ) 
#define INV_B2_37   ( CLM*5 +8 ) 
#define INV_B2_38   ( CLM*5 +10 ) 
#define INV_B2_39   ( CLM*6 +0 )
#define INV_B2_40   ( CLM*6 +2 ) 
#define INV_B2_41   ( CLM*6 +5 )
#define INV_B2_42   ( CLM*6 +8 ) 
#define INV_B2_43   ( CLM*6 +10 ) 
#define INV_B2_44   ( CLM*7 +3 )
#define INV_B2_45   ( CLM*7 +4 )
#define INV_B2_46   ( CLM*7 +6 )
#define INV_B2_47   ( CLM*7 +7 )


#define INV_C1_1    ( CLM*0 +4 )
#define INV_C1_2    ( CLM*0 +5 )
#define INV_C1_3    ( CLM*0 +6 )
#define INV_C1_4    ( CLM*0 +7 )
#define INV_C1_5    ( CLM*1 +1 )
#define INV_C1_6    ( CLM*1 +2 )
#define INV_C1_7    ( CLM*1 +3 )
#define INV_C1_8    ( CLM*1 +4 )
#define INV_C1_9    ( CLM*1 +5 )
#define INV_C1_10   ( CLM*1 +6 )
#define INV_C1_11   ( CLM*1 +7 )
#define INV_C1_12   ( CLM*1 +8 )
#define INV_C1_13   ( CLM*1 +9 )
#define INV_C1_14   ( CLM*1 +10 )
#define INV_C1_15   ( CLM*2 +0 )
#define INV_C1_16   ( CLM*2 +1 )
#define INV_C1_17   ( CLM*2 +2 )
#define INV_C1_18   ( CLM*2 +3 )
#define INV_C1_19   ( CLM*2 +4 )
#define INV_C1_20   ( CLM*2 +5 )
#define INV_C1_21   ( CLM*2 +6 )
#define INV_C1_22   ( CLM*2 +7 )
#define INV_C1_23   ( CLM*2 +8 )
#define INV_C1_24   ( CLM*2 +9 )
#define INV_C1_25   ( CLM*2 +10 )
#define INV_C1_26   ( CLM*2 +11 )
#define INV_C1_27   ( CLM*3 +0 )
#define INV_C1_28   ( CLM*3 +1 )
#define INV_C1_29   ( CLM*3 +2 )
#define INV_C1_30   ( CLM*3 +5 )
#define INV_C1_31   ( CLM*3 +6 )
#define INV_C1_32   ( CLM*3 +9 )
#define INV_C1_33   ( CLM*3 +10 )
#define INV_C1_34   ( CLM*3 +11 )
#define INV_C1_35   ( CLM*4 +0 )
#define INV_C1_36   ( CLM*4 +1 )
#define INV_C1_37   ( CLM*4 +2 )
#define INV_C1_38   ( CLM*4 +3 )
#define INV_C1_39   ( CLM*4 +4 )
#define INV_C1_40   ( CLM*4 +5 )
#define INV_C1_41   ( CLM*4 +6 )
#define INV_C1_42   ( CLM*4 +7 )
#define INV_C1_43   ( CLM*4 +8 )
#define INV_C1_44   ( CLM*4 +9 )
#define INV_C1_45   ( CLM*4 +10 )
#define INV_C1_46   ( CLM*4 +11 )
#define INV_C1_47   ( CLM*5 +3 )
#define INV_C1_48   ( CLM*5 +4 )
#define INV_C1_49   ( CLM*5 +7 )
#define INV_C1_50   ( CLM*5 +8 )
#define INV_C1_51   ( CLM*6 +2 )
#define INV_C1_52   ( CLM*6 +3 )
#define INV_C1_53   ( CLM*6 +5 )
#define INV_C1_54   ( CLM*6 +6 )
#define INV_C1_55   ( CLM*6 +7 )
#define INV_C1_56   ( CLM*6 +8 )
#define INV_C1_57   ( CLM*6 +9 )
#define INV_C1_58   ( CLM*7 +1 )
#define INV_C1_59   ( CLM*7 +2 )
#define INV_C1_60   ( CLM*7 +10 )
#define INV_C1_61   ( CLM*7 +11 )


#define INV_C2_1    ( CLM*0 +4 )
#define INV_C2_2    ( CLM*0 +5 )
#define INV_C2_3    ( CLM*0 +6 )
#define INV_C2_4    ( CLM*0 +7 )    
#define INV_C2_5    ( CLM*1 +1 )
#define INV_C2_6    ( CLM*1 +2 )
#define INV_C2_7    ( CLM*1 +3 )
#define INV_C2_8    ( CLM*1 +4 )
#define INV_C2_9    ( CLM*1 +5 )
#define INV_C2_10   ( CLM*1 +6 )
#define INV_C2_11   ( CLM*1 +7 )
#define INV_C2_12   ( CLM*1 +8 )
#define INV_C2_13   ( CLM*1 +9 )
#define INV_C2_14   ( CLM*1 +10 )   
#define INV_C2_15   ( CLM*2 +0 )
#define INV_C2_16   ( CLM*2 +1 )
#define INV_C2_17   ( CLM*2 +2 )
#define INV_C2_18   ( CLM*2 +3 )
#define INV_C2_19   ( CLM*2 +4 )
#define INV_C2_20   ( CLM*2 +5 )
#define INV_C2_21   ( CLM*2 +6 )
#define INV_C2_22   ( CLM*2 +7 )
#define INV_C2_23   ( CLM*2 +8 )
#define INV_C2_24   ( CLM*2 +9 )
#define INV_C2_25   ( CLM*2 +10 )
#define INV_C2_26   ( CLM*2 +11 )
#define INV_C2_27   ( CLM*3 +0 )
#define INV_C2_28   ( CLM*3 +1 )
#define INV_C2_29   ( CLM*3 +2 )
#define INV_C2_30   ( CLM*3 +5 )
#define INV_C2_31   ( CLM*3 +6 )
#define INV_C2_32   ( CLM*3 +9 )
#define INV_C2_33   ( CLM*3 +10 )
#define INV_C2_34   ( CLM*3 +11 )
#define INV_C2_35   ( CLM*4 +0 )
#define INV_C2_36   ( CLM*4 +1 )
#define INV_C2_37   ( CLM*4 +2 )
#define INV_C2_38   ( CLM*4 +3 )
#define INV_C2_39   ( CLM*4 +4 )
#define INV_C2_40   ( CLM*4 +5 )
#define INV_C2_41   ( CLM*4 +6 )
#define INV_C2_42   ( CLM*4 +7 )
#define INV_C2_43   ( CLM*4 +8 )
#define INV_C2_44   ( CLM*4 +9 )
#define INV_C2_45   ( CLM*4 +10 )
#define INV_C2_46   ( CLM*4 +11 )
#define INV_C2_47   ( CLM*5 +2 )
#define INV_C2_48   ( CLM*5 +3 )
#define INV_C2_49   ( CLM*5 +4 )
#define INV_C2_50   ( CLM*5 +7 )
#define INV_C2_51   ( CLM*5 +8 )
#define INV_C2_52   ( CLM*5 +9 )
#define INV_C2_53   ( CLM*6 +1 )
#define INV_C2_54   ( CLM*6 +2 )
#define INV_C2_55   ( CLM*6 +4 )
#define INV_C2_56   ( CLM*6 +5 )
#define INV_C2_57   ( CLM*6 +6 )
#define INV_C2_58   ( CLM*6 +7 )
#define INV_C2_59   ( CLM*6 +9 )
#define INV_C2_60   ( CLM*6 +10 )
#define INV_C2_61   ( CLM*7 +2 )
#define INV_C2_62   ( CLM*7 +3 )
#define INV_C2_63   ( CLM*7 +8 )
#define INV_C2_64   ( CLM*7 +9 )



/*==========================================================================*/
/*                                                                          */
/*==========================================================================*/
class CCSL
{
public:
    CCSL();                 /* constructor for intializing                  */
    void Ini();
    void SetVram();
    void clear_screen();
    UB   set_cursor( UB, UB );
    UB   set_line_color( UB, UB, UB );
    UB   put_char( UB, UB, UB );
    UB   put_char( UB );
    void print(const char *);
    
private:
    UB cursor_x, cursor_y;
    int numRows;
    int numCols;
};

