/**
 * 6502 指令宏实现~ 还不太完善
 */
#define STACK_BASE      0x100

#define GetStack(M)     GetMem(M + STACK_BASE)
#define SetStack(M, V)  SetMem(M + STACK_BASE, V)

#define CYCLE(V)        cycle_remain -= V;
#define CHECK_CYCLE()   if (cycle_remain <= 0) goto LABEL_END;

#define HEX(N)          0x##N
#define LABEL(ADDR)     L_##ADDR
#define GOTO(ADDR)      goto LABEL(ADDR);

#define ZPX(V)          ( ((V) + X) & 0xff )
#define ZPY(V)          ( ((V) + Y) & 0xff )
#define ABSX(V)         ( (V) + X )
#define ABSY(V)         ( (V) + Y )


// TODO: 跨页内存 cycle++

#define INDX_ADDR(M)    uint8_t index = ZPX(M); \
                        uint16_t addr = GetMem(index + 1) << 8 | GetMem(index);

#define INDY_ADDR(M)    uint16_t addr = (GetMem(M + 1) << 8 | GetMem(M)) + Y;


#define GET_INDX(R, M)  { INDX_ADDR(M); R = GetMem(addr); }
#define SET_INDX(R, M)  { INDX_ADDR(M); SetMem(addr, R); }

#define GET_INDY(R, M)  { INDY_ADDR(M); R = GetMem(addr); }
#define SET_INDY(R, M)  { INDY_ADDR(M); SetMem(addr, R); }

#define FLAG_N(v)       SR_N = (v) > 127;
#define FLAG_Z(v)       SR_Z = (v) == 0;
#define FLAG_NZ(v)      FLAG_N(v); FLAG_Z(v);

//
// status
//
#define CLC()           CYCLE(2); SR_C = 0;
#define CLD()           CYCLE(2); SR_D = 0;
#define CLI()           CYCLE(2); SR_I = 0;
#define CLV()           CYCLE(2); SR_V = 0;

#define SEC()           CYCLE(2); SR_C = 1;
#define SED()           CYCLE(2); SR_D = 1;
#define SEI()           CYCLE(2); SR_I = 1;

//
// load
//
#define _LD_IMM(R, I)   R = I; FLAG_NZ(R);
#define _LD_MEM(R, M)   R = GetMem(M); FLAG_NZ(R);


#define LDA_IMM(v)      CYCLE(2); _LD_IMM(A, v);
#define LDX_IMM(v)      CYCLE(2); _LD_IMM(X, v);
#define LDY_IMM(v)      CYCLE(2); _LD_IMM(Y, v);

#define LDA_ZP(v)       CYCLE(3); _LD_MEM(A, v);
#define LDX_ZP(v)       CYCLE(3); _LD_MEM(X, v);
#define LDY_ZP(v)       CYCLE(3); _LD_MEM(Y, v);

#define LDA_ZP_X(v)     CYCLE(4); _LD_MEM(A, ZPX(v));
#define LDX_ZP_Y(v)     CYCLE(4); _LD_MEM(X, ZPY(v));
#define LDY_ZP_X(v)     CYCLE(4); _LD_MEM(Y, ZPX(v));

#define LDA_ABS(v)      CYCLE(4); _LD_MEM(A, v);
#define LDA_ABS_X(v)    CYCLE(4); _LD_MEM(A, ABSX(v));
#define LDA_ABS_Y(v)    CYCLE(4); _LD_MEM(A, ABSY(v));
#define LDX_ABS(v)      CYCLE(4); _LD_MEM(X, v);
#define LDX_ABS_Y(v)    CYCLE(4); _LD_MEM(X, ABSY(v));
#define LDY_ABS(v)      CYCLE(4); _LD_MEM(Y, v);
#define LDY_ABS_X(v)    CYCLE(4); _LD_MEM(Y, ABSX(v));

#define LDA_IDR_X(v)    CYCLE(6); GET_INDX(A, v);
#define LDA_IDR_Y(v)    CYCLE(5); GET_INDY(A, v);

//
// store
//
#define _ST(R, M)       SetMem(M, R);

#define STA_ZP(v)       CYCLE(3); _ST(A, v);
#define STX_ZP(v)       CYCLE(3); _ST(X, v);
#define STY_ZP(v)       CYCLE(3); _ST(Y, v);

#define STA_ZP_X(v)     CYCLE(4); _ST(A, ZPX(v));
#define STX_ZP_Y(v)     CYCLE(4); _ST(X, ZPY(v));
#define STY_ZP_X(v)     CYCLE(4); _ST(X, ZPX(v));

#define STA_ABS(v)      CYCLE(4); _ST(A, v);
#define STA_ABS_X(v)    CYCLE(5); _ST(A, ABSX(v);
#define STA_ABS_Y(v)    CYCLE(5); _ST(A, ABSY(v));
#define STX_ABS_Y(v)    CYCLE(4); _ST(X, ABSY(v));
#define STY_ABS_X(v)    CYCLE(4); _ST(Y, ABSX(v));

#define STA_IDX(v)      CYCLE(6); SET_INDX(A, v);
#define STA_IDY(v)      CYCLE(6); SET_INDY(A, v);

//
// transfer
//
#define _TR(D, S)       CYCLE(2); D = S; FLAG_NZ(D);

#define TAX()           _TR(X, A);
#define TAY()           _TR(Y, A);

#define TXA()           _TR(A, X);
#define TYA()           _TR(A, Y);

#define TSX()           _TR(X, SP);
#define TXS()           _TR(SP, X);

//
// comparison
//
#define _CP_VAL(R, I)   SR_C = (R >= I); FLAG_NZ(R - I);
#define _CP_MEM(R, M)   { uint8_t v = GetMem(M); _CP_VAL(R, v); }


#define CMP_IMM(M)      CYCLE(2); _CP_VAL(A, M);
#define CPX_IMM(M)      CYCLE(2); _CP_VAL(X, M);
#define CPY_IMM(M)      CYCLE(2); _CP_VAL(Y, M);

#define CMP_ZP(M)       CYCLE(3); _CP_MEM(A, M);
#define CPX_ZP(M)       CYCLE(3); _CP_MEM(X, M);
#define CPY_ZP(M)       CYCLE(3); _CP_MEM(Y, M);

#define CMP_ZP_X(M)     CYCLE(4); _CP_MEM(A, ZPX(M));

#define CMP_ABS(M)      CYCLE(4); _CP_MEM(A, M);
#define CMP_ABS_X(M)    CYCLE(4); _CP_MEM(A, ABSX(M));
#define CMP_ABS_Y(M)    CYCLE(4); _CP_MEM(A, ABSY(M));
#define CPX_ABS(M)      CYCLE(4); _CP_MEM(X, M);
#define CPY_ABS(M)      CYCLE(4); _CP_MEM(Y, M);

#define CMP_IDX(M)      CYCLE(6); { uint8_t v; GET_INDX(v, M); _CP_VAL(A, v); }
#define CMP_IDY(M)      CYCLE(5); { uint8_t v; GET_INDY(v, M); _CP_VAL(A, v); }

//
// arithmetic（抄 easy6502 的判断逻辑，不知道能不能优化一下）
//
#define _ADC_VAL(V) {                           \
    uint16_t t;                                 \
    SR_V = ((A ^ V) & 0x80) == 0;               \
    if (SR_D) {                                 \
        t = (A & 0xf) + (V & 0xf) + SR_C;       \
        if (t >= 10) {                          \
            t = 0x10 | ((t + 6) & 0xf);         \
        }                                       \
        t += (A & 0xf0) + (V & 0xf0);           \
        if (t >= 160) {                         \
            SR_C = 1;                           \
            if (SR_V && t >= 0x180) {           \
                SR_V = 0;                       \
            }                                   \
            t += 0x60;                          \
        } else {                                \
            SR_C = 0;                           \
            if (SR_V && t < 0x80) {             \
                SR_V = 0;                       \
            }                                   \
        }                                       \
    } else {                                    \
        t = A + V + SR_C;                       \
        if (t >= 0x100) {                       \
            SR_C = 1;                           \
            if (SR_V && t >= 0x180) {           \
                SR_V = 0;                       \
            }                                   \
        } else {                                \
            SR_C = 0;                           \
            if (SR_V && t < 0x80) {             \
                SR_V = 0;                       \
            }                                   \
        }                                       \
    }                                           \
    A = t & 0xff;                               \
    FLAG_NZ(A);                                 \
}

#define _ADC_MEM(M)     { uint8_t v = GetMem(M); _ADC_VAL(v); }

#define ADC_IMM(I)      CYCLE(2); _ADC_VAL(I);
#define ADC_ZP(M)       CYCLE(3); _ADC_MEM(M);
#define ADC_ZP_X(M)     CYCLE(4); _ADC_MEM(ZPX(M));
#define ADC_ABS(M)      CYCLE(4); _ADC_MEM(M);
#define ADC_ABS_X(M)    CYCLE(4); _ADC_MEM(ABSX(M));
#define ADC_ABS_Y(M)    CYCLE(4); _ADC_MEM(ABSY(M));
#define ADC_IDX(M)      CYCLE(6); { uint8_t v; GET_INDX(v, M); _ADC_VAL(v); }
#define ADC_IDY(M)      CYCLE(5); { uint8_t v; GET_INDY(v, M); _ADC_VAL(v); }


// 本来还是写成 inline 函数比较好。敲反斜扛敲的好累，还有对齐强迫症。

#define _SBC_VAL(V) {                           \
    uint16_t t, w;                              \
    SR_V = ((A ^ V) & 0x80) != 0;               \
    if (SR_D) {                                 \
        t = 0xf + (A & 0xf) - (V & 0xf) + SR_C; \
        if (t < 0x10) {                         \
            w = 0;                              \
            t -= 6;                             \
        } else {                                \
            w = 0x10;                           \
            t -= 0x10;                          \
        }                                       \
        w += 0xf0 + (A & 0xf0) - (V & 0xf0);    \
        if (w < 0x100) {                        \
            SR_C = 0;                           \
            if (SR_V && w < 0x80) {             \
                SR_V = 0;                       \
            }                                   \
            w -= 0x60;                          \
        } else {                                \
            SR_C = 1;                           \
            if (SR_V && w >= 0x180) {           \
                SR_V = 0;                       \
            }                                   \
        }                                       \
        w += t;                                 \
    } else {                                    \
        w = 0xff + A - V + SR_C;                \
        if (w < 0x100) {                        \
            SR_C = 0;                           \
            if (SR_V && w < 0x80) {             \
                SR_V = 0;                       \
            }                                   \
        } else {                                \
            SR_C = 1;                           \
            if (SR_V && w >= 0x180) {           \
                SR_V = 0;                       \
            }                                   \
        }                                       \
    }                                           \
    A = w & 0xff;                               \
    FLAG_NZ(A);                                 \
}

#define _SBC_MEM(M)     { uint8_t v = GetMem(M); _SBC_VAL(v); }


#define SBC_IMM(I)      CYCLE(2); _SBC_VAL(I);
#define SBC_ZP(M)       CYCLE(3); _SBC_MEM(M);
#define SBC_ZP_X(M)     CYCLE(4); _SBC_MEM(ZPX(M));
#define SBC_ABS(M)      CYCLE(4); _SBC_MEM(M);
#define SBC_ABS_X(M)    CYCLE(4); _SBC_MEM(ABSX(M));
#define SBC_ABS_Y(M)    CYCLE(4); _SBC_MEM(ABSY(M));
#define SBC_IDX(M)      CYCLE(6); { uint8_t v; GET_INDX(v, M); _SBC(v); }
#define SBC_IDY(M)      CYCLE(5); { uint8_t v; GET_INDY(v, M); _SBC(v); }



// INC, DEC
#define _ADD_VAL(R, I)  CYCLE(2); R += I; FLAG_NZ(R);

#define INX()           _ADD_VAL(X,  1);
#define INY()           _ADD_VAL(Y,  1);
#define DEX()           _ADD_VAL(X, -1);
#define DEY()           _ADD_VAL(Y, -1);


#define _ADD_MEM(M, I) {                        \
    uint8_t v = GetMem(M) + I;                  \
    SetMem(M, v);                               \
    FLAG_NZ(v);                                 \
}

#define INC_ZP(M)       CYCLE(5); _ADD_MEM(M, 1);
#define INC_ZP_X(M)     CYCLE(6); _ADD_MEM(ZPX(M), 1);
#define INC_ABS(M)      CYCLE(6); _ADD_MEM(M, 1);
#define INC_ABS_X(M)    CYCLE(7); _ADD_MEM(ABSX(M), 1);

#define DEC_ZP(M)       CYCLE(5); _ADD_MEM(M, -1);
#define DEC_ZP_X(M)     CYCLE(6); _ADD_MEM(ZPX(M), -1);
#define DEC_ABS(M)      CYCLE(3); _ADD_MEM(M, -1);
#define DEC_ABS_X(M)    CYCLE(7); _ADD_MEM(ABSX(M), -1);

//
// logical
//
#define _OR(V)          A |= V; FLAG_NZ(A);
#define _EOR(V)         A ^= V; FLAG_NZ(A);
#define _AND(V)         A &= V; FLAG_NZ(A);

#define ORA_IMM(I)      CYCLE(2); _OR( I );
#define ORA_ZP(M)       CYCLE(3); _OR( GetMem(M) );
#define ORA_ZP_X(M)     CYCLE(4); _OR( GetMem(ZPX(M)) );
#define ORA_ABS(M)      CYCLE(4); _OR( GetMem(M) );
#define ORA_ABS_X(M)    CYCLE(4); _OR( GetMem(ABSX(M)) );
#define ORA_ABS_Y(M)    CYCLE(4); _OR( GetMem(ABSY(M)) );
#define ORA_IDX(M)      CYCLE(6); { uint8_t v; GET_INDX(v, M); _OR(v); }
#define ORA_IDY(M)      CYCLE(5); { uint8_t v; GET_INDY(v, M); _OR(v); }

#define EOR_IMM(I)      CYCLE(2); _EOR( I );
#define EOR_ZP(M)       CYCLE(3); _EOR( GetMem(M) );
#define EOR_ZP_X(M)     CYCLE(4); _EOR( GetMem(ZPX(M)) );
#define EOR_ABS(M)      CYCLE(4); _EOR( GetMem(M) );
#define EOR_ABS_X(M)    CYCLE(4); _EOR( GetMem(ABSX(M)) );
#define EOR_ABS_Y(M)    CYCLE(4); _EOR( GetMem(ABSY(M)) );
#define EOR_IDX(M)      CYCLE(6); { uint8_t v; GET_INDX(v, M); _EOR(v); }
#define EOR_IDY(M)      CYCLE(5); { uint8_t v; GET_INDY(v, M); _EOR(v); }

#define AND_IMM(I)      CYCLE(2); _AND( I );
#define AND_ZP(M)       CYCLE(3); _AND( GetMem(M) );
#define AND_ZP_X(M)     CYCLE(4); _AND( GetMem(ZPX(M)) );
#define AND_ABS(M)      CYCLE(4); _AND( GetMem(M) );
#define AND_ABS_X(M)    CYCLE(4); _AND( GetMem(ABSX(M)) );
#define AND_ABS_Y(M)    CYCLE(4); _AND( GetMem(ABSY(M)) );
#define AND_IDX(M)      CYCLE(6); { uint8_t v; GET_INDX(v, M); _AND(v); }
#define AND_IDY(M)      CYCLE(5); { uint8_t v; GET_INDY(v, M); _AND(v); }


//
// bit（眼花缭乱了有木有）
//
#define _BIT(M) {                           \
    uint8_t v = GetMem(M);                  \
    FLAG_N(v);                              \
    SR_V = (v & 64) != 0;                   \
    FLAG_Z(v & A);                          \
}

#define BIT_ZP(M)       CYCLE(3); _BIT(M);
#define BIT_ABS(M)      CYCLE(4); _BIT(M);


// shift right
#define _LSR_V(R)       SR_C = (R & 1) != 0; R >>= 1; FLAG_Z(R);
#define _LSR_M(ADDR) {                      \
    uint8_t v = GetMem(ADDR);               \
    _LSR(v);                                \
    SetMem(ADDR, v)                         \
}

#define LSR_ZP(M)       CYCLE(5); LSR_M( M );
#define LSR_ZP_X(M)     CYCLE(6); LSR_M( ZPX(M) );
#define LSR_ABS(M)      CYCLE(6); LSR_M( M );
#define LSR_ABS_X(M)    CYCLE(7); LSR_M( ABSX(M) );
#define LSR_A()         CYCLE(2); _LSR_V(A);


// shift left
#define _ASL_V(R)       SR_C = (R & 128) != 0; R <<= 1; FLAG_NZ(R);
#define _ASL_M(ADDR) {                      \
    uint8_t v = GetMem(ADDR);               \
    _ASL(v);                                \
    SetMem(ADDR, v)                         \
}


#define ASL_ZP(M)       CYCLE(5); _ASL_M( M );
#define ASL_ZP_X(M)     CYCLE(6); _ASL_M( ZPX(M) );
#define ASL_ABS(M)      CYCLE(6); _ASL_M( M );
#define ASL_ABS_X(M)    CYCLE(7); _ASL_M( ABSX(M) );
#define ASL_A(R)        CYCLE(2); _ASL_V(A);

//
// stack
//
#define _PUSH(R)        CYCLE(3); SetStack(SP, R); SP -= 1;
#define _PULL(R)        CYCLE(4); SP += 1; R = GetStack(SP);

#define PHA()           _PUSH(A);
#define PLA()           _PULL(A); FLAG_NZ(A);

// PHP 才是坠吼的
#define PHP() {                     \
    uint8_t sr;                     \
    sr = (SR_N << 7) |              \
         (SR_V << 6) |              \
         (   1 << 5) |              \
         (SR_B << 4) |              \
         (SR_D << 3) |              \
         (SR_I << 2) |              \
         (SR_Z << 1) |              \
         (SR_C << 0) ;              \
    _PUSH(sr);                      \
}

#define PLP() {                     \
    uint8_t sr;                     \
    _PULL(sr);                      \
    SR_N = (sr & 128) != 0;         \
    SR_V = (sr &  64) != 0;         \
    SR_B = (sr &  16) != 0;         \
    SR_D = (sr &   8) != 0;         \
    SR_I = (sr &   4) != 0;         \
    SR_Z = (sr &   2) != 0;         \
    SR_C = (sr &   1) != 0;         \
}

//
// branching
//
#define _BR(COND, ADDR) CYCLE(2); if (COND) { GOTO(ADDR); }

#define BCC(ADDR)       _BR(SR_C == 0, ADDR);
#define BCS(ADDR)       _BR(SR_C == 1, ADDR);

#define BNE(ADDR)       _BR(SR_Z == 0, ADDR);
#define BEQ(ADDR)       _BR(SR_Z == 1, ADDR);

#define BPL(ADDR)       _BR(SR_N == 0, ADDR);
#define BMI(ADDR)       _BR(SR_N == 1, ADDR);

#define BVC(ADDR)       _BR(SR_V == 0, ADDR);
#define BVS(ADDR)       _BR(SR_V == 1, ADDR);

//
// subroutine
//
#define JSR(addr, curr)                     \
    CYCLE(6);                               \
    SetStack(SP, (HEX(curr) + 2) & 0xff);   \
    SetStack(SP - 1, (HEX(curr) + 2) >> 8); \
    SP -= 2;                                \
    GOTO(addr);


#define RTS()                               \
    CYCLE(6);                               \
    PC = GetStack(SP + 1) << 8 |            \
         GetStack(SP + 2);                  \
    SP += 2;                                \
    CHECK_CYCLE();                          \
    goto _RET_MAP;


#define JMP(ADDR, CURR)                     \
    CYCLE(3);                               \
    PC = HEX(ADDR);                         \
    if (HEX(ADDR) <= HEX(CURR)) {           \
        /* CHECK_CYCLE(); */                \
    }                                       \
    GOTO(ADDR);


#define JMP_IND(ADDR)                       \
    CYCLE(5);                               \
    PC = GetMem(HEX(ADDR) + 1) << 8 |       \
         GetMem(HEX(ADDR));                 \
    CHECK_CYCLE();                          \
    goto _RET_MAP;

//
// system
//
#define NOP()           CYCLE(2);
#define BRK()           SR_I = 1; goto LABEL_END;

#define RET_BEGIN       _RET_MAP: switch(PC) {
#define RET_ADDR(ADDR)  case HEX(ADDR)-1: goto LABEL(ADDR);
#define RET_END         default: /*interpreter(PC);*/; }


// TODO: 实现解释器

void interpreter(uint16_t pc) {
}


