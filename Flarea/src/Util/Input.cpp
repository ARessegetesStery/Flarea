#include "flrpch.h"
#include "Input.h"

#include "Application/Event/Event.h"

namespace FLR
{
    LuaPort* Input::luaPort = nullptr;

    void Input::Init()
    {
        constexpr int scanCodeMax = 512;
        for (int code = 0; code != scanCodeMax; ++code)
            keyboardStatus[static_cast<unsigned int>(code)] = KeyState::KEY_UP;
    }

    KeyState Input::GetKeyStatus(unsigned int scancode)
    {
        return keyboardStatus[scancode];
    }

    KeyState Input::GetMouseStatus(uint8_t code)
    {
        return mouseStatus[code];
    }

    /*void Input::ProcessEvent(const Event* const event)
    {
        unsigned int curCode = event.key.keysym.scancode;
        uint8_t curButton = event.button.button;

        if (event.type == SDL_KEYDOWN && keyboardStatus[curCode] != KeyState::KEY_HOLD)
        {
            keyboardStatus[curCode] = KeyState::KEY_PRESSED;
            keyJustPressed.push_back(curCode);

#if defined(FLR_DEBUG) && defined(FLR_PRINT_INPUT) 
            cout << "Key " << static_cast<int>(curCode) << " Pressed\n";
#endif
        }
        else if (event.type == SDL_KEYUP && keyboardStatus[curCode] != KeyState::KEY_UP)
        {
            keyboardStatus[curCode] = KeyState::KEY_RELEASED;
            keyJustReleased.push_back(curCode);

#if defined(FLR_DEBUG) && defined(FLR_PRINT_INPUT) 
            cout << "Key " << static_cast<int>(curCode) << " Released\n";
#endif
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && mouseStatus[static_cast<int>(curButton)] != KeyState::KEY_HOLD)
        {
            mouseStatus[curButton] = KeyState::KEY_PRESSED;
            mouseJustPressed.push_back(curButton);
            
#if defined(FLR_DEBUG) && defined(FLR_PRINT_INPUT) 
            cout << "Mouse " << static_cast<int>(curButton) << " Pressed\n";
#endif
        }
        else if (event.type == SDL_MOUSEBUTTONUP && mouseStatus[static_cast<int>(curButton)] != KeyState::KEY_UP)
        {
            mouseStatus[curButton] = KeyState::KEY_RELEASED;
            mouseJustReleased.push_back(curButton);

#if defined(FLR_DEBUG) && defined(FLR_PRINT_INPUT) 
            cout << "Mouse " << static_cast<int>(curButton) << " Released\n";
#endif
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
			mousePos.x = event.motion.x;
			mousePos.y = event.motion.y;
		}
        else if (event.type == SDL_MOUSEWHEEL)
        {
			mouseWheel = event.wheel.preciseY;
            scrolledThisFrame = true;
		}
    }*/

    void Input::LateProcessEvent()
    {
        if (scrolledThisFrame == false)
            mouseWheel = 0;
        scrolledThisFrame = false;
    }

    void Input::LateUpdate()
    {
        for (const unsigned int& code : keyJustPressed)
            keyboardStatus[code] = KeyState::KEY_HOLD;
        for (const unsigned int& code : keyJustReleased)
            keyboardStatus[code] = KeyState::KEY_UP;
        for (const uint8_t& code : mouseJustPressed)
            mouseStatus[code] = KeyState::KEY_HOLD;
        for (const uint8_t& code : mouseJustReleased)
            mouseStatus[code] = KeyState::KEY_UP;

        keyJustPressed.clear();
        keyJustReleased.clear();
    }

}
