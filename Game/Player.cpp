#include "Player.h"
#include "Renderer.h"
#include "Engine.h"
#include "SpaceGame.h"
#include "../Game/Bullet.h"
#include "../Game/Assets.h"
#include "FMod.h"
#include "Factory.h"

#include <ResourceManager.h>

FACTORY_REGISTER(Player)

void Player::Update(float dt) {
    float thrust = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +m_speed;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;

    SetRotation(m_transform.rotation + rotate * dt);

    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    FMOD::Sound* sound = nullptr;
    std::vector<FMOD::Sound*> sounds;

    audio->createSound("laser.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    // particle system
    if (thrust) {
        nu::Particle particle;
        nu::Vector2 offset{ -10.0f, 0.0f };
        offset = offset.Rotate(m_transform.rotation * nu::DegToRad);
        particle.position = m_transform.pos + offset;

        nu::Color colors[3] = { { 1.0f, 1.0f, 1.0f}, { 1.0f, 0.0f, 0.0f}, { 1.0f, 1.0f, 0.0f} };
        particle.color = colors[nu::RandomInt(3)];
        particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
        particle.velocity = nu::Vector2{ nu::RandomFloat(- 30.0f, -100.0f), 0.0f}.Rotate((m_transform.rotation + nu::RandomInt(-10, 10)) * nu::DegToRad);

        nu::Engine::Get().GetPS().AddParticle(particle);
    }

    nu::Vector2 forward{ 1, 0 };
    nu::Vector2 vel = forward.Rotate(m_transform.rotation * nu::DegToRad) * thrust;
    AddVelocity(vel * dt);

    if (m_powerUpTimer > 0.0f) {
        m_powerUpTimer -= dt;
    } else {
        triple = false;
        circle = false;
        size = false;
    }

    if (size == true) {
          sizes = 8.0f;
    }
    else {
        sizes = 2.0f;
    }
    //fire
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {

        BulletDesc desc;
        desc.name = "Bullet";
        desc.tag = "PlayerBullet";
        //desc.model = assets::bulletModel;
        desc.texture = nu::Resources().Get<nu::Texture>("bullet.png", nu::Engine::Get().GetRenderer());
        desc.transform = m_transform;
        desc.transform.scale = sizes;
        desc.speed = 400.0f;
        desc.lifespan = 2.0f;

        audio->playSound(sounds[0], 0, false, nullptr);

        Bullet* bullet = new Bullet{ desc };
        m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));
        
        if (triple == true) {
            desc.transform.rotation += 10.0f;
            Bullet* bullet2 = new Bullet{ desc };
            m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));

            desc.transform.rotation -= 20.0f;
            Bullet* bullet3 = new Bullet{ desc };
            m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));
        }

        if (circle == true) {
            for (int x = 0; x < 7; x++) {
                desc.transform.rotation += 45.0f;
                Bullet* bullet2 = new Bullet{ desc };
                m_scene->AddActor(std::move(std::make_unique<Bullet>(desc)));
            }
        }
    }

    // bullet time
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_X)) {
        nu::Engine::Get().GetTime().SetTimeScale(0.5f);
    } else {
        nu::Engine::Get().GetTime().SetTimeScale(1.0f);
    }

    Actor::Update(dt);
}

void Player::Draw(const nu::Renderer& renderer) const {
	Actor::Draw(renderer);
}

void Player::OnCollision(Actor* other) {
    if (other->GetTag() == "Enemy") {
        SetDestroyed(true);
        ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();
    }

    if (other->GetTag() == "TripleShot") {
        m_powerUpTimer = 10.0f;
        other->SetDestroyed(true);
        triple = true;
    }

    if (other->GetTag() == "CircleShot") {
        m_powerUpTimer = 10.0f;
        other->SetDestroyed(true);
        circle = true;
    }

    if (other->GetTag() == "Size") {
        m_powerUpTimer = 10.0f;
        other->SetDestroyed(true);
        size = true;
    }
}

void Player::Read(const nu::json::value_t& value) {
    Actor::Read(value);

    JSON_READ_NAME(value, "speed", m_speed);
}