#include "Projectile.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265f
#endif

Projectile::Projectile(SDL_Renderer* renderer, Vector2 spawnPosition, float spawnAngle)
    : GameObject(renderer, new Vector2int(10, 13), new Vector2int(2, 2)) {

    //To instantiate its atributes we use the same as the spaceship, except the velocity!
    position = spawnPosition;
    //Instead of degrees, as claimed in the exercise, we convert them to radians 
    float radians = (spawnAngle - 90.0f) * (M_PI / 180.0f);
    Vector2 direction(cos(radians), sin(radians));
    float speed = 200.0f;
    velocity = direction * speed;
    //The rotation is the same that had the spaceship the moment the projectile was instantiated 
    zRotation = spawnAngle;
    //We upscale the sprite to make it more visible 
        scale = Vector2(3.0f, 3.0f);
}

void Projectile::Update(float dt) {
    position += velocity * dt;
}
