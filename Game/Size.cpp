#include "Size.h"
#include "Factory.h"

FACTORY_REGISTER(Size)

void Size::Update(float dt) {
	Actor::Update(dt);
}

void Size::Read(const nu::json::value_t& value) {
    Actor::Read(value);

    JSON_READ_NAME(value, "speed", m_speed);
}