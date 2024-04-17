#ifndef _INPUT_H
#define _INPUT_H

namespace FLR
{
	class LuaPort;
	class Event;

	enum class KeyState
	{
		KEY_UP, KEY_PRESSED, KEY_HOLD, KEY_RELEASED
	};

	class Input
	{
	public:
		static void Init();

		static inline bool IsKeyDown(unsigned int code) 
		{
			return Input::GetKeyStatus(code) == KeyState::KEY_PRESSED ||
				Input::GetKeyStatus(code) == KeyState::KEY_HOLD;
		}

		static inline bool IsKeyUp(unsigned int code)
		{
			return Input::GetKeyStatus(code) == KeyState::KEY_RELEASED ||
				Input::GetKeyStatus(code) == KeyState::KEY_UP;
		}

		static KeyState GetKeyStatus(unsigned int);
		static KeyState GetMouseStatus(uint8_t);

		static inline bool IsMouseButtonDown(uint8_t code) 
			{ return mouseStatus[code] == KeyState::KEY_PRESSED || mouseStatus[code] == KeyState::KEY_HOLD; }

		//static void ProcessEvent(const Event* const);
		static void LateProcessEvent();
		static void LateUpdate();

		static inline glm::vec2 GetMousePos() { return mousePos; }
		static inline float GetMouseWheelDelta() { return mouseWheel; }

		static LuaPort* luaPort;

	private:
		static inline std::unordered_map<unsigned int, KeyState> keyboardStatus;
		static inline std::array<KeyState, 6> mouseStatus;

		static inline vector<unsigned int> keyJustPressed;
		static inline vector<unsigned int> keyJustReleased;
		static inline vector<uint8_t> mouseJustPressed;
		static inline vector<uint8_t> mouseJustReleased;

		static inline glm::vec2 mousePos;

		// using double to cater to lua: lua uses double-precision floating-point numbers
		static inline float mouseWheel; 
		static inline bool scrolledThisFrame = false;
	};
}

#endif
