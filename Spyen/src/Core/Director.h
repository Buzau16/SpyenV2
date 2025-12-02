#pragma once
#include <memory>
#include "Core.h"
#include <string>
#include <Math/Math.h>

namespace Spyen {
	// A static class for accesing variables across the engine/applications
	class Director
	{
	public:
		Director(const Director& other) = delete;
		~Director() = default;

		static IVec2 GetWindowDimensions();
		static Scene* GetActiveScene();
		static void SetActiveScene(const std::string& name);
		static void AddScene(const std::string& name, std::unique_ptr<Scene> scene);
		static void Transition(const std::string& name);
	private:
		static Engine* s_Instance;
		friend class Engine;
	};

}