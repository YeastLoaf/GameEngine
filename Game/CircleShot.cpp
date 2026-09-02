#include "CircleShot.h"
#include "Core/Factory.h"

FACTORY_REGISTER(CircleShot)

void CircleShot::Update(float dt) {
	Actor::Update(dt);
}

void CircleShot::Read(const nu::json::value_t& value) {
    Actor::Read(value);

    JSON_READ_NAME(value, "speed", m_speed);
}