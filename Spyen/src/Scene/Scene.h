#pragma once
#include <entt/entt.hpp>
#include <string>
#include <unordered_map>
#include <Core/UUID.h>
#include <Time/TimeStep.h>


namespace Spyen {
	class Entity;
	class Renderer;

	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
		Entity FindEntityByName(const std::string& name);


		template<typename... T>
		auto GetEntitiesWith() {
			return m_Registry.view<T...>();
		}

		void OnInit();
		void OnUpdate(Timestep ts);
		void OnRender(Renderer* renderer, uint32_t width, uint32_t height) const noexcept;
		void OnRemove();

		static std::unique_ptr<Scene> Create();

	private:
		std::unordered_map<UUID, entt::entity> m_EntityMap;
		entt::registry m_Registry;
		// a Camera should be an entity or it can be a component of an entity
		friend class Entity;
	};

}

