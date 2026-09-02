#pragma once
#include "Framework/Actor.h"

struct TripleShotDesc : public nu::ActorDesc {
	float speed = 0.0f;
};

class TripleShot : public nu::Actor {
public:
	TripleShot() = default;
	TripleShot(const TripleShotDesc& BulletDesc) : Actor{ BulletDesc }, m_speed{ BulletDesc.speed } {}

	CLASS_PROTOTYPE(TripleShot);

	void Update(float dt) override;

	virtual void Read(const nu::json::value_t& value) override;

private:
	int m_ammo = 0;
	float m_speed = 800.0f;
};