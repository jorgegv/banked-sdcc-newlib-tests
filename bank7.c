#include <stdio.h>

#pragma bank 7

int banked_function7( int a ) __banked {
    printf( "** BANK7.a = 0x%04X\n", a );
    return 0x0002 * a;
}
