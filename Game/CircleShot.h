#pragma once
#include "Framework/Actor.h"

struct CircleShotDesc : public nu::ActorDesc {
	float speed = 0.0f;
};

class CircleShot : public nu::Actor {
public:
	CircleShot() = default;
	CircleShot(const CircleShotDesc& BulletDesc) : Actor{ BulletDesc }, m_speed{ BulletDesc.speed } {}

	CLASS_PROTOTYPE(CircleShot);

	void Update(float dt) override;

	virtual void Read(const nu::json::value_t& value) override;

private:
	int m_ammo = 0;
	float m_speed = 800.0f;
};