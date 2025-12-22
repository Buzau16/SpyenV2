#pragma once
#include <entt/entt.hpp>
#include <Core/Log.h>
#include <Scene/Scene.h>
#include "Components.h"
namespace Spyen {
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		~Entity();

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			SPY_CORE_ASSERT(!HasComponent<T>(), "Entity already has a this component");
			T& comp =  m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			return comp;
		}

		template<typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args) {
			T& comp = m_Scene->m_Registry.emplace_or_replace<T>(m_EntityHandle, std::forward<Args>(args)...);
			return comp;
		}

		template<typename T>
		T& GetComponent(){
			SPY_CORE_ASSERT(HasComponent<T>(), "Entity does not have this component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent() {
			return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent() const {
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}
		

		UUID GetUUID() { return GetComponent<IDComponent>().ID; }
		const std::string& GetTag() { return GetComponent<TagComponent>().Tag; }
		
	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;

		friend class Scene;
		friend class Script;
	};

}

