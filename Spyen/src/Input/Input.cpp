#include "spypch.h"
#include "Input.h"
#include <Core/Director.h>
#include <GLFW/glfw3.h>

namespace Spyen {
	bool Input::IsKeyDown(KeyCode key)
	{
		auto window = Director::GetWindow();
		auto state = glfwGetKey(window, static_cast<int>(key));
		return state == GLFW_PRESS;
	}
	bool Input::IsKeyUp(KeyCode key)
	{
		auto window = Director::GetWindow();
		auto state = glfwGetKey(window, static_cast<int>(key));
		return state == GLFW_RELEASE;
	}
	bool Input::IsMouseButtonDown(MouseCode button)
	{
		auto window = Director::GetWindow();
		auto state = glfwGetMouseButton(window, static_cast<int>(button));
		return state == GLFW_PRESS;
	}
	bool Input::IsMouseButtonUp(MouseCode button)
	{
		auto window = Director::GetWindow();
		auto state = glfwGetMouseButton(window, static_cast<int>(button));
		return state == GLFW_RELEASE;
	}
	Vec2 Input::GetMousePosition()
	{
		auto window = Director::GetWindow();
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return {x,y};
	}
	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}
	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}
}