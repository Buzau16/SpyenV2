#pragma once
#include <entt/entt.hpp>
#include <string>
#include <unordered_map>
#include <Core/UUID.h>


namespace Spyen {
	class Entity;
	class Renderer;

	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		Entity& CreateEntity(const std::string& name = std::string());
		Entity& CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());

		void OnRender(Renderer* renderer, uint32_t width, uint32_t height) const noexcept;


	private:
		// refactor this to use uuids instead of strings for the key
		std::unordered_map<UUID, Entity> m_EntityMap;
		entt::registry m_Registry;
		// a Camera should be an entity or it can be a component of an entity
		friend class Entity;
	};

}

