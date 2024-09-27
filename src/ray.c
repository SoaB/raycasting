#include "ray.h"
#include "raylib.h"
#include <stdbool.h>
#define RAYMATH_IMPLEMENTATION
#include "raymath.h"
#include <math.h>

Ray2D GenRay(float x, float y, float angle)
{
    Ray2D r = (Ray2D) {
        .pos = (Vector2) { x, y },
        .dir = (Vector2) { cosf(DEG2RAD * angle), sinf(DEG2RAD * angle) },
    };
    return r;
}
void Ray2dSetPos(Ray2D* r, Vector2 pos)
{
    r->pos = pos;
}
void DrawRay2d(Ray2D* ray, Color col)
{
    Vector2 endpos = Vector2Add(ray->pos, Vector2Scale(ray->dir, 10));
    DrawCircleV(ray->pos, 4, col);
    DrawLineV(ray->pos, endpos, col);
}

void Ray2DLookAt(Ray2D* ray, Vector2 at)
{
    Vector2 gg = Vector2Subtract(at, ray->pos);
    ray->dir = Vector2Normalize(gg);
}

bool Ray2dCast(Barrier* b, Ray2D* r, Vector2* p)
{
    float x1, y1, x2, y2, x3, y3, x4, y4;
    float den;
    x1 = b->p1.x;
    y1 = b->p1.y;
    x2 = b->p2.x;
    y2 = b->p2.y;

    x3 = r->pos.x;
    y3 = r->pos.y;
    x4 = r->pos.x + r->dir.x;
    y4 = r->pos.y + r->dir.y;

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