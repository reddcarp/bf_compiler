; include macro file (ie: copy paste it's content here)
%include "macros.asm"

extern EXIT_SUCCESS, LF                         ; from constants.asm
extern decreaseIndex                            ; from decreaseIndex.asm
extern increaseIndex                            ; from increaseIndex.asm
extern printData                                ; from printData.asm
extern readData                                 ; from readData.asm
extern dataArr, dataIndex                       ; from data.asm

section .text
global _start
_start:
    call readData
    call printData

    ; mov byte [data], 'A'
    ; lea rdi, data
    ; mov si, 1
    ; mov dl, 1
    ; call print

    ; mov dil, 'C'
    ; call printChar
    ; mov dil, LF
    ; call printChar
    exit EXIT_SUCCESS