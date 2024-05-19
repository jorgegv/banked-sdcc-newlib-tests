// zcc +zx -vn --list -s -m --c-code-in-asm -lndos main.c bank6.c -create-app -o banked.bin

#include <stdio.h>

extern int banked_function1( void ) __banked;
extern int banked_function3( void ) __banked;
extern int banked_function4( void ) __banked;
extern int banked_function6( void ) __banked;
extern int banked_function7( int a ) __banked __z88dk_fastcall;

void main( void ) {
    printf( "Hello world from main bank!\n" );
    printf( "** Value from bank 1: 0x%04x\n", banked_function1() );
    printf( "** Value from bank 3: 0x%04x\n", banked_function3() );
    printf( "** Value from bank 4: 0x%04x\n", banked_function4() );
    printf( "** Value from bank 6: 0x%04x\n", banked_function6() );
    printf( "** Value from bank 7: 0x%04x\n", banked_function7(2) );
//    while ( 1 ) ;
}
