extern STDOUT               ; from constants.asm
extern dataArr, dataIndex   ; from start.asm
extern print                ; from print.asm

section .text
global printData            ; make this label available to other files
; brief:
;   prints the character at dataIndex in the dataArr
printData:
    lea r10, dataArr        ; load dataArr address into r10
    add r10, [dataIndex]    ; add the offset to the address
    mov rdi, r10            ; move the address to rdi
    mov si, 1               ; bytes to print
    mov dl, STDOUT          ; file descriptor
    call print              ; call the print function

    ret                     ; return