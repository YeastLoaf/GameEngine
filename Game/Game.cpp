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
#include <File.h>

using namespace nu;

int main() {
    // load the json data from a file
    std::string buffer;
    if (ReadTextFile("assets/data/data.json", buffer))
    {
        // show the contents of the json file (debug)
        std::cout << buffer << std::endl;

        // create json document from the json file contents
        rapidjson::Document document;
        if (json::Load("assets/data/data.json", document))
        {
            // read the data from the json
            std::string name;
            int age;
            float speed;
            bool isAwake;
            Vector2 position;
            Vector3 color;

            JSON_READ(document, name);
            JSON_READ(document, age);
            JSON_READ(document, speed);
            JSON_READ(document, isAwake);
            JSON_READ(document, position);
            JSON_READ(document, color);

            // show the data
            std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
            std::cout << position.x << " " << position.y << std::endl;
            std::cout << color.x << " " << color.y << " " << color.z << " " << std::endl;
        }
    }

    //+ After running the program, the console will display the contents of the** JSON** file and the** age** data.
    //    <div align = "left">
    //    <img src = "json-output.jpg" alt = "Output" width = "80%" / >
    //    < / div>

    //    ### Add Addition JSON Functions ###
    //    _Add additional functions to load different data types from the * *JSON * *file._

    //    + In the Json.h file, _add_ the following functions.
    //    + Add new functions to load * *float**, **bool**, **std::string**, ** vec2**, and **vec3**
    //    +Include * *Math / Vector2.h * *and **Math / Vector3.h * *

    return 0;

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

