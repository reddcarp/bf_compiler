section .data
global dataArr, dataArrMaxSize, dataIndex       ; used to export symbols to be accessed from other files
dataArrMaxSize equ 300                          ; maximum size of dataArr
dataArr TIMES dataArrMaxSize db 0               ; 300 element bytes array initialized to 0
dataIndex dq 0                                  ; 64 bit integer variable initialized to 0