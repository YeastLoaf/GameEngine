#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtil.h"
#include "Texture.h"
#include "Factory.h"
#include <Components/RendererComponent.h>

//FACTORY_REGISTER(Actor);

namespace nu {

	void Actor::Update(float dt) {
		//lifespan
		if (m_lifespan > 0.0f) {
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0.0f);
		}

		for (auto component : m_components) {
			component->Update(dt);
		}

		//physics
		m_transform.pos += (m_velocity * dt);
		m_velocity *= 1.0f / ((1.2f) + m_damping * dt);
		
		m_transform.pos.x = Wrap(0.0f, 1920.0f, m_transform.pos.x);
		m_transform.pos.y = Wrap(0.0f, 1024.0f, m_transform.pos.y);
	}
	void Actor::Draw(const Renderer& renderer) const {
		//for (auto component : m_components) {
		//	component->Draw(renderer);
		//}

		if (m_model) {
			renderer.DrawModel(*m_model, m_transform);
		}
		if (m_texture) {
			renderer.DrawTexture(*m_texture, m_transform.pos.x, m_transform.pos.y, m_transform.rotation, m_transform.scale);
		}

		//for (auto component : m_components) {
		//	auto rendererComponent = dynamic_cast<RendererComponent*>(component);
		//	if (rendererComponent) {
		//		rendererComponent->Draw(renderer);
		//	}
		//}
	}

	float Actor::GetRadius() const {
		if (m_model) return m_model->GetRadius() * m_transform.scale * 0.9f;
		if (m_texture) return (m_texture->GetSize().Length() * 0.5f) * 0.5f;
		return 0.0f;
	}

	void Actor::Read(const json::value_t& value) {
		Object::Read(value);

		if (JSON_HAS_NAME(value, "transform")) {
			m_transform.Read(JSON_GET_NAME(value, "transform"));
		}

		JSON_READ_NAME(value, "tag", m_tag);
		JSON_READ_NAME(value, "lifespan", m_lifespan);
		JSON_READ_NAME(value, "velocity", m_velocity);
		JSON_READ_NAME(value, "damping", m_damping);
	}
}