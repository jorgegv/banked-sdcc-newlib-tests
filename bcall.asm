	SECTION code_driver
	PUBLIC banked_call
	EXTERN l_jphl
	defc ZX_BANK_IOPORT = 0x7ffd
	INCLUDE "target/zx/def/sysvar.def"

banked_call:
    di				; critical section start
    pop     hl			; Return address into HL
				; Compiler stuffs 4 bytes there: bank (16 bits) and function addr (16 bits)

    ld      a,(SV_BANKM)	; save previous bank register value on the stack
    push    af

    ld      e,(hl)		; Fetch the call address into DE (2 bytes)
    inc     hl
    ld      d,(hl)
    inc     hl

    ld      a,(hl)		; Get the bank number in A (1 byte)
    inc     hl	
    inc     hl			; Skip the 4th byte

    ex      (sp),hl		; HL now contains the real return address (4
				; bytes past the call instruction); push it
				; and get the previous bank register value
				; in H

    push    hl			; push previous bank register value again

    ld      l,a			; save new bank number
    ld	    a,h			; h = previous bank register value
    and     0xf8		; mask out bank number
    or      l			; set new bank number
				; now A contains the new bank number and the
				; saved ROM config

    ld      bc,ZX_BANK_IOPORT	; prepare register value to switch bank
    ld      (SV_BANKM),a	; save the new bank value
    out     (c),a		; ...and do the switch

    ei				; critical section end

    ld      l,e			; DE contains the address to call to
    ld      h,d			; so call there
    call    l_jphl		; ints are enabled here

    di				; again, critical section start

    pop     af			; Pop the old bank

    ld      bc,ZX_BANK_IOPORT	; restore switch to the old bank and save
    ld      (SV_BANKM),a	; the bank register value
    out     (c),a

    ei				; critical section end

    ret
