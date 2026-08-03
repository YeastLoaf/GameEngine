#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "assets.h"
#include "FMod.h"
#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <filesystem>
#include <map>
#include <memory>

using namespace nu;

class Object {
public:
    Object() { std::cout << "constructor\n"; }
    ~Object() { std::cout << "destructor\n"; }

    Object(const Object& object) { std::cout << "copy\n"; }
    Object& operator = (const Object& object) { std::cout << "assignment\n"; return *this; }
};

int main() {
    std::cout << "==================object==================\n";
    {
        Object objectA;
        Object objectB(objectA);
        Object objectC;
        objectC = objectA;
    }

    std::cout << "\n==================raw pointers==================\n";
    {
        Object* objectA = new Object();
        std::cout << objectA << std::endl;
        Object* objectB = new Object(*objectA);
        std::cout << objectB << std::endl;
        Object* objectC = nullptr;
        objectC = objectA;
        std::cout << objectC << std::endl;

        delete objectA;
        delete objectB;
        //delete objectC;
    }

    std::cout << "\n==================smart pointers==================\n";
    {
        std::unique_ptr<Object> objectA = std::make_unique<Object>();
        std::cout << objectA.get() << std::endl;
        std::unique_ptr<Object> objectB;
        objectB = std::move(objectA);
        std::cout << objectA.get() << std::endl;
        std::cout << objectB.get() << std::endl;

        objectB.reset();
    }

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

    //audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound);
    //sounds.push_back(sound);

    // MAIM LOOP
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

        //audio jungle
        //if (e.GetInput().GetKeyPressed(SDL_SCANCODE_1))
        //{
        //    audio->playSound(sounds[0], 0, false, nullptr);
        //}


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

