#include "barrier.h"
#include "raymath.h"
#include <raylib.h>
#include <stdbool.h>

typedef struct {
    Vector2 pos;
    //    Ray2D rays[360];
    Vector2 dir[360];
    int thi;
} Particle;

Particle GenParticle(float x, float y)
{
    Particle pt;
    pt.pos.x = x;
    pt.pos.y = y;
    pt.thi = 0;
    for (int i = 0; i < 360; i++) {
        pt.dir[i] = (Vector2) { cosf(DEG2RAD * i), sinf(DEG2RAD * i) };
    }
    return pt;
}

void SetParticlePos(Particle* pt, Vector2 pos)
{
    pt->pos = pos;
}

bool CastRay(Barrier* b, Particle* r, Vector2* p)
{
    float x1, y1, x2, y2, x3, y3, x4, y4;
    float den;
    x1 = b->p1.x;
    y1 = b->p1.y;
    x2 = b->p2.x;
    y2 = b->p2.y;

    x3 = r->pos.x;
    y3 = r->pos.y;
    x4 = r->pos.x + r->dir[r->thi].x;
    y4 = r->pos.y + r->dir[r->thi].y;

    den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (den == 0) {
        return false;
    }

    float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;
    if (t > 0 && t < 1 && u > 0) {
        p->x = x1 + t * (x2 - x1);
        p->y = y1 + t * (y2 - y1);
        return true;
    } else {
        return false;
    }
}
void ParticleLookWall(Particle* pt, Barrier* br)
{
    for (int i = 0; i < 360; i++) {
        Vector2 nearest, cp;
        float record = 100000;
        bool draw = false;
        pt->thi = i;
        for (int j = 0; j < 5; j++) {
            if (CastRay(&br[j], pt, &cp)) {
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
        Vector2 endpos = Vector2Add(pt->pos, Vector2Scale(pt->dir[i], 10));
        DrawLineV(pt->pos, endpos, WHITE);
    }
}