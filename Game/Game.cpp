#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "assets.h"
#include "FMod.h"
#include "SpaceGame.h"
#include "ResourceManager.h"

#include <iostream>
#include <vector>
#include <filesystem>
#include <map>
#include <memory>
#include <random>
#include <fstream>

using namespace nu;

int main() {
    //SetWorkingDirectory("assets");

    //{
    //    // read file (input file ))
    //    std::ifstream file("assets/data/text.txt");
    //    if (file.is_open()) {
    //        std::string str;
    //        while (std::getline(file, str)) {
    //        std::cout << str << std::endl;
    //        }
    //    }
    //    else {
    //        std::cout << "Could not load" << std::endl;
    //    }
    //    file.close();
    //}

    //{
    //    // read file (output file ))
    //    std::ofstream file("assets/data/text.txt", std::ios::app);
    //    if (file.is_open()) {
    //        file << "Have a day.\n";
    //    }
    //}

    //{
    //    // read / write (input / output file)
    //    std::fstream file("assets/data/text.txt", std::ios::in | std::ios::out | std::ios::app);
    //    if (file.is_open()) {
    //        // input
    //        file << "Add a line.\n";
    //        file.seekg(0);
    //        // output
    //        std::string str;
    //        while (std::getline(file, str)) {
    //            std::cout << str << std::endl;
    //        }
    //    }
    //}

    //{
    //    std::string name;
    //    int score;
    //    bool isAlive;

    //    // save game data
    //    bool save = false;
    //    if (save) {
    //        name = "Tyler";
    //        score = 420;
    //        isAlive = true;

    //        std::ofstream file("assets/data/game.txt", std::ios::trunc);
    //        if (file.is_open()) {
    //            file << name << "\n";
    //            file << score << "\n";
    //            file << std::boolalpha << isAlive << "\n";
    //        }
    //    }

    //    // load game data
    //    bool load = true;
    //    if (load) {
    //        // read file (input file ))
    //        std::ifstream file("assets/data/game.txt");
    //        if (file.is_open()) {
    //            std::getline(file, name);

    //            std::string str;
    //            std::getline(file, str);

    //            score = std::stoi(str);
    //            file >> std::boolalpha >> isAlive;
    //        }
    //    }

    //    std::cout << name << std::endl;
    //    std::cout << score << std::endl;
    //    std::cout << std::boolalpha << isAlive << std::endl;
    //}

    //return 0;

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

