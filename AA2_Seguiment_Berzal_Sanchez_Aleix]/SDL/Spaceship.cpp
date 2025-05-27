#include "Spaceship.h"
#include "InputManager.h"
#include <cmath>
#include "Projectile.h"

#ifndef M_PI
#define M_PI 3.14159265f
#endif

Spaceship::Spaceship(SDL_Renderer* renderer)
    : GameObject(renderer, new Vector2int(0, 0), new Vector2int(30, 40)) {
    this->renderer = renderer;
    position = Vector2(250.0f, 250.0f);
}



void Spaceship::Update(float dt) {
    //Float to control the rotation speed of our spaceship(problem encountered because it rotated too fast)
    float zRotationSpeed = 180.0f;
    //SDL input system
    if (IM.GetKey(SDLK_RIGHT, DOWN) || IM.GetKey(SDLK_RIGHT, HOLD)) {
        zRotation += zRotationSpeed * dt;
    }
    if (IM.GetKey(SDLK_LEFT, DOWN) || IM.GetKey(SDLK_LEFT, HOLD)) {
        zRotation -= zRotationSpeed * dt;
    }
    //Conversion to radians and not degrees 
    float radians = (zRotation - 90.0f) * (M_PI / 180.0f);
    Vector2 direction(cos(radians), sin(radians));

    if (IM.GetKey(SDLK_UP, DOWN) || IM.GetKey(SDLK_UP, HOLD)) {
        velocity += direction * acceleration * dt;
    }

    //60 FPS simulation to not depend on the frames of each device, also makes the spaceship slow smoothly 
    velocity = velocity * pow(linearVelocity, dt * 60);
    //We normalize the velocity for the same motives explained in the header 
    if (velocity.Magnitude() > speedLimit) {
        velocity = velocity.Normalized() * speedLimit;
    }

    position += velocity * dt;

      fireCooldown -= dt;
      //We instantiate a new projectile when the cooldown is up and the add the frame rate as cooldown for the next projectile 
      if ((IM.GetKey(SDLK_SPACE, HOLD) || IM.GetKey(SDLK_SPACE, DOWN)) && fireCooldown <= 0.0f) {
          projectiles.push_back(new Projectile(renderer, position, zRotation));
          fireCooldown = fireRate;
      }
 
      for (int i = 0; i < projectiles.size(); ) {

          projectiles[i]->Update(dt);
          i++;
          //Calling the update method to advance each projectile, also checks collisions if needed in the future I guess!
      }
    
}

void Spaceship::Render(SDL_Renderer* renderer) {
    //We render the projectiles in addition to the spaceship
    for (auto* p : projectiles) {
        p->Render(renderer);

    }
    GameObject::Render(renderer);
}
