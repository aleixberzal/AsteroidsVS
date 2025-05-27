#pragma once
#include "GameObject.h"
#include "Utils.h"
#include <vector>
#include "Projectile.h"
class Spaceship : public GameObject {

protected:

	//Spaceship atributes
	Vector2 velocity;	

	float linearVelocity = 0.98f;
	float angularVelocity = 0.95f;	
	SDL_Renderer* renderer;
	float acceleration = 100.f;
	float speedLimit = 250.f;

	//Projectile atributes
	float fireCooldown = 1.5f;
	const float fireRate = 0.5f;
	//Dynamic memory to store and manage each projectile instantiated
	std::vector<Projectile*> projectiles;


public:
	Spaceship(SDL_Renderer* renderer);

	void Update(float dt) override;
	void Render(SDL_Renderer* renderer) override;
};