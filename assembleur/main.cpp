//
//  main.cpp
//  assembleur
//
//  Created by Philippe Groarke on 2013-10-26.
//  Copyright (c) 2013 Groarke and co. All rights reserved.
//

#include <iostream>
#include <bitset>

using namespace std;

int main(int argc, const char * argv[])
{

    unsigned long input;

    int alSize = 8;

    int Zflag = 0;
    int CF = 0;
    int CFTemp = 0;

    bitset<16> AX(0);
    bitset<16> BX(0);
    bitset<16> CX(0);
    bitset<16> DX(0);
    bitset<16> SI(0);
    bitset<16> temp(0);

    bitset<8> AH;
    bitset<8> AL;
    bitset<8> BL;
    bitset<8> CL;
    bitset<8> DH;
    bitset<8> DL;

    cin >> input;

    do {
        AL = input;

        AX = int8_t(AL.to_ulong());

        BX = AX;

    centsix:

        CF = AX[0];
        AX>>=1;

        CFTemp = CX[63];
        CX<<=1;
        CX[0] = CF;
        CF = CFTemp;

        if (Zflag != 0) goto centsix;

        temp = AX;
        AX = CX;
        CX = temp;

    centdix:

        DX = 201;

        CF = DX[63];
        DX<<=1;
        DX[0] = CF;

        CF = BX[0];
        BX>>=1;
        BX[63] = 0;

        CFTemp = CX[63];
        CX<<=1;
        CX[0] = CF;
        CF = CFTemp;

        for (int i = alSize; i < alSize*2; ++i)
        {
            DH[i-alSize] = DX[i];
        }

        if (DH.to_ulong() <= int16_t(BX.to_ulong())) goto centdix;

        if (int16_t(BX.to_ulong()) <= int16_t(DX.to_ulong())) goto centvingtquatre;

        CF = BX[0];
        BX>>=1;
        BX[63] = CF;

        CFTemp = CX[63];
        CX<<=1;
        CX[0] = CF;
        CF = CFTemp;

        CF = BX[63];
        BX<<=1;
        BX[0] = CF;

    centvingtquatre:

        for (int i = alSize; i < alSize*2; ++i)
        {
            AH[i-alSize] = AX[i];
        }

        int8_t tempSub = int8_t(AH.to_ulong());

        tempSub -= int8_t(DX.to_ulong());

        AH = tempSub;

        for (int i = alSize; i < alSize*2; ++i)
        {
            AX[i] = AH[i-alSize];
        }

        int16_t tempSub16 = 0;

        tempSub16 = int16_t(DX.to_ullong());
        tempSub16 -= 1;
        DX = tempSub16;

        AL = int8_t(AX.to_ulong());
        DL = int8_t(DX.to_ulong());
        AL&=DL;

        for (int i = 0; i < alSize; ++i)
        {
            AX[i] = AL[i];
            DX[i] = DL[i];
        }

        SI&=DX;

        // Compare
        if (int8_t(DX.to_ulong()) != int8_t(AL.to_ulong())) Zflag = 1;
        else Zflag = 0;

        tempSub = int8_t(BX.to_ulong());

        tempSub -= CF;

        for (int i = alSize; i < alSize*2; ++i)
        {
            AH[i-alSize] = AX[i];
        }

        tempSub -= int8_t(AH.to_ulong());

        BL = tempSub;

    } while (CX.to_ullong() > 0);








    cout << BL;

    return 0;
}

