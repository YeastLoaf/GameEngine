#pragma once
#include "Actor.h"

struct TripleShotDesc : public nu::ActorDesc {
	float speed = 0.0f;
};

class TripleShot : public nu::Actor {
public:
	TripleShot() = default;
	TripleShot(const TripleShotDesc& BulletDesc) : Actor{ BulletDesc }, m_speed{ BulletDesc.speed } {}

	void Update(float dt) override;

private:
	int m_ammo = 0;
	float m_speed = 800.0f;
};