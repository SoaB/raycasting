
#include "barrier.h"
#include "particle.h"
#include "ray.h"
#include "raylib.h"
#include "soabdef.h"

int main()
{
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "RayCasting free style");
    SetTargetFPS(60);
    Color bgColor = (Color) { 0x18, 0x18, 0x18, 0xFF };
    Barrier barrier[5];
    Particle ptr = GenParticle(SCR_WIDTH / 2, SCR_HEIGHT / 2);
    for (int i = 0; i < 5; i++)
        barrier[i] = GenRandomBarrier();
    while (!WindowShouldClose()) {
        SetParticlePos(&ptr, GetMousePosition());
        BeginDrawing();
        ClearBackground(bgColor);
        for (int i = 0; i < 5; i++)
            BarrierDraw(&barrier[i]);
        DrawParticle(&ptr);
        ParticleLookWall(&ptr, barrier);
        EndDrawing();
    }
    return 0;
}