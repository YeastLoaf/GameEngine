#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "assets.h"
#include "FMod.h"
#include "SpaceGame.h"
#include "Resources/ResourceManager.h"
#include "Bullet.h"
#include "Size.h"
#include "CircleShot.h"
#include "TripleShot.h"

#include <iostream>
#include <vector>
#include <filesystem>
#include <map>
#include <memory>
#include <random>
#include <fstream>
#include <Core/File.h>

using namespace nu;

int main() {
    Engine& e = Engine::Get();

    // INITIALIZE
    e.Initialize();

    SpaceGame game;
    game.Initialize();

    // audio
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    FMOD::Sound* sound = nullptr;
    std::vector<FMOD::Sound*> sounds;

    // MAIN LOOP
    bool quit = false;
    while (!quit) {

        // UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }
        
        // engine
        Engine::Get().Update();

        float dt = Engine::Get().GetTime().GetDeltaTime();

        game.Update(dt);
        audio->update();


        // RENDER
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();

        game.Draw(Engine::Get().GetRenderer());

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());
        
        Engine::Get().GetRenderer().Present();
    }

    // SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
}