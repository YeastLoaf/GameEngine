#include "TripleShot.h"
#include "Core/Factory.h"

FACTORY_REGISTER(TripleShot)

void TripleShot::Update(float dt) {
	Actor::Update(dt);
}

void TripleShot::Read(const nu::json::value_t& value) {
    Actor::Read(value);

    JSON_READ_NAME(value, "speed", m_speed);
}