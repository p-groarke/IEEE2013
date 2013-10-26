

0100 E2FE              LOOPW   0100             ;loop 100 foix
0102 50                PUSH    AX
0103 5E                POP     SI
0104 89C3              MOV     BX,AX            ;bx = ax
0106 D1E8              SHR     AX,1             ;shift ax right 1, bit de droite dans CF
0108 D1D1              RCL     CX,1             ;rotate left, shift left 1, right most bit set to previous CF, CF = bit enlever a gauche
010A 75FA              JNZ     0106             ;Short Jump if Not Zero (not equal) to adresse 106
010C 91                XCHG    AX,CX            ;ax = cx; cx = ax
010D BA0102            MOV     DX,0201          ;dx = 0201
0110 D1C2              ROL     DX,1             ;shift all bits left, the bit that goes off is set to CF and the same bit is inserted to the right-most position
0112 D1EB              SHR     BX,1
0114 D1D1              RCL     CX,1
0116 38DE              CMP     DH,BL
0118 7EF6              JLE     0110
011A 38D3              CMP     BL,DL
011C 7E06              JLE     0124
011E D1CB              ROR     BX,1
0120 D1D1              RCL     CX,1
0122 D1C3              ROL     BX,1
0124 28D4              SUB     AH,DL
0126 4A                DEC     DX
0127 20D0              AND     AL,DL
0129 21F2              AND     DX,SI
012B 38C2              CMP     DL,AL
012D 18E3              SBB     BL,AH
