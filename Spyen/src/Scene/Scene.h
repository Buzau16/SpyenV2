#pragma once

#include <entt/entt.hpp>

namespace Spyen
{
	class Renderer;
	class Entity;

	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		Entity CreateEntity(const std::string& name);
		[[nodiscard]] Entity GetEntityByName(const std::string& name) const;

		void OnRender(Renderer* renderer) const;
		void OnUpdate() {}; // to be implemented

		template<typename... TComponents>
		auto GetEntitiesWith()
		{
			return m_Registry.view<TComponents...>();
		}

	private:
		entt::registry m_Registry;
		//std::unordered_map<std::string, Entity> m_Entities;

		friend class Entity;
	};
}


