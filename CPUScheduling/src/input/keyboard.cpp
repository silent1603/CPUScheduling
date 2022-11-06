#include "keyboard.h"
#include "SDL2/SDL_keyboard.h"

namespace Input {
		std::array<bool, Keyboard::KeyCount> Keyboard::keys;
		std::array<bool, Keyboard::KeyCount> Keyboard::keysLast;

		void Keyboard::Initialize()
		{
			std::fill(keys.begin(), keys.end(), false);
			std::fill(keysLast.begin(), keysLast.end(), false);
		}

		void Keyboard::Update()
		{
			keysLast = keys;
			const Uint8* state = SDL_GetKeyboardState(nullptr);
			for (int i = INPUT_KEY_FIRST; i < KeyCount; i++)
			{
				keys[i] = state[i];
			}
		}

		bool Keyboard::Key(int key)
		{
			if (key >= INPUT_KEY_FIRST && key < KeyCount)
			{
				return keys[key];
			}
			return false;
		}

		bool Keyboard::KeyDown(int key)
		{
			if (key >= INPUT_KEY_FIRST && key < KeyCount)
			{
				return keys[key] && !keysLast[key];
			}
			return false;
		}

		bool Keyboard::KeyUp(int key)
		{
			if (key >= INPUT_KEY_FIRST && key < KeyCount)
			{
				return !keys[key] && keysLast[key];
			}
			return false;
		}
}
