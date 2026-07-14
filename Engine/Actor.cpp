#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtil.h"

namespace nu {
	void Actor::Update(float dt) {
		m_transform.pos += (m_velocity * dt);
		
		m_transform.pos.x = Wrap(0.0f, 1920.0f, m_transform.pos.x);
		m_transform.pos.y = Wrap(0.0f, 1024.0f, m_transform.pos.y);
	}
	void Actor::Draw(const Renderer& renderer) const {
		renderer.SetColor(1.0f, 1.0f, 1.0f);
		renderer.DrawFillRect(m_transform.pos.x - (m_transform.scale + 0.5f), m_transform.pos.y - (m_transform.scale + 0.5f), m_transform.scale, m_transform.scale);
	}
}