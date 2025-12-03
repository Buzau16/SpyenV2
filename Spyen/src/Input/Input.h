#pragma once
#include <Math/Math.h>
#include <Input/KeyCodes.h>
#include <Input/MouseCodes.h>

namespace Spyen {
	class Input
	{
	public:
		static bool IsKeyDown(KeyCode key);
		static bool IsKeyUp(KeyCode key);
		//static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonDown(MouseCode button);
		static bool IsMouseButtonUp(MouseCode button);
		//static bool IsMouseButtonPressed(MouseCode button);

		static Vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

	};

}

