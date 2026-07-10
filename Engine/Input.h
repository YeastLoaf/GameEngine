#pragma once
#include "Vector2.h"
#include <vector>

namespace nu {
	class Input {
	public:
		enum MouseButton {
			Left = 1,
			Middle = 2,
			Right = 3
		};
	public:
		bool Initialize();
		void ShutDown();

		void Update();

		bool GetKeyDown(int key) const { return m_keyStates[key]; }
		bool GetPrevKeyDown(int key) const { return m_prevKeyStates[key]; }
		bool GetKeyPressed(int key) const { return !m_prevKeyStates[key] && m_keyStates[key]; }
		bool GetKeyReleased(int key) const { return !m_prevKeyStates[key] && !m_keyStates[key]; }

		bool GetButtonDown(MouseButton button) const { return m_bottonStates & GetButtonBit(button); }
		bool GetPrevButtonDown(MouseButton button) const { return m_prevBottonStates & GetButtonBit(button); }
		bool GetButtonPressed(MouseButton button) const { return !GetPrevButtonDown(button) && GetButtonDown(button); }
		bool GetButtonReleased(MouseButton button) const { return GetPrevButtonDown(button) && !GetButtonDown(button); }

		Vector2 GetMousePos() const { return m_mousePos; }

	private:
		uint32_t GetButtonBit(MouseButton button) const;

	private:
		// keyboard stuff
		std::vector<bool> m_keyStates;
		std::vector<bool> m_prevKeyStates;

		// mouse stuff
		uint32_t m_bottonStates = 0;
		uint32_t m_prevBottonStates = 0;

		Vector2 m_mousePos;
	};
}