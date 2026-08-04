#pragma once
#include "Actor.h"

struct EnemyDesc : public nu::ActorDesc {
	float speed = speed;
};

class Enemy : public nu::Actor {
public:
	Enemy() = default;
	Enemy(const EnemyDesc& enemyDesc) : Actor{ enemyDesc }, m_speed{ enemyDesc.speed } {}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;
	void Draw(const class nu::Renderer& renderer) const;

private:
	int m_ammo = 0;
	float m_speed = 8000.0f;
};