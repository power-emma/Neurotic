ADD r0, r0, #1  ; Set r0 to 1
ADD r2, r1, r0  ; Start of Loop r2 = r1 + r0 
ADD r0, r1, #0  ; Copy r0 into r1
ADD r1, r2, #0  ; Copy r2 into r1
ADD r5, r2, #0  ; Copy r2 into r5
ADD r3, r3, #1  ; Increment r3 (Loop Counter)
CMP r3, #40     ; Compare r3 and 40
BEQ #1          ; If r3 = 40 skip the next line
B #-8           ; Else; Loop back to line 2
HLT
LDR r0, [10]        ; Load Address of TX_FIFO into register 2
ADD r2, r2, #10     ; Load r2 with Address of 1st letter of string
ADD r3, r3, #1      ; Increment r2 and r3
ADD r2, r2, #1
LDR r1, r2          ; Load Next Letter (Memory at r2) into r1
STR r1, r0          ; Store r1 into TX_FIFO (UART_TX)
CMP r3, #16         ; Compare current loops with total length
BEQ #1              ; If == 16 then halt
B #-7               ; Else loop to Line 3
0xF0000000          ; TX_FIFO = 0xF0000000
0x48    ;H
0x65    ;e
0x6C    ;l
0x6C    ;l
0x6F    ;o
0x20    ;(space)
0x77    ;w
0x6F    ;o
0x72    ;r
0x6C    ;l
0x64    ;d
0x20    ;(space)
0x3A    ;:
0x33    ;3
0x0A    ;\n