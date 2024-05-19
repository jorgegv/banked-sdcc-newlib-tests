#include <stdio.h>

#pragma bank 7

int banked_function7( int a ) __banked __z88dk_fastcall {
    printf( "** BANK7.a = 0x%04X\n", a );
    return 0x0002 * a;
}
