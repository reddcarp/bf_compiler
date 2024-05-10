section .data
global LF, EXIT_SUCCESS, EXIT_ERROR, STDIN, STDOUT, STDERR ; used to export symbols to be accessed from other files
LF              equ 10  ; line feed
EXIT_SUCCESS    equ 0   ; success code
EXIT_ERROR      equ 1   ; error code
STDIN           equ 0   ; standard input
STDOUT          equ 1   ; standard output
STDERR          equ 2   ; standard error

global SYS_read, SYS_write, SYS_exit ; used to export symbols to be accessed from other files
SYS_read        equ 0   ; read sys call
SYS_write       equ 1   ; write sys call
SYS_exit        equ 60  ; exit sys call