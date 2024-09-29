
#include "barrier.h"
#include "fnoise.h"
#include "particle.h"
#include "raylib.h"
#include "soabdef.h"
#include <stdio.h>
#include <time.h>

fnl_state Noise;

void InitApp()
{
    // Initialize noise
    Noise = fnlCreateState();
    Noise.noise_type = FNL_NOISE_OPENSIMPLEX2;
}

void UpdateParticleNoise(Particle* p)
{
    Vector2 loc = p->pos;
    float n = fnlGetNoise2D(&Noise, GetRandomValue(-100, 100), GetRandomValue(-100, 100));
    printf("per n = %f\n", n);
    loc.x += n + 0.1;
    loc.y += n - 0.1;
    SetParticlePos(p, loc);
}
int main()
{
    InitApp();
    // Create and configure noise state
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "RayCasting free style");
    SetTargetFPS(60);
    Color bgColor = (Color) { 0x18, 0x18, 0x18, 0xFF };
    Barrier barrier[5];
    Particle ptr = GenParticle(SCR_WIDTH / 2, SCR_HEIGHT / 2);
    for (int i = 0; i < 5; i++)
        barrier[i] = GenRandomBarrier();
    while (!WindowShouldClose()) {
        UpdateParticleNoise(&ptr);
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