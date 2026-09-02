#pragma once

#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Math/MathUtil.h"
#include "Core/File.h"
#include "Serialization/json.h"
#include "Core/StringUtils.h"
#include "Physics/Physics.h"

#include "Renderer/Text.h"
#include "Renderer/Texture.h"

#include "Core/Factory.h"
#include "Resources/ResourceManager.h"

#include "Renderer/Renderer.h"
#include "Input/Input.h"
#include "Core/GameTime.h"
#include "Renderer/ParticleSystem.h"

#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Framework/Game.h"

#include <vector>
#include <iostream>

namespace nu {
	class Engine {
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		Time& GetTime() { return m_time; }
		ParticleSystem& GetPS() { return m_particlesystem; }
		Physics& GetPhysics() { return m_physics; }

		Engine& operator = (const Engine&) = delete;
	private:
		Engine() = default;

	private:
		Input m_input;
		Renderer m_renderer;
		ParticleSystem m_particlesystem;
		Time m_time;
		Physics m_physics;
	};
}