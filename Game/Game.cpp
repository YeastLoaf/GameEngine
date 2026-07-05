#include <iostream>
#include "Engine.h"
#include "SDL3/SDL.h"

int main()
{
    nu::Renderer renderer;
    renderer.initialize("Game engine", 1920, 1024);

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        renderer.SetColor(0, 0, 0);
        renderer.Clear();

        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set render draw color to black
        //SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 255);
        //SDL_RenderClear(renderer); // Clear the renderer
        
        for (int x = 0; x < 1000; x++) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawPoint(rand() % 1920, rand() % 1024);
            //SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 255);
            //SDL_RenderPoint(renderer, rand() % 1280, rand() % 1024);
        }

        for (int x = 0; x < 20; x++) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawLine(rand() % 1920, rand() % 1024, rand() % 1920, rand() % 1024);
        }

        for (int x = 0; x < 15; x++) {
            renderer.SetColor(rand() % 256, rand() % 500, rand() % 500);
            renderer.DrawFillRect(rand() % 1920, rand() % 1024, rand() % 192, rand() % 102);
        }
        //SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 255); // Set render draw color to green
        //SDL_RenderFillRect(renderer, &greenSquare); // Render the rectangle

        //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //SDL_RenderDebugText(renderer, 30, 30, "Hello World.");

        //SDL_RenderPresent(renderer); // Render the screen
        renderer.Present();
    }

    renderer.ShutDown();

    return 0;
}

