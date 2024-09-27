#include "barrier.h"

void BarrierDraw(Barrier* b)
{
    DrawLineV(b->p1, b->p2, b->color);
}

Barrier GenRandomBarrier(void)
{
    Barrier b = (Barrier) {
        .p1 = (Vector2) { GetRandomValue(10, 1500), GetRandomValue(100, 800) },
        .p2 = (Vector2) { GetRandomValue(10, 1500), GetRandomValue(100, 800) },
        .col = 0xFF778899,
    };
    return b;
}
