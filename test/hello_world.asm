        LDR r0, tx_fifo     ; Load Address of TX_FIFO into register 2
        ADD r2, r2, #10     ; Load r2 with Address of 1st letter of string
loop    ADD r3, r3, #1      ; Increment r2 and r3
        ADD r2, r2, #1
        LDR r1, r2          ; Load Next Letter (Memory at r2) into r1
        STR r1, r0          ; Store r1 into TX_FIFO (UART_TX)
        CMP r3, #16         ; Compare current loops with total length
        BEQ #2              ; If == 16 then halt
        B loop              ; Else loop to Line 3
        HLT
tx_fifo 0xF0000000          ; TX_FIFO = 0xF0000000
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
