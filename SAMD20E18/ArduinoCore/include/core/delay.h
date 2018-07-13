/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _DELAY_
#define _DELAY_

#include <stdint.h>
#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32_t millis();
uint32_t micros();
void     delay( uint32_t dwMs );
void delayMicroseconds( uint32_t us );
///**
//* \brief Pauses the program for the amount of time (in microseconds) specified
//as parameter.
//*
//* \param dwUs the number of microseconds to pause (uint32_t)
//*/
// static __inline__ void delayMicroseconds( unsigned int )
// __attribute__((always_inline, unused)) ;  static __inline__ void
// delayMicroseconds( unsigned int usec )
//{
// if ( usec == 0 )
//{
// return ;
//}
//
///*
//*  The following loop:
//*
//*    for (; ul; ul--) {
//*      __asm__ volatile("");
//*    }
//*
//*  produce the following assembly code:
//*
//*    loop:
//*      subs r3, #1        // 1 Core cycle
//*      bne.n loop         // 1 Core cycle + 1 if branch is taken
//*/
//
//// VARIANT_MCK / 1000000 == cycles needed to delay 1uS
////                     3 == cycles used in a loop
// uint32_t n = usec * (VARIANT_MCK / 1000000) / 3;
//__asm__ __volatile__(
//"1:              \n"
//"   sub %0, #1   \n" // substract 1 from %0 (n)
//"   bne 1b       \n" // if result is not 0 jump to 1
//: "+r" (n)           // '%0' is n variable with RW constraints
//:                    // no input
//:                    // no clobber
//);
//// https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html
//// https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html#Volatile
//}

#ifdef __cplusplus
}
#endif

#endif /* _DELAY_ */
