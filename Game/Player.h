#pragma once
#include "Actor.h"

struct PlayerDesc : public nu::ActorDesc {
	float speed = speed;
};

class Player : public nu::Actor {
public:
	Player() = default;
	Player(const PlayerDesc& playerDesc) : Actor{ playerDesc }, m_speed{ playerDesc.speed } { }
	Player(float speed, const nu::Transform& transform) : Actor{ transform }, m_speed{ speed } {}
	Player(float speed, const nu::Transform& transform, const nu::Model& model) : Actor{ transform, model }, m_speed{ speed } {}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;
	void Draw(const class nu::Renderer& renderer) const;

private:
	int m_ammo = 0;
	float sizes = 2.0f;
	float m_speed = 800.0f;
	bool triple = false;
	bool circle = false;
	bool size = false;
	float m_powerUpTimer = 0.0f;
};