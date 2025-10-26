#pragma once

#include <entt/entt.hpp>
#include "Core/locked_ptr.h"
#include "Renderer/Renderer.h"

namespace Spyen
{
	class Entity;

	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		locked_ptr<Entity> CreateEntity(const std::string& name);
		[[nodiscard]] locked_ptr<Entity> GetEntityByName(const std::string& name) const;

		void OnRender(Renderer* renderer) const;
		void OnUpdate() {}; // to be implemented

	private:
		entt::registry m_Registry;
		std::unordered_map<std::string, std::shared_ptr<Entity>> m_Entities;

		friend class Entity;
	};
}


