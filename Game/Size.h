#pragma once
#include "Actor.h"

struct SizeDesc : public nu::ActorDesc {
	float speed = 0.0f;
};

class Size : public nu::Actor {
public:
	Size() = default;
	Size(const SizeDesc& BulletDesc) : Actor{ BulletDesc }, m_speed{ BulletDesc.speed } {}
	
	CLASS_PROTOTYPE(Size);

	void Update(float dt) override;

	virtual void Read(const nu::json::value_t& value) override;

private:
	int m_ammo = 0;
	float m_speed = 800.0f;
};