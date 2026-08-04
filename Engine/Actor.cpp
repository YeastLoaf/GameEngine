#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtil.h"

namespace nu {
	void Actor::Update(float dt) {
		//lifespan
		if (m_lifespan > 0.0f) {
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0.0f);
		}

		//physics
		m_transform.pos += (m_velocity * dt);
		m_velocity *= 1.0f / ((1.2f) + m_damping * dt);
		
		m_transform.pos.x = Wrap(0.0f, 1920.0f, m_transform.pos.x);
		m_transform.pos.y = Wrap(0.0f, 1024.0f, m_transform.pos.y);
	}
	void Actor::Draw(const Renderer& renderer) const {
		if (m_model) {
			renderer.DrawModel(*m_model, m_transform);
		}
	}
	float Actor::GetRadius() const {
		return m_model->GetRadius() * m_transform.scale * 0.9f;
	}
}