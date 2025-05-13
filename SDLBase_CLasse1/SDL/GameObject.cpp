#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* renderer, Vector2int* _textureCoor, Vector2int* _size) {

	position = Vector2(50, 50);
	zRotation = 0.f;
	scale = Vector2(0.75f, 0.75f);

	textureCoor = *_textureCoor;
	size = *_size;

	//LOAD TEXTURE
	SDL_Surface* surf = IMG_Load("resources/asteroids_spritesheet (1).png");
	if (surf == nullptr) {
		std::cout << "Error al cargar la surface:" << SDL_GetError();
	}

	texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr) {
		std::cout << "Error al cargar la textura:" << SDL_GetError();
	}

	SDL_FreeSurface(surf);
}

	

void GameObject::Render(SDL_Renderer* renderer) {
	SDL_Rect source{ textureCoor.x, textureCoor.y,		// TEXTURE POSITION
					size.x, size.y };	//TEXTURE SIZE
	
	SDL_Rect destination{ position.x,position.y,		//WINDOW POSITION
				source.w*scale.x,source.h *scale.y };	//WINDOW SIZE

	SDL_RenderCopyEx(renderer, texture, &source, &destination, zRotation, NULL, SDL_FLIP_NONE);
}