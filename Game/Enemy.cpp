#include "Enemy.h"
#include "Renderer.h"
#include "Engine.h"
#include "Player.h"
#include "SpaceGame.h"
#include "FMod.h"

//FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt) {
    Player* player = m_scene->GetActorByName<Player>("Player");
    if (player) {
        nu::Vector2 direction = player->GetTransform().pos - m_transform.pos;
        float rotation = direction.Angle();
        SetRotation(rotation * nu::RadToDeg);

        nu::Vector2 forward{ 1, 0 };
        forward = forward.Rotate(m_transform.rotation * nu::DegToRad);
        AddVelocity(forward * m_speed * dt);
    }


    // particle system
    nu::Particle particle;
    nu::Vector2 offset{ -10.0f, 0.0f };
    offset = offset.Rotate(m_transform.rotation * nu::DegToRad);
    particle.position = m_transform.pos + offset;
    particle.color = { 0.0f, 1.0f, 0.0f };
    particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
    particle.velocity = { nu::RandomFloat(-20.0f, 20.0f), nu::RandomFloat(-20.0f, 20.0f) };

    nu::Engine::Get().GetPS().AddParticle(particle);

    Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other) {
    if (other->GetTag() == "PlayerBullet") {

        FMOD::System* audio;
        FMOD::System_Create(&audio);

        void* extradriverdata = nullptr;
        audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

        FMOD::Sound* sound = nullptr;
        std::vector<FMOD::Sound*> sounds;

        audio->createSound("explosion.wav", FMOD_DEFAULT, 0, &sound);
        sounds.push_back(sound);
        audio->playSound(sounds[0], 0, false, nullptr);

        SetDestroyed(true);
        other->SetDestroyed(true);

        ((SpaceGame*)m_scene->GetGame())->AddPoints(100);

        // create particle explosion
        for (int i = 0; i < 100; i++)
        {
            float cool = nu::RandomFloat();
            nu::Particle particle;
            particle.position = m_transform.pos;
            particle.color = { cool, cool, cool};
            particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
            particle.velocity = { nu::RandomFloat(-60.0f, 60.0f), nu::RandomFloat(-60.0f, 60.0f) };

            nu::Engine::Get().GetPS().AddParticle(particle);
        }
    }
}

void Enemy::Draw(const nu::Renderer& renderer) const {
    Actor::Draw(renderer);
}
