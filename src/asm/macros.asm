extern SYS_exit             ; from constants.asm

%macro exit 1
    mov rax, SYS_exit       ; system call number for exit
    mov rdi, %1             ; status code = %1
    syscall                 ; call the kernel to perform the system call
%endmacro

%macro addToData 1
    lea r10, dataArr        ; r10 = dataArr
    add r10, [dataIndex]    ; r10 = dataArr + dataIndex ie. dataArr[dataIndex]
    add byte [r10], %1      ; dataArr[dataIndex] += %1
%endmacro

%macro subFromData 1
    lea r10, dataArr        ; r10 = dataArr
    add r10, [dataIndex]    ; r10 = dataArr + dataIndex ie. dataArr[dataIndex]
    sub byte [r10], %1      ; dataArr[dataIndex] -= %1
%endmacro

%macro jmpIfDataZero 1
    lea r10, dataArr        ; r10 = dataArr
    add r10, [dataIndex]    ; r10 = dataArr + dataIndex ie. dataArr[dataIndex]
    cmp byte [r10], 0       ; compare dataArr[dataIndex] with 0
    je %1                   ; jump to %1 if dataArr[dataIndex] == 0
%endmacro

%macro jmpIfDataNotZero 1
    lea r10, dataArr        ; r10 = dataArr
    add r10, [dataIndex]    ; r10 = dataArr + dataIndex ie. dataArr[dataIndex]
    cmp byte [r10], 0       ; compare dataArr[dataIndex] with 0
    jne %1                  ; jump to %1 if dataArr[dataIndex] != 0
%endmacro