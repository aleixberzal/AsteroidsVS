#pragma once
#include "GameObject.h"

class Spaceship : public GameObject {

private: 
	float linearVelocity= 3.f;
	float angularVelocity= 2.f;
public:
	Spaceship(SDL_Renderer* renderer);

	 virtual void Update(float dt) override;
};