%include "macros.asm"

extern dataIndex, dataArrMaxSize            ; from data.asm
extern EXIT_ERROR, STDERR, LF               ; from constants.asm
extern print                                ; from print.asm

section .data
error_msg db "Error: buffer overflow", LF
error_size equ $ - error_msg

section .text
global increaseIndex    ; make this label available to other files
; brief:
;   decrease the index of the data array and performs safety checks
; args:
;   rdi -> amount to increase the index by
increaseIndex:
    add [dataIndex], rdi                    ; increase dataIndex by rdi
    cmp qword [dataIndex], dataArrMaxSize   ; compare dataIndex to dataArrMaxSize
    jge .error                              ; if dataIndex >= dataArrMaxSize, jump to error
    ret                                     ; return
.error:
    mov rdi, error_msg                      ; load address of error_msg into rdi
    mov si, error_size                      ; load size of error_msg into si
    mov dl, STDERR                          ; load STDERR into dl
    call print                              ; print error message
    exit EXIT_ERROR                         ; exit with error code