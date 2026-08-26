#pragma once

#include "Renderer.h"
#include "Random.h"
#include "Vector2.h"
#include "Input.h"
#include "GameTime.h"
#include "MathUtil.h"
#include "Actor.h"
#include "Scene.h"
#include "Text.h"
#include "Game.h"
#include "ParticleSystem.h"
#include "Texture.h"
#include "StringUtils.h"
#include "Factory.h"
#include "json.h"
#include "Factory.h"

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