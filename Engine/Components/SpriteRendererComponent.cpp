#include "pch.h"
#include "SpriteRendererComponent.h"
#include "Engine.h"

namespace nu {
	FACTORY_REGISTER(SpriteRendererComponent)

	void SpriteRendererComponent::Draw(const Renderer& renderer) {
		if (m_texture) {
			renderer.DrawTexture(*m_texture, GetOwner()->GetTransform().pos.x, GetOwner()->GetTransform().pos.y, GetOwner()->GetTransform().rotation, GetOwner()->GetTransform().scale);
		}
	}

	void SpriteRendererComponent::Read(const json::value_t& value) {
		RendererComponent::Read(value);

		std::string TextureName;
		JSON_READ_NAME(value, "texture", TextureName);
		if (!TextureName.empty()) {
			m_texture = Resources().Get<Texture>(TextureName, Engine::Get().GetRenderer());
		}
	}
}