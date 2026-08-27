#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "TripleShot.h"
#include "CircleShot.h"
#include "Size.h"
#include "Assets.h"
#include "FMod.h"

#include <memory>
#include <ResourceManager.h>

using namespace nu;

bool SpaceGame::Initialize() {
    Game::Initialize();

    m_scene = new Scene();
    m_scene->SetGame(this);
    m_scene->Load("assets/data/scene.json");

    titleFont = Resources().Get<Font>("assets/fonts/airstrike.ttf", 64.0f);
    titleFont->Load("assets/fonts/airstrike.ttf", 64);

    titleText = new Text(titleFont);
    titleText->Create(Engine::Get().GetRenderer(), "XENON", Color{ 1.0f, 1.0f, 1.0f });

    gameFont = Resources().Get<Font>("assets/fonts/airstrike.ttf", 64.0f);
    gameFont->Load("assets/fonts/airstrike.ttf", 32);

    scoreText = new Text(gameFont);
    livesText = new Text(gameFont);
    finalScoreText = new Text(gameFont);

    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    FMOD::Sound* sound = nullptr;
    std::vector<FMOD::Sound*> sounds;

    audio->createSound("music.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->playSound(sounds[0], 0, false, nullptr);

    return true;
}

void SpaceGame::Update(float dt) {
    switch (m_gamestate)
    {
    case GameState::Title:
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gamestate = GameState::StartGame;
        }
        break;
    case GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_spawnTime = 5.0f;
        m_stateTimer = 0.5f;
        m_powerUpTimer = 5.0f;
        m_gamestate = GameState::StartLevel;
        break;
    case GameState::StartLevel:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_scene->RemoveAllActors();
            SpawnPlayer();
            m_spawnTime = 5.0f;
            m_gamestate = GameState::Game;
        }
        break;
    case GameState::Game:
        m_spawnTimer -= dt;
        m_powerUpTimer -= dt;
        if (m_spawnTimer <= 0.0f) {
            m_spawnTimer = m_spawnTime;
            SpawnEnemy();
            m_spawnCount++;
            if (m_spawnCount > 5) {
                m_spawnCount = 0;
                if (m_spawnTime > 0.5f) {
                    m_spawnTime -= 0.5f;
                }
            }
        }

        if (m_powerUpTimer <= 0.0f) {
            SpawnPowerUp();
            if (m_spawnTime > 3.0f) {
                m_powerUpTimer = m_spawnTime;
            }
            else if (m_spawnTime > 1.0f) {
                m_powerUpTimer = m_spawnTime * 5;
            }
            else {
                m_powerUpTimer = m_spawnTime * 10;
            }
        }
        break;
    case GameState::GameOver:
        m_finalScore = m_score;
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_scene->RemoveAllActors();
        }
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gamestate = GameState::Title;
        }
        break;
    default:
        break;
    }

    Game::Update(dt);
}

void SpaceGame::Draw(nu::Renderer& renderer) {
    renderer.DrawTexture(*nu::Resources().Get<Texture>("background.png", Engine::Get().GetRenderer()), 1000, 500);

    switch (m_gamestate)
    {
    case GameState::Title:
        titleText->Draw(renderer, 800.0f, 400.0f);
        break;
    case GameState::StartGame:
        break;
    case GameState::StartLevel:
        break;
    case GameState::Game:
        scoreText->Create(renderer, "Score: " + std::to_string(m_score), { 1.0f, 1.0f, 1.0f });
        scoreText->Draw(renderer, 30.0f, 30.0f);
        livesText->Create(renderer, "Lives: " + std::to_string(m_lives), { 1.0f, 1.0f, 1.0f });
        livesText->Draw(renderer, renderer.GetWidth() - 160.0f, 30.0f);
        break;
    case GameState::GameOver:
        finalScoreText->Create(renderer, "Final score: " + std::to_string(m_finalScore), { 1.0f, 1.0f, 1.0f });
        finalScoreText->Draw(renderer, 800.0f, 400.0f);
        break;
    default:
        break;
    }

    Game::Draw(renderer);
}

void SpaceGame::OnPlayerDead() {
    m_lives--;

    if (m_lives <= 0) {
        m_gamestate = GameState::GameOver;
    } else {
        m_gamestate = GameState::StartLevel;
    }

    m_stateTimer = 2.0f;
}

void SpaceGame::SpawnPlayer() {
    auto actor = Factory::Instance().Create<Actor>("PlayerPrototype");
    m_scene->AddActor(std::move(actor));
}

void SpaceGame::SpawnEnemy() {
    auto actor = Factory::Instance().Create<Actor>("EnemyPrototype");
    actor->SetPosition(nu::Vector2{ nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight()) });
    m_scene->AddActor(std::move(actor));
}

void SpaceGame::SpawnPowerUp() {
    int power = nu::RandomInt(3);

    if (power == 1) {
        TripleShotDesc tripleShot;
        tripleShot.name = "TripleShot";
        tripleShot.tag = "TripleShot";
        tripleShot.model = assets::tripleShotModel;
        tripleShot.transform = Transform{ Vector2{ nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight())}, 90.0f, 10.0f };
        tripleShot.vel = Vector2{ 0.0f, 0.0f };
        tripleShot.damping = 0.0f;

        std::unique_ptr<TripleShot> tripleShoter = std::make_unique<TripleShot>(tripleShot);
        m_scene->AddActor(std::move(tripleShoter));
    } else if (power == 0) {
        CircleShotDesc circleShot;
        circleShot.name = "CircleShot";
        circleShot.tag = "CircleShot";
        circleShot.model = assets::circleShotModel;
        circleShot.transform = Transform{ Vector2{ nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight())}, 90.0f, 10.0f };
        circleShot.vel = Vector2{ 0.0f, 0.0f };
        circleShot.damping = 0.0f;

        std::unique_ptr<CircleShot> circleShoter = std::make_unique<CircleShot>(circleShot);
        m_scene->AddActor(std::move(circleShoter));
    } else if (power == 2) {
        SizeDesc Sizes;
        Sizes.name = "Size";
        Sizes.tag = "Size";
        Sizes.model = assets::sizeModel;
        Sizes.transform = Transform{ Vector2{ nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight())}, 90.0f, 10.0f };
        Sizes.vel = Vector2{ 0.0f, 0.0f };
        Sizes.damping = 0.0f;

        std::unique_ptr<Size> Sizer = std::make_unique<Size>(Sizes);
        m_scene->AddActor(std::move(Sizer));
    }
}