;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; RAGE1 CUSTOM MEMORY MODEL FOR THE LINKER
;;
;; See doc/BANKING-DESIGN, section "C Binary Linker Memory Map"
;; for the design that led to using this file.
;;
;; This file is published under the same license as Z88DK
;; itself
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; memory model ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

SECTION CODE

org __crt_org_code

IF (__crt_org_vector_table = -0x80) || (__crt_org_vector_table = -0x100)

section code_crt_interrupt_vector_table
section code_crt_start

ENDIF

;; load banks if any
IF !DEFINED_CRT_DISABLELOADER
  call   loadbanks
ENDIF

;; regular memory map
section code_crt_init
section code_crt_main
section code_crt_exit
section code_crt_return
section code_crt_common
;; the following sections have been moved from their normal places so
;; that game data is placed at the start of the memory map
section rodata_input
section rodata_compiler
section rodata_sound_bit
section data_compiler
section data_arch
section data_stdlib
section data_sound_bit
section bss_compiler
section bss_error
section bss_stdlib          

IF (__crt_org_vector_table) && (__crt_org_vector_table != -0x80) && (__crt_org_vector_table != -0x100)

section code_crt_interrupt_vector_table

ENDIF

section code_compiler
section code_driver
section code_font
section code_clib
  include "../../clib_code.inc"
section code_lib
section code_user
;; place the bit_beepfx routine and pals in non-contended memory
;; above code_compiler section
section code_sound_bit

section rodata_align_256
align 256

section rodata_align_128
align 128

section rodata_align_64
align 64

section rodata_align_32
align 32

section rodata_align_16
align 16

section rodata_align_8
align 8

section rodata_align_4
align 4

section rodata_align_2
align 2

section rodata_driver
section rodata_font
section rodata_clib
  include "../../clib_rodata.inc"
  ;;section rodata_error_strings
  ;;section rodata_error_string_end
  ;;defb 0
section rodata_lib
;; moved to the start of the memory map
;;section rodata_compiler
section rodata_user

SECTION CODE_END

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

SECTION DATA

IF __crt_org_data

   org __crt_org_data

ELSE

   IF __crt_model
      
      "DATA section address must be specified for rom models"
   
   ENDIF

ENDIF

section data_align_256
align 256

section data_align_128
align 128

section data_align_64
align 64

section data_align_32
align 32

section data_align_16
align 16

section data_align_8
align 8

section data_align_4
align 4

section data_align_2
align 2

section smc_jump_vectors
section smc_driver
section smc_font
section smc_clib
  include "../../clib_smc.inc"
section smc_lib
section smc_compiler
section smc_user

section data_driver
section data_font
section data_clib
  include "../../clib_data.inc"
  ;;section data_fcntl_stdio_heap_head
  ;;section data_fcntl_stdio_heap_body
  ;;section data_fcntl_stdio_heap_tail
  ;;section data_fcntl_fdtable_body
section data_lib
;; moved to the start of the memory map
;;section data_compiler
section data_user

SECTION DATA_END

;; this must be at the end of the memory map
;; can be before BSS
IF !DEFINED_CRT_DISABLELOADER
loadbanks:
  IF DEFINED_CRT_PLUS3LOADER
      INCLUDE "zx_p3loader.asm"
  ELSE
      INCLUDE "zx_tapeloader.asm"
  ENDIF
ENDIF

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

SECTION BSS

IF __crt_org_bss

   org __crt_org_bss

ELSE

   IF __crt_model

      org -1

   ENDIF

ENDIF

section bss_align_256
align 256

section bss_align_128
align 128

section bss_align_64
align 64

section bss_align_32
align 32

section bss_align_16
align 16

section bss_align_8
align 8

section bss_align_4
align 4

section bss_align_2
align 2

section bss_driver
section bss_font
section bss_clib
  include "../../clib_bss.inc"
section bss_lib
;; moved to the start of he memory map
;;section bss_compiler
section bss_user

section BSS_UNINITIALIZED
SECTION BSS_END

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

IF (__crt_org_vector_table = 0)

section code_crt_interrupt_vector_table
org 0

ENDIF

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Define Memory Banks
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    IFNDEF CRT_ORG_BANK_0
        defc CRT_ORG_BANK_0 = 0xc000
    ENDIF

    IFNDEF CRT_ORG_BANK_1
        defc CRT_ORG_BANK_1 = 0xc000
    ENDIF

    IFNDEF CRT_ORG_BANK_2
        defc CRT_ORG_BANK_2 = 0xc000
    ENDIF

    IFNDEF CRT_ORG_BANK_3
        defc CRT_ORG_BANK_3 = 0xc000
    ENDIF

    IFNDEF CRT_ORG_BANK_4
        defc CRT_ORG_BANK_4 = 0xc000
    ENDIF

    IFNDEF CRT_ORG_BANK_5
        defc CRT_ORG_BANK_5 = 0xc000
    ENDIF

    IFNDEF CRT_ORG_BANK_6
        defc CRT_ORG_BANK_6 = 0xc000
    ENDIF

    IFNDEF CRT_ORG_BANK_7
        defc CRT_ORG_BANK_7 = 0xc000
    ENDIF


    SECTION BANK_0
    org 0x000000 + CRT_ORG_BANK_0
    SECTION CODE_0
    SECTION RODATA_0
    SECTION DATA_0
    SECTION BSS_0
    SECTION BANK_0_END

    SECTION BANK_1
    org 0x010000 + CRT_ORG_BANK_1
    SECTION CODE_1
    SECTION RODATA_1
    SECTION DATA_1
    SECTION BSS_1
    SECTION BANK_1_END

    SECTION BANK_2
    org 0x020000 + CRT_ORG_BANK_2
    SECTION CODE_2
    SECTION RODATA_2
    SECTION DATA_2
    SECTION BSS_2
    SECTION BANK_2_END

    SECTION BANK_3
    org 0x030000+ CRT_ORG_BANK_3
    SECTION CODE_3
    SECTION RODATA_3
    SECTION DATA_3
    SECTION BSS_3
    SECTION BANK_3_END

    SECTION BANK_4
    org 0x040000 + CRT_ORG_BANK_4
    SECTION CODE_4
    SECTION RODATA_4
    SECTION DATA_4
    SECTION BSS_4
    SECTION BANK_4_END

    SECTION BANK_5
    org 0x050000 + CRT_ORG_BANK_5
    SECTION CODE_5
    SECTION RODATA_5
    SECTION DATA_5
    SECTION BSS_5
    SECTION BANK_5_END

    SECTION BANK_6
    org 0x060000 + CRT_ORG_BANK_6
    SECTION CODE_6
    SECTION RODATA_6
    SECTION DATA_6
    SECTION BSS_6
    SECTION BANK_6_END

    SECTION BANK_7
    org 0x070000 + CRT_ORG_BANK_7
    SECTION CODE_7
    SECTION RODATA_7
    SECTION DATA_7
    SECTION BSS_7
    SECTION BANK_7_END
