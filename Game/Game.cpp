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

using namespace nu;

class Object {
public:
    Object() { std::cout << "constructor\n"; }
    ~Object() { std::cout << "destructor\n"; }

    Object(const Object& object) { std::cout << "copy\n"; }
    Object& operator = (const Object& object) { std::cout << "assignment\n"; return *this; }
};

uint32_t seed = 1234;

uint32_t RNG(){
    seed = (seed * 1103515245) + 12345;
    return seed;
}

int main() {
    /*
    // rand()
    for (size_t i = 0; i < 10; i++) std::cout << RNG() << " ";
    std::cout << std::endl;
    seed = 1234;
    for (size_t i = 0; i < 10; i++) std::cout << RNG() << " ";
    std::cout << std::endl;
    
    //srand((unsigned int)time(NULL));
    SeedRandom((unsigned int)time(NULL));
    for (size_t i = 0; i < 10; i++) std::cout << rand() << " ";
    std::cout << std::endl;

    // random<>
    std::random_device randomDevice;
    std::cout << randomDevice.min() << std::endl;
    std::cout << randomDevice.max() << std::endl;
    std::cout << randomDevice.entropy() << std::endl;

    std::mt19937 generator(randomDevice());

    std::uniform_int_distribution<> dist(0, 20);
    for (size_t i = 0; i < 20; i++) std::cout << dist(generator) << " ";
    std::cout << std::endl;

    std::uniform_real_distribution<float> distReal(-10.0f, 20.0f);
    for (size_t i = 0; i < 20; i++) std::cout << distReal(generator) << " ";
    std::cout << std::endl;

    return 0;

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

    std::cout << "\n==================unique pointers==================\n";
    {
        std::unique_ptr<Object> objectA = std::make_unique<Object>();
        std::cout << objectA.get() << std::endl;
        std::unique_ptr<Object> objectB;
        objectB = std::move(objectA);
        std::cout << objectB.get() << std::endl;

        objectB.reset();
    }

    std::cout << "\n==================shared pointers==================\n";
    std::shared_ptr<Object> objectC;
    {
        std::shared_ptr<Object> objectA = std::make_shared<Object>();
        std::cout << objectA.get() << std::endl;
        std::cout << objectA.use_count() << std::endl;
        auto objectB = objectA;
        std::cout << objectB.get() << std::endl;
        std::cout << objectB.use_count() << std::endl;
        objectC = objectA;
        std::cout << objectC.get() << std::endl;
        std::cout << objectC.use_count() << std::endl;
    }
    std::cout << objectC.use_count() << std::endl;

    //return 0;

    */

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


    // create texture, using shared_ptr so texture can be shared
    //std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    //texture->Load("player.png", Engine::Get().GetRenderer());

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


        // RENDER
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();

        game.Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().DrawTexture(*Resources().Get<Texture>("player.png", Engine::Get().GetRenderer()), 30, 30);

        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());
        
        Engine::Get().GetRenderer().Present();
    }

    // SHUTDOWN
    Engine::Get().Shutdown();

    return 0;
}

