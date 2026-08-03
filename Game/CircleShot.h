#pragma once
#include "Actor.h"

struct CircleShotDesc : public nu::ActorDesc {
	float speed = 0.0f;
};

class CircleShot : public nu::Actor {
public:
	CircleShot() = default;
	CircleShot(const CircleShotDesc& BulletDesc) : Actor{ BulletDesc }, m_speed{ BulletDesc.speed } {}
	CircleShot(float speed, const nu::Transform& transform) : Actor{ transform }, m_speed{ speed } {}
	CircleShot(float speed, const nu::Transform& transform, const nu::Model& model) : Actor{ transform, model }, m_speed{ speed } {}

	void Update(float dt) override;

private:
	int m_ammo = 0;
	float m_speed = 800.0f;
};