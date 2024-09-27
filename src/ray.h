#ifndef __RAY_H__
#define __RAY_H__

#include "barrier.h"
#include "raylib.h"
#include <stdbool.h>

typedef struct {
    Vector2 pos;
    Vector2 dir;
} Ray2D;

Ray2D GenRay(float x, float y, float angle);
void Ray2dSetPos(Ray2D* r, Vector2 pos);
void DrawRay2d(Ray2D* ray, Color col);
void Ray2DLookAt(Ray2D* ray, Vector2 at);
bool Ray2dCast(Barrier* b, Ray2D* r, Vector2* p);

#endif