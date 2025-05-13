#pragma once
#include <SDL.h>
#include <vector>

#include "GameObject.h"
#include "UIText.h"

class Scene {
public: 
	std::vector<GameObject*> objects;
	std::vector<UIText*> textObjects;

	std::string targetScene; //Control de transiciones de escenas
	bool isFinished = true;

public: 
	virtual void Start(SDL_Renderer* rend) {
		isFinished = false;
	}
	virtual void Update(float dt){
		for (int i = 0; i < objects.size(); i++) 
			objects[i]->Update(dt);
		
	}
	virtual void Render(SDL_Renderer* rend) {
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render(rend);
	}

	//Virtual pura para que cada una gestione su exit de forma única
	virtual void Exit() = 0;

	//GETTERS
	bool IsFinished() { return isFinished; };
	std::string GetTargetScene() { return targetScene; };
};