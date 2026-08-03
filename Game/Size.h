#pragma once
#include "Actor.h"

struct SizeDesc : public nu::ActorDesc {
	float speed = 0.0f;
};

class Size : public nu::Actor {
public:
	Size() = default;
	Size(const SizeDesc& BulletDesc) : Actor{ BulletDesc }, m_speed{ BulletDesc.speed } {}
	Size(float speed, const nu::Transform& transform) : Actor{ transform }, m_speed{ speed } {}
	Size(float speed, const nu::Transform& transform, const nu::Model& model) : Actor{ transform, model }, m_speed{ speed } {}

	void Update(float dt) override;

private:
	int m_ammo = 0;
	float m_speed = 800.0f;
};