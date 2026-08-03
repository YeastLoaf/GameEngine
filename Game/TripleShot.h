#pragma once
#include "Actor.h"

struct TripleShotDesc : public nu::ActorDesc {
	float speed = 0.0f;
};

class TripleShot : public nu::Actor {
public:
	TripleShot() = default;
	TripleShot(const TripleShotDesc& BulletDesc) : Actor{ BulletDesc }, m_speed{ BulletDesc.speed } {}
	TripleShot(float speed, const nu::Transform& transform) : Actor{ transform }, m_speed{ speed } {}
	TripleShot(float speed, const nu::Transform& transform, const nu::Model& model) : Actor{ transform, model }, m_speed{ speed } {}

	void Update(float dt) override;

private:
	int m_ammo = 0;
	float m_speed = 800.0f;
};