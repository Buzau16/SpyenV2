#include "spypch.h"
#include "Entity.h"


namespace Spyen {
	Entity::Entity(entt::entity handle, Scene* scene) : m_EntityHandle(handle), m_Scene(scene) {}

	Entity::~Entity()
	{
		m_EntityHandle = entt::null;
		m_Scene = nullptr;
	}
	void Entity::SetParent(const Entity& entity)
	{
		GetComponent<ParentComponent>().Parent = entity.m_EntityHandle;
	}
}
