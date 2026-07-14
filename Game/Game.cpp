#include "Engine.h"

using namespace nu;

int main()
{
    // INITIALIZE
    nu::Renderer renderer;
    renderer.initialize("Game engine", 1920, 1024);

    nu::Input input;
    input.Initialize();

    nu::Time time;

    Actor player{ Transform{ Vector2{640.0f, 512.0f}, 0.0f, 50.0f} };

    Vector2 pos{ 640.0f, 512.0f };
    Vector2 vel{ 0.0f, 0.0f };
    float speed = 400.0f;

    std::vector<Vector2> points;

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

        input.Update();

        time.Tick();

        if (input.GetButtonDown(Input::MouseButton::Left)) {
            if (points.empty()) {
                points.push_back(input.GetMousePos());
            }
            else {
                Vector2 v = points.back() - input.GetMousePos();

                if (v.Length() > 30.0f) {
                    points.push_back(input.GetMousePos());
                }
            }
        }

        //undo
        if (input.GetButtonPressed(Input::Right)) {
            if (!points.empty()) {
                points.pop_back();
            }
        }

        Vector2 force{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_D)) force.x = +speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) force.y = +speed;
        if (input.GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;

        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
        player.Update(time.GetDeltaTime());

        //vel += (force * time.GetDeltaTime());
        //pos += (vel * time.GetDeltaTime());

        //pos.x = Wrap(0.0f, 1920.0f, pos.x);
        //pos.y = Wrap(0.0f, 1024.0f, pos.y);


        // RENDER
        renderer.SetColor(0.0f, 0.0f, 0.0f);
        renderer.Clear();
        
        for (int i = 0; i < (int)points.size() - 1; i++) {
            renderer.SetColor(1.0f, 1.0f, 1.0f);
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        //char
        player.Draw(renderer);
        //renderer.SetColor(0.5f, 0.1f, 0.2f);
        //renderer.DrawFillRect(pos.x - 20, pos.y - 20, 40, 40);

        
        renderer.Present();
    }

    // SHUTDOWN
    renderer.ShutDown();

    return 0;
}

