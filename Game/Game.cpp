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

class Animal {
public:
    virtual void speak() { std::cout << "???"; }
};

class Cat : public Animal {
    void speak() override { std::cout << "meow"; }
};

class Dog : public Animal {
    void speak() override { std::cout << "woof"; }
};

class Bird : public Animal {
    void speak() override { std::cout << "scraw"; }
};

/*
enum class Type {
    Cat = 1,
    Dog = 2,
    Bird = 3
};

Animal* Animalfactory(Type id) {
    Animal* animal = nullptr;

    switch (id) {
    case Type::Cat:
        animal = new Cat;
        break;
    case Type::Dog:
        animal = new Dog;
        break;
    case Type::Bird:
        animal = new Bird;
        break;
    }

    return animal;
}
*/

Animal* Animalfactory(const std::string& id) {
    Animal* animal = nullptr;

    if (nu::ToLower(id) == "cat") animal = new Cat;
    else if (nu::EqualsIgnoreCase(id, "Dog")) animal = new Dog;
    else if (id == "Bird") animal = new Bird;

    return animal;
}
/*
class ICreater {
public:
    virtual ~ICreater() = default;
    virtual std::unique_ptr<Animal> Create() = 0;
};

template <typename T>
class Creater : public ICreater {
public:
    std::unique_ptr<Animal> Create() override {
        return std::make_unique<T>();
    }
};

std::map<std::string, std::unique_ptr<ICreater>> registry;

*/

int main() {
    //Factory::Instance().Register<Actor>("Actor");
    //auto actor = Factory::Instance().Create<Actor>("Actor");
    //std::cout << actor->IsActive() << std::endl;



    //registry["Cat"] = std::make_unique<Creater<Cat>>();
    //registry["Dog"] = std::make_unique<Creater<Dog>>();

    //{
    //    auto animal = registry["Dog"]->Create();
    //    animal->speak();
    //}

    //std::string selection;

    //std::cout << "Selecte animal: ";
    //std::cin >> selection;

    //auto animal = Animalfactory(selection);
    //if (animal) animal->speak();

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

