#include "Scene.h"

#include "Components.h"
#include "Core/Defines.h"
#include "Entity.h"
#include <Renderer/Renderer.h>

namespace Spyen
{

	std::unordered_map<std::string, Entity> m_Entities;

	Entity Scene::CreateEntity(const std::string& name)
	{
		SPY_CORE_ASSERT(!m_Entities.contains(name), "Entity {} already exists!", name.c_str());
		m_Entities.insert({ name, Entity(m_Registry.create(), this) });
		auto& entity = m_Entities.at(name);
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<RenderComponent>();

		return entity;
	}
	Entity Scene::GetEntityByName(const std::string& name) const
	{
		SPY_CORE_ASSERT(m_Entities.contains(name), "Entity {} does not exists!", name.c_str());
		return m_Entities.at(name);
	}
	void Scene::OnRender(Renderer* renderer) const
	{
		const auto& view = m_Registry.view<TransformComponent, RenderComponent>();

		renderer->BeginFrame();

		for (auto [entity, transform, render] : view.each())
		{
			if (render.Texture == nullptr)
			{
				renderer->DrawQuad(transform.GetTransformMatrix(), render.Color);
			}else
			{
				renderer->DrawQuad(transform.GetTransformMatrix(), render.Texture);
			}
			
		}

		renderer->EndFrame();

	}
}
