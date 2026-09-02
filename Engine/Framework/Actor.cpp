#include "pch.h"
#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Math/MathUtil.h"
#include "Renderer/Texture.h"
#include "Core/Factory.h"
#include "Engine.h"
#include "Resources/ResourceManager.h"

namespace nu {
	FACTORY_REGISTER(Actor)

		Actor::Actor(const Actor& other) : Object{ other }, 
		m_tag{ other.m_tag }, 
		m_transform{ other.m_transform }, 
		m_velocity{ other.m_velocity }, 
		m_damping{ other.m_damping },
		m_lifespan{ other.m_lifespan } {
			// clone all components
			for (const auto& component : other.m_components) {
				auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
				AddComponent(std::move(clone));
			}
		}

	void Actor::Update(float dt) {
		// lifespan
		if (m_lifespan > 0.0f) {
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0.0f);
		}

		for (auto& component : m_components) {
			component->Update(dt);
		}

		//physics
		m_transform.pos += (m_velocity * dt);
		m_velocity *= 1.0f / ((1.2f) + m_damping * dt);
		
		m_transform.pos.x = Wrap(0.0f, 1920.0f, m_transform.pos.x);
		m_transform.pos.y = Wrap(0.0f, 1024.0f, m_transform.pos.y);
	}

	void Actor::Draw(const Renderer& renderer) const {
		for (auto& component : m_components) {
			auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
			if (rendererComponent) {
				rendererComponent->Draw(renderer);
			}
		}
	}

	float Actor::GetRadius() const {
		return 0.0f;
	}

	void Actor::AddComponent(std::unique_ptr<Component> component) {
		component->SetOwner(this);
		m_components.push_back(std::move(component));
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

		if (JSON_HAS_NAME(value, "components"))
		{
			// iterate through components
			for (auto& componentValue : JSON_GET_NAME(value, "components").GetArray())
			{
				// get component type
				std::string typeName;
				JSON_READ_NAME(componentValue, "type", typeName);

				std::cout << "Loading component type: " << typeName << std::endl;

				// create component of type
				auto component = Factory::Instance().Create<Component>(typeName);

				if (component) {
					component->Read(componentValue);
					AddComponent(std::move(component));
				}
			}
		}
	}
}