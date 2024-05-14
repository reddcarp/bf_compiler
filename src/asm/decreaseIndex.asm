%include "macros.asm"

extern dataIndex                ; from data.asm
extern EXIT_ERROR, STDERR, LF   ; from constants.asm
extern print                    ; from print.asm

section .data
error_msg db "Error: buffer underflow", LF
error_size equ $ - error_msg

section .text
global decreaseIndex            ; make this label available to other files
; brief:
;   decrease the index of the data array and performs safety checks
; args:
;   rdi -> amount to decrease the index by
decreaseIndex:
    cmp [dataIndex], rdi        ; compare dataIndex to di
    jl  .error                  ; if dataIndex < di, jump to error
    sub [dataIndex], rdi        ; decrease dataIndex by di
    ret                         ; return
.error:
    mov rdi, error_msg          ; load address of error_msg into rdi
    mov si, error_size          ; load size of error_msg into si
    mov dl, STDERR              ; load STDERR into dl
    call print                  ; print error message
    exit EXIT_ERROR             ; exit with error code