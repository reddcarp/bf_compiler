extern dataArr, dataIndex           ; from data.asm
extern STDIN, STDOUT, SYS_read, LF  ; from constants.asm
extern print                        ; from print.asm

section .data
msg db "Enter a character: "
msg_size equ $ - msg

section .text
global readData
; brief:
;   reads a character from STDIN and stores it in dataArr[dataIndex]
;   flushes the input buffer if more than one character is entered
readData:
    mov rdi, msg                    ; load address of msg into rdi
    mov si, msg_size                ; load size of msg_size into si
    mov dl, STDOUT                  ; load STDOUT into dl
    call print                      ; print message

    lea r10, dataArr                ; r10 = dataArr
    add r10, [dataIndex]            ; r10 = dataArr + dataIndex ie. dataArr[dataIndex]

    mov rax, SYS_read               ; system call number for read
    mov rdi, STDIN                  ; file descriptor for standard input
    mov rsi, r10                    ; buffer to read into
    mov rdx, 1                      ; number of bytes to read
    syscall                         ; call the kernel to perform the system call

    cmp byte [r10], LF              ; check if the character read is a newline
    je end                          ; if it is, end the program

    sub rsp, 1                      ; allocate space for a character on the stack (it grows downwards)
flushStdin:
    mov rax, SYS_read               ; system call number for read
    mov rdi, STDIN                  ; file descriptor for standard input
    mov rsi, rsp                    ; buffer to read into
    mov rdx, 1                      ; number of bytes to read
    syscall                         ; call the kernel to perform the system call

    cmp byte [rsp], LF              ; check if the character read is a newline
    jne flushStdin                  ; if not, read the next character

    add rsp, 1                      ; deallocate the space for the character on the stack (restore rsp to its original )
end:
    ret                             ; return to the caller (the return address is stored in the stack rsp register)