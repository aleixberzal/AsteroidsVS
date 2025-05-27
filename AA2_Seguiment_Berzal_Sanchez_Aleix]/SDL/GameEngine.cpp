#include "GameEngine.h"
#include "GameObject.h"
#include "InputManager.h"

GameEngine::GameEngine(int windowWidth, int windowHeight) {
    InitSDL();
    InitWindowAndRenderer(windowWidth, windowHeight);
}

void GameEngine::Update() {
    // TIME
    float lastTime = (float)SDL_GetPerformanceCounter();
    float dt = 0.0f;

    const int FPS = 60;
    const float frameTime = 1.0f / (float)FPS;

    // SCENES
    std::map<std::string, Scene*> gameScene;

    gameScene["MainMenu"] = new MenuScene();
    gameScene["Gameplay"] = new GameplayScene();
    gameScene["Highscores"] = new HighscoresScene();

    Scene* currentScene = gameScene["Gameplay"];
    currentScene->Start(renderer);

    while (!IM.GetQuit()) {
        IM.Listen();

        // DELTA TIME CONTROL
        //Upgraded the delta with IA because my spaceShip did not move with the previous code. I still do not know why
        float currentTime = (float)SDL_GetPerformanceCounter();
        float frameDt = (currentTime - lastTime) / (float)SDL_GetPerformanceFrequency();
        lastTime = currentTime;
        dt += frameDt;

        if (dt >= frameTime) {
            // LOGIC
            currentScene->Update(dt);

            // RENDER
            SDL_RenderClear(renderer);
            currentScene->Render(renderer);
            SDL_RenderPresent(renderer);

            // SCENE TRANSITION
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
        std::cout << "[ ERROR ] - No es va poder inicialitzar SDL: " << SDL_GetError() << std::endl;
    }
    if (TTF_Init() < 0) {
        std::cout << "[ ERROR ] - No es va poder inicialitzar TTF: " << TTF_GetError() << std::endl;
    }
}

void GameEngine::InitWindowAndRenderer(int windowWidth, int windowHeight) {
    // Window
    window = SDL_CreateWindow("A, as an Asteroid Destroyer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight,
        SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cout << "[ ERROR ] - No es va poder crear la finestra: " << SDL_GetError() << std::endl;
    }

    // Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cout << "[ ERROR ] - No es va poder crear el renderer: " << SDL_GetError() << std::endl;
    }
}
