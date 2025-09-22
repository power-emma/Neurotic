LDR r0, #1
ADD r2, r1, r0
LDR r0, r1
LDR r1, r2
LDR r12, r2
ADD r3, r3, #1
CMP r3, #40
BEQ #1
B #-8
HLT
