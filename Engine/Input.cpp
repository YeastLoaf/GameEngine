#include "pch.h"
#include "Input.h"

#include <SDL3/SDL.h>

namespace nu {

    bool Input::Initialize() {
        int numkeys;
        const bool* keyState = SDL_GetKeyboardState(&numkeys);
        m_keyStates.resize(numkeys);

        std::copy(keyState, keyState + numkeys, m_keyStates.begin());
        m_prevKeyStates = m_keyStates;

        return true;
    }

    void Input::ShutDown() {
        //
    }

    void Input::Update() {
        m_prevKeyStates = m_keyStates;
        const bool* keyState = SDL_GetKeyboardState(NULL);
        std::copy(keyState, keyState + m_keyStates.size(), m_keyStates.begin());

        m_prevBottonStates = m_bottonStates;
        m_bottonStates = SDL_GetMouseState(&m_mousePos.x, &m_mousePos.y);
    }

    uint32_t Input::GetButtonBit(MouseButton button) const {
        return SDL_BUTTON_MASK((uint32_t)button);
    }
}