	SECTION code_driver
	PUBLIC banked_call
	EXTERN l_jphl
	defc ZX_BANK_IOPORT = 0x7ffd
	INCLUDE "target/zx/def/sysvar.def"

banked_call:
    di				; critical section start
    pop     hl			; Return address into HL
				; Compiler stuffs 4 bytes there: bank (16 bits) and function addr (16 bits)

    ld      a,(SV_BANKM)	; save current bank register value on the stack
    push    af

    ld      e,(hl)		; Fetch the call address into DE
    inc     hl
    ld      d,(hl)
    inc     hl

    ld      a,(hl)		; Get the bank number in A
    inc     hl	

    inc     hl			; Skip the 4th byte

    push    hl			; Push the real return address

    ld      bc,ZX_BANK_IOPORT	; prepare register value to switch bank
    or      0x10		; A contains the bank nr
    ld      (SV_BANKM),a	; save the new bank value
    out     (c),a		; ...and do the switch

    ei				; critical section end

    ld      l,e			; DE contains the address to call to
    ld      h,d			; so call there
    call    l_jphl		; ints are enabled here

    di				; again, critical section start

    pop     bc			; Get the return address into BC
    pop     af			; Pop the old bank
    push    bc			; Push again return address

    ld      bc,ZX_BANK_IOPORT	; restore switch to the old bank and save
    ld      (SV_BANKM),a	; the bank register value
    out     (c),a

    ei				; critical section end

    ret
