L_0600: JSR(0606, 0600)
L_0603: JSR(0638, 0603)
L_0606: JSR(060d, 0606)
L_0609: JSR(062a, 0609)
L_060c: RTS()
L_060d: LDA_IMM(0x02)
L_060f: STA_ZP(0x02)
L_0611: LDA_IMM(0x04)
L_0613: STA_ZP(0x03)
L_0615: LDA_IMM(0x11)
L_0617: STA_ZP(0x10)
L_0619: LDA_IMM(0x10)
L_061b: STA_ZP(0x12)
L_061d: LDA_IMM(0x0f)
L_061f: STA_ZP(0x14)
L_0621: LDA_IMM(0x04)
L_0623: STA_ZP(0x11)
L_0625: STA_ZP(0x13)
L_0627: STA_ZP(0x15)
L_0629: RTS()
L_062a: LDA_ZP(0xfe)
L_062c: STA_ZP(0x00)
L_062e: LDA_ZP(0xfe)
L_0630: AND_IMM(0x03)
L_0632: CLC()
L_0633: ADC_IMM(0x02)
L_0635: STA_ZP(0x01)
L_0637: RTS()
L_0638: JSR(064d, 0638)
L_063b: JSR(068d, 063b)
L_063e: JSR(06c3, 063e)
L_0641: JSR(0719, 0641)
L_0644: JSR(0720, 0644)
L_0647: JSR(072d, 0647)
L_064a: JMP(0638, 064a)
L_064d: LDA_ZP(0xff)
L_064f: CMP_IMM(0x77)
L_0651: BEQ(0660)
L_0653: CMP_IMM(0x64)
L_0655: BEQ(066b)
L_0657: CMP_IMM(0x73)
L_0659: BEQ(0676)
L_065b: CMP_IMM(0x61)
L_065d: BEQ(0681)
L_065f: RTS()
L_0660: LDA_IMM(0x04)
L_0662: BIT_ZP(0x02)
L_0664: BNE(068c)
L_0666: LDA_IMM(0x01)
L_0668: STA_ZP(0x02)
L_066a: RTS()
L_066b: LDA_IMM(0x08)
L_066d: BIT_ZP(0x02)
L_066f: BNE(068c)
L_0671: LDA_IMM(0x02)
L_0673: STA_ZP(0x02)
L_0675: RTS()
L_0676: LDA_IMM(0x01)
L_0678: BIT_ZP(0x02)
L_067a: BNE(068c)
L_067c: LDA_IMM(0x04)
L_067e: STA_ZP(0x02)
L_0680: RTS()
L_0681: LDA_IMM(0x02)
L_0683: BIT_ZP(0x02)
L_0685: BNE(068c)
L_0687: LDA_IMM(0x08)
L_0689: STA_ZP(0x02)
L_068b: RTS()
L_068c: RTS()
L_068d: JSR(0694, 068d)
L_0690: JSR(06a8, 0690)
L_0693: RTS()
L_0694: LDA_ZP(0x00)
L_0696: CMP_ZP(0x10)
L_0698: BNE(06a7)
L_069a: LDA_ZP(0x01)
L_069c: CMP_ZP(0x11)
L_069e: BNE(06a7)
L_06a0: INC_ZP(0x03)
L_06a2: INC_ZP(0x03)
L_06a4: JSR(062a, 06a4)
L_06a7: RTS()
L_06a8: LDX_IMM(0x02)
L_06aa: LDA_ZP_X(0x10)
L_06ac: CMP_ZP(0x10)
L_06ae: BNE(06b6)
L_06b0: LDA_ZP_X(0x11)
L_06b2: CMP_ZP(0x11)
L_06b4: BEQ(06bf)
L_06b6: INX()
L_06b7: INX()
L_06b8: CPX_ZP(0x03)
L_06ba: BEQ(06c2)
L_06bc: JMP(06aa, 06bc)
L_06bf: JMP(0735, 06bf)
L_06c2: RTS()
L_06c3: LDX_ZP(0x03)
L_06c5: DEX()
L_06c6: TXA()
L_06c7: LDA_ZP_X(0x10)
L_06c9: STA_ZP_X(0x12)
L_06cb: DEX()
L_06cc: BPL(06c7)
L_06ce: LDA_ZP(0x02)
L_06d0: LSR_A()
L_06d1: BCS(06dc)
L_06d3: LSR_A()
L_06d4: BCS(06ef)
L_06d6: LSR_A()
L_06d7: BCS(06f8)
L_06d9: LSR_A()
L_06da: BCS(070b)
L_06dc: LDA_ZP(0x10)
L_06de: SEC()
L_06df: SBC_IMM(0x20)
L_06e1: STA_ZP(0x10)
L_06e3: BCC(06e6)
L_06e5: RTS()
L_06e6: DEC_ZP(0x11)
L_06e8: LDA_IMM(0x01)
L_06ea: CMP_ZP(0x11)
L_06ec: BEQ(0716)
L_06ee: RTS()
L_06ef: INC_ZP(0x10)
L_06f1: LDA_IMM(0x1f)
L_06f3: BIT_ZP(0x10)
L_06f5: BEQ(0716)
L_06f7: RTS()
L_06f8: LDA_ZP(0x10)
L_06fa: CLC()
L_06fb: ADC_IMM(0x20)
L_06fd: STA_ZP(0x10)
L_06ff: BCS(0702)
L_0701: RTS()
L_0702: INC_ZP(0x11)
L_0704: LDA_IMM(0x06)
L_0706: CMP_ZP(0x11)
L_0708: BEQ(0716)
L_070a: RTS()
L_070b: DEC_ZP(0x10)
L_070d: LDA_ZP(0x10)
L_070f: AND_IMM(0x1f)
L_0711: CMP_IMM(0x1f)
L_0713: BEQ(0716)
L_0715: RTS()
L_0716: JMP(0735, 0716)
L_0719: LDY_IMM(0x00)
L_071b: LDA_ZP(0xfe)
L_071d: STA_IDY(0x00)
L_071f: RTS()
L_0720: LDX_ZP(0x03)
L_0722: LDA_IMM(0x00)
L_0724: STA_IDX(0x10)
L_0726: LDX_IMM(0x00)
L_0728: LDA_IMM(0x01)
L_072a: STA_IDX(0x10)
L_072c: RTS()
L_072d: LDX_IMM(0x00)
L_072f: NOP()
L_0730: NOP()
L_0731: DEX()
L_0732: BNE(072f)
L_0734: RTS()
L_0735: BRK()

RET_BEGIN
    RET_ADDR(0603)
    RET_ADDR(0606)
    RET_ADDR(0609)
    RET_ADDR(060c)
    RET_ADDR(063b)
    RET_ADDR(063e)
    RET_ADDR(0641)
    RET_ADDR(0644)
    RET_ADDR(0647)
    RET_ADDR(064a)
    RET_ADDR(0690)
    RET_ADDR(0693)
    RET_ADDR(06a7)
RET_END