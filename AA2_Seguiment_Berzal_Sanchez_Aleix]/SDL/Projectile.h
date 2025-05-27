#pragma once
#include "GameObject.h"
#include "Utils.h"

class Projectile : public GameObject {
public:
    //To instantiate the projectile we only need the renderer, 
    // the spawnPosition and the angle which the sprite will come out as (apart from velocity itself)
    Projectile(SDL_Renderer* renderer, Vector2 spawnPosition, float spawnAngle);
    Vector2 velocity;

    void Update(float dt) override;
};
