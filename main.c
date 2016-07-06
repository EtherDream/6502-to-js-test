#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <SDL/SDL.h>
#include <emscripten.h>

#include "6502.h"

#define PROG_ASM  "snake_asm.c"


uint8_t memory[65536] = {0};

// TODO: 填入原始二进制指令数据，解释模式需要
// memory[0x0600] = ...


#define ADDR_SCREEN         0x200
#define ADDR_RAND           0xfe
#define ADDR_INPUT          0xff

#define SCREEN_W            32
#define SCREEN_H            32

#define CYCLE_PER_FRAME     10


// 存储读写
uint8_t load(uint16_t addr) {
    if (addr == ADDR_RAND) {
        return rand();
    }
    return memory[addr];
}

void store(uint16_t addr, uint8_t val) {
    memory[addr] = val;
}


// 寄存器上下文
uint16_t Reg_PC = 0;
uint8_t Reg_A = 0;
uint8_t Reg_X = 0;
uint8_t Reg_Y = 0;
uint8_t Reg_SP = 0xff;

uint8_t Reg_SR_N = 0;
uint8_t Reg_SR_V = 0;
uint8_t Reg_SR_B = 1;
uint8_t Reg_SR_D = 0;
uint8_t Reg_SR_I = 0;
uint8_t Reg_SR_Z = 0;
uint8_t Reg_SR_C = 0;

int lastCycle = 0;


void update() {
    // 如果上次周期超额（小于 0），则在本次扣除
    int cycle_remain = CYCLE_PER_FRAME + lastCycle;

    // 恢复上下文（使用局部变量，容易优化）
    uint16_t PC = Reg_PC;
    uint8_t A = Reg_A;
    uint8_t X = Reg_X;
    uint8_t Y = Reg_Y;
    uint8_t SP = Reg_SP;

    uint8_t SR_N = Reg_SR_N;
    uint8_t SR_V = Reg_SR_V;
    uint8_t SR_B = Reg_SR_B;
    uint8_t SR_D = Reg_SR_D;
    uint8_t SR_I = Reg_SR_I;
    uint8_t SR_Z = Reg_SR_Z;
    uint8_t SR_C = Reg_SR_C;

    // 回到上次跳出的位置
    if (PC) goto _RET_MAP;

    #include PROG_ASM

LABEL_END:
    // 保存上下文
    Reg_PC = PC;
    Reg_A = A;
    Reg_X = X;
    Reg_Y = Y;
    Reg_SP = SP;

    Reg_SR_N = SR_N;
    Reg_SR_V = SR_V;
    Reg_SR_B = SR_B;
    Reg_SR_D = SR_D;
    Reg_SR_I = SR_I;
    Reg_SR_Z = SR_Z;
    Reg_SR_C = SR_C;

    lastCycle = cycle_remain;
}

void dump() {
    printf("program end\n");
    printf("A=$%02x X=$%02x Y=$%02x\n", Reg_A, Reg_X, Reg_Y);
    printf("SP=$%02x PC=$%04x\n", Reg_SP, Reg_PC);
    
    printf("NV-BDIZC\n");
    printf("%d%d1%d%d%d%d%d\n",
           Reg_SR_N, Reg_SR_V, Reg_SR_B, Reg_SR_D, Reg_SR_I, Reg_SR_Z, Reg_SR_C);
}

void input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            memory[ADDR_INPUT] = event.key.keysym.sym;
        }
    }
}

// 屏幕输出
SDL_Surface *screen;

const uint32_t PALETTE[16] = {
    0xff000000, 0xffffffff, 0xff000088, 0xffeeffaa,
    0xffcc44cc, 0xff55cc00, 0xffaa0000, 0xff77eeee,
    0xff5588dd, 0xff004466, 0xff7777ff, 0xff333333,
    0xff777777, 0xff66ffaa, 0xffff8800, 0xffbbbbbb
};

void output() {
    if (SDL_MUSTLOCK(screen)) {
        SDL_LockSurface(screen);
    }
    uint32_t* pixels = screen->pixels;

    // SDL_SetPaletteColors 用不了...
    for (int i = 0; i < SCREEN_W * SCREEN_H; i++) {
        uint8_t index = memory[ADDR_SCREEN + i];
        pixels[i] = PALETTE[index % 16];
    }

    if (SDL_MUSTLOCK(screen)) {
        SDL_UnlockSurface(screen);
    }
    SDL_Flip(screen); 
}


void render() {
    input();
    update();
    output();

    // 执行了 BRK 指令
    if (Reg_SR_I) {
        emscripten_cancel_main_loop();
        dump();
    }
}

int main() {
    srand( time(NULL) );

    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_SWSURFACE);

    emscripten_set_main_loop(render, 0, 1);
    return 0;
}
