/*****************************************************************************
    System Name : Arduino 2010
    File Name   : nabe_common.h
    Content     : common headder
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

#ifndef COMMON_H
#define COMMON_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

/*==========================================================================*/
/* typedef                                                                  */
/*==========================================================================*/
typedef signed   char       SB;             /* signed    8bit               */
typedef unsigned char       UB;             /* unsigned  8bit               */
typedef signed   short      SH;             /* siged    16bit               */
typedef unsigned short      UH;             /* unsigned 16bit               */
typedef signed   long       SW;             /* signed   32bit               */
typedef unsigned long       UW;             /* unsined  32bit               */
typedef unsigned char       BL;             /* boolean                      */

/*==========================================================================*/
/* defines                                                                  */
/*==========================================================================*/
#define ON      1
#define OFF     0
#define ERROR   (-1)
#define EOF	(-1)

#endif  /* COOMON_H */

