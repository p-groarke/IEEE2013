

LOOPW   0100             ;loop ici, use CX et non ECX
PUSH    AX
POP     SI
MOV     BX,AX            ;bx = ax
SHR     AX,1             ;shift ax right 1, bit de droite dans CF
RCL     CX,1             ;rotate left: shift left 1, right most bit set to previous CF, CF = bit enlever a gauche
JNZ     0106             ;Short Jump if Not Zero (not equal) to adresse 106
XCHG    AX,CX            ;ax = cx; cx = ax
MOV     DX,0201          ;dx = 0201
ROL     DX,1             ;shift all bits left, the bit that goes off is set to CF and the same bit is inserted to the right-most position
SHR     BX,1             ;shift bx right 1, bit de droite dans CF, 0 ajouter a gauche
RCL     CX,1             ;rotate left: shift left 1, bit de droite setter a previous CF, CF = bit enlever a gauche
CMP     DH,BL            ;compare
JLE     0110             ;if (DH <= BL), goto 110 (Signed)
CMP     BL,DL            ;compare
JLE     0124             ;if (BL <= DL), goto 124 (signed)
ROR     BX,1             ;rotate right: shift right 1, CF= bit enlever a droite, bit enlever a droite ajouter a gauche
RCL     CX,1             ;rotate left: shift left 1, right most bit set to previous CF, CF = bit enlever a gauche
ROL     BX,1             ;shift all bits left, the bit that goes off is set to CF and the same bit is inserted to the right-most position
SUB     AH,DL            ;AH - DL
DEC     DX               ;DX - 1
AND     AL,DL            ;DL & AL
AND     DX,SI            ;SI & DX
CMP     DL,AL            ;compare
SBB     BL,AH            ;BL - AH - CF















0100 E2FE              LOOPW   0100             ;loop au debut 100 foix, use CX et non ECX
0102 50                PUSH    AX
0103 5E                POP     SI
0104 89C3              MOV     BX,AX            ;bx = ax
0106 D1E8              SHR     AX,1             ;shift ax right 1, bit de droite dans CF
0108 D1D1              RCL     CX,1             ;rotate left: shift left 1, right most bit set to previous CF, CF = bit enlever a gauche
010A 75FA              JNZ     0106             ;Short Jump if Not Zero (not equal) to adresse 106
010C 91                XCHG    AX,CX            ;ax = cx; cx = ax
010D BA0102            MOV     DX,0201          ;dx = 0201
0110 D1C2              ROL     DX,1             ;shift all bits left, the bit that goes off is set to CF and the same bit is inserted to the right-most position
0112 D1EB              SHR     BX,1             ;shift bx right 1, bit de droite dans CF, 0 ajouter a gauche
0114 D1D1              RCL     CX,1             ;rotate left: shift left 1, bit de droite setter a previous CF, CF = bit enlever a gauche
0116 38DE              CMP     DH,BL            ;compare
0118 7EF6              JLE     0110             ;if (DH <= BL), goto 110 (Signed)
011A 38D3              CMP     BL,DL            ;compare
011C 7E06              JLE     0124             ;if (BL <= DL), goto 124 (signed)
011E D1CB              ROR     BX,1             ;rotate right: shift right 1, CF= bit enlever a droite, bit enlever a droite ajouter a gauche
0120 D1D1              RCL     CX,1             ;rotate left: shift left 1, right most bit set to previous CF, CF = bit enlever a gauche
0122 D1C3              ROL     BX,1             ;shift all bits left, the bit that goes off is set to CF and the same bit is inserted to the right-most position
0124 28D4              SUB     AH,DL            ;AH - DL
0126 4A                DEC     DX               ;DX - 1
0127 20D0              AND     AL,DL            ;DL & AL
0129 21F2              AND     DX,SI            ;SI & DX
012B 38C2              CMP     DL,AL            ;compare
012D 18E3              SBB     BL,AH            ;BL - AH - CF
