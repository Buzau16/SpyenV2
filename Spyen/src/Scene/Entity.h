#pragma once
#include <entt/entity/entity.hpp>
#include "Scene.h"
#include "Core/Log.h"


namespace Spyen {
	class Entity
	{
	public:
		Entity(entt::entity handle, Scene* parent_scene) : m_EntityHandle(handle), m_ParentScene(parent_scene) {};
		~Entity() = default;

		template<typename TComponent, typename... Args>
		void AddComponent(Args&&... args)
		{
			if (m_ParentScene->m_Registry.any_of<TComponent>(m_EntityHandle))
			{
				SPY_CORE_ERROR("Entity already has this component!");
				return;
			}

			m_ParentScene->m_Registry.emplace<TComponent>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename TComponent>
		void RemoveComponent() const {
			m_ParentScene->m_Registry.remove<TComponent>(m_EntityHandle);
		}

		template<typename TComponent>
		[[nodiscard]] bool HasComponent() const {
			return m_ParentScene->m_Registry.all_of<TComponent>(m_EntityHandle);
		}

		template<typename TComponent>
		TComponent& GetComponent() {
			if (!HasComponent<TComponent>()) {
				SPY_CORE_ERROR("Entity does not have this component!");
				throw std::runtime_error("Component does not exist");
			}
			return m_ParentScene->m_Registry.get<TComponent>(m_EntityHandle);
		}

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_ParentScene == other.m_ParentScene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

	private:
		entt::entity m_EntityHandle;
		Scene* m_ParentScene = nullptr;
	};

}
