# sccz80, classic
#CFLAGS = --list -s -m --c-code-in-asm -lndos -create-app -o banked.bin

# sccz80, newlib
#CFLAGS = --list -s -m -clib=new --c-code-in-asm -create-app -o banked.bin

# sdcc, classic
#CFLAGS = --list -s -m -compiler=sdcc --c-code-in-asm -lndos

# sdcc, newlib
CFLAGS = --list -s -m -compiler=sdcc -clib=sdcc_iy --c-code-in-asm -pragma-include zpragma.inc


#OBJS = bcall.o main.o bank6.o
OBJS = zx_banked_call.o main.o bank6.o

%.o: %.c
	zcc +zx -vn -c $(CFLAGS) $<

%.o: %.asm
	zcc +zx -vn -c $(CFLAGS) $<

banked.bin: $(OBJS)
	zcc +zx -vn $(CFLAGS) $(OBJS) -create-app -o banked.bin

all: banked.bin

clean:
	-rm *.bin *.lis *.sym *.map *.tap *.o

run:
	fuse --machine 128 banked.tap
