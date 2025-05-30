#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Utils.h"

class GameObject {
protected:
    Vector2 position;
    Vector2 scale;
    float zRotation;

    SDL_Texture* texture;
    Vector2int textureCoor;
    Vector2int size;

public:
    GameObject(SDL_Renderer* renderer, Vector2int* _textureCoor, Vector2int* _size);
    virtual void Update(float dt) = 0;
    virtual void Render(SDL_Renderer* renderer);

    Vector2 GetPosition() const { return position; }
};
