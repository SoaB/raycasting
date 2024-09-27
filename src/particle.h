#ifndef __PARTICLE_H__
#define __PARTICLE_H__
#include "ray.h"
#include <raylib.h>

typedef struct {
    Vector2 pos;
    Ray2D rays[360];
} Particle;

Particle GenParticle(float x, float y);
void SetParticlePos(Particle* pt, Vector2 pos);
void DrawParticle(Particle* pt);
void ParticleLookWall(Particle* pt, Barrier* br);

#endif