#include "GameEngine.h"
#include "GameObject.h"
#include "InputManager.h"
GameEngine::GameEngine(int windowWidth, int windowHeight) {
	InitSDL();
	InitWindowAndRenderer(windowWidth, windowHeight);

}

void GameEngine::Update() {



	//TIME

	float dt = 0.0;
	float lastTime = (float)SDL_GetPerformanceCounter() / (float)SDL_GetPerformanceFrequency(); 
	
	const int FPS = 60;
	//Duración que necesita un frame para mantenerse a 60 fps
	const float frameTime = 1.0f/(float)FPS;

	//SCENES
	//Pasamos la key y el value
	//map te obliga a que la lista esté ordenada mientras que unordered no

	std::map<std::string, Scene*> gameScene;
	gameScene["MainMenu"] = new MenuScene();
	gameScene["Gameplay"] = new GameplayScene();
	gameScene["Highscores"] = new HighscoresScene();

	//La primera escena que quiero activa es el gameplay
	Scene* currentScene = gameScene["Gameplay"];
	currentScene->Start(renderer);

	while (!IM.GetQuit()) {

		IM.Listen();
		//DELTA TIME CONTROL
		float currentTime= (float)SDL_GetPerformanceCounter() / (float)SDL_GetPerformanceFrequency();
		dt += currentTime - lastTime;

		if (dt > frameTime) {


			

			//LOGIC
			currentScene->Update(dt);
			//RENDER
			//SDL_SetRenderDrawColor(renderer, 255, 120, 0, 1); //Que queremos que pinte

			SDL_RenderClear(renderer);						  //Limpia lo anterior
			currentScene->Render(renderer);
			SDL_RenderPresent(renderer);					  //Pintamos lo nuevo

			//SCENE TRANSITION

			if (currentScene->IsFinished()) {
				currentScene->Exit();
				currentScene = gameScene[currentScene->GetTargetScene()];
				currentScene->Start(renderer);
			}

			dt -= frameTime;
		}
	}
}

void GameEngine::Finish() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void GameEngine::InitSDL() {


	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Error al inicialzar SDL:" << SDL_GetError();
	}
	if (TTF_Init() < 0) {
		std::cout << "Error al inicializar TTF: " << SDL_GetError();
	}
}
void GameEngine::InitWindowAndRenderer(int windowWidth, int windowHeight) {
	//WINDOWS
	window = SDL_CreateWindow("My Fist Game Engine",		//NAME
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,		//POSITION
		windowWidth, windowHeight,							//SIZE
		SDL_WINDOW_SHOWN);									//SHOW BY DEFAULT
				
	if (window == nullptr) {
		std::cout << "Error al inicialzar window:" << SDL_GetError();
	}

	//RENDERER
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cout << "Error al inicialzar window:" << SDL_GetError();
	}

}