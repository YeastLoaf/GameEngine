#pragma once

#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Transform.h"
#include "MathUtil.h"
#include "File.h"
#include "json.h"
#include "StringUtils.h"

#include "Text.h"
#include "Texture.h"

#include "Factory.h"
#include "ResourceManager.h"

#include "Renderer.h"
#include "Input.h"
#include "GameTime.h"
#include "ParticleSystem.h"

#include "Actor.h"
#include "Scene.h"
#include "Game.h"

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

		Engine& operator = (const Engine&) = delete;
	private:
		Engine() = default;

	private:
		Input m_input;
		Renderer m_renderer;
		ParticleSystem m_particlesystem;
		Time m_time;
	};
}