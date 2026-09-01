// Engine.cpp : Defines the functions for the static library.

#include "pch.h"
#include "Engine.h"

namespace nu {
	bool nu::Engine::Initialize() {
		m_renderer.initialize("Game engine", 1920, 1024);
		m_particlesystem.Initialize();
		m_input.Initialize();
		m_physics.Initialize();

		return true;
	}

	void Engine::Shutdown() {
		m_input.ShutDown();
		m_particlesystem.Shutdown();
		m_renderer.ShutDown();
		m_physics.Shutdown();
	}

	void Engine::Update() {
		m_time.Tick();
		m_input.Update();
		m_particlesystem.Update(m_time.GetDeltaTime());
		m_physics.Update(m_time.GetDeltaTime());
	}

}
