#include "barrier.h"
#include "ray.h"
#include "raymath.h"
#include <raylib.h>
#include <stdbool.h>

typedef struct {
    Vector2 pos;
    Ray2D rays[360];
} Particle;

Particle GenParticle(float x, float y)
{
    Particle pt;
    pt.pos.x = x;
    pt.pos.y = y;
    for (int i = 0; i < 360; i++) {
        pt.rays[i] = GenRay(x, y, i);
    }
    return pt;
}

void SetParticlePos(Particle* pt, Vector2 pos)
{
    pt->pos = pos;
    for (int i = 0; i < 360; i++) {
        Ray2dSetPos(&pt->rays[i], pos);
    }
}
void ParticleLookWall(Particle* pt, Barrier* br)
{
    for (int i = 0; i < 360; i++) {
        Vector2 nearest, cp;
        float record = 100000;
        bool draw = false;
        for (int j = 0; j < 5; j++) {
            if (Ray2dCast(&br[j], &pt->rays[i], &cp)) {
                float d = Vector2Distance(pt->pos, cp);
                if (d < record) {
                    record = d;
                    nearest = cp;
                    draw = true;
                }
            }
        }
        if (draw) {
            DrawLineV(pt->pos, nearest, YELLOW);
        }
    }
}
void DrawParticle(Particle* pt)
{
    DrawCircleV(pt->pos, 4, YELLOW);
    for (int i = 0; i < 360; i++) {
        DrawRay2d(&pt->rays[i], YELLOW);
    }
}