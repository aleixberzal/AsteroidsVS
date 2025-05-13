#include "MenuScene.h"



void MenuScene:: Start(SDL_Renderer* rend) {
	Scene::Start(rend);

	textObjects.push_back(new UIText(rend, Vector2(250,250), Vector2(1.f, 1.f), 0.0f, "Asteroids"));
}
void MenuScene::Update(float dt) {
	Scene::Update(dt);

}
void MenuScene::Render(SDL_Renderer* rend) {
	Scene::Render(rend);
	if (!textObjects.empty()) textObjects[0]->SetText("ASTEROIDS", rend);
	textObjects[0]->Render(rend);
}
void MenuScene::Exit() {
	for (int i = 0; i < textObjects.size(); i++) {
		delete(textObjects[i]);
	}

	objects.clear();
}