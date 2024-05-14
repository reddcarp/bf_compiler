extern SYS_write            ; from constants.asm

section .text
global print                ; make this label available to other files
; brief:
;   prints a character to the standard output
; args:
;   rdi -> pointer to the string to print
;   si  -> length of the string to print (16-bit, ie. 0-65535)
;   dl  -> file descriptor for the write system call (8-bit, ie. 0-255)
print:
    mov     r10, rdi        ; save the address of the character to print in the r10 temporary register

    mov     rax, SYS_write  ; system call number for write
    movzx   rdi, dl         ; file descriptor for the write system call
    movzx   rdx, si         ; number of characters to print
    mov     rsi, r10        ; address of the characters to print
    syscall                 ; invoke the write system call

    ret                     ; return