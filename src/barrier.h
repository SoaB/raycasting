#ifndef __BARRIER_H__
#define __BARRIER_H__

#include "raylib.h"
#include "soabdef.h"
#include <stdint.h>

typedef struct {
    Vector2 p1;
    Vector2 p2;
    union {
        Color color;
        uint32_t col;
    };
} Barrier;

void BarrierDraw(Barrier* b);
Barrier GenRandomBarrier(void);

#endif