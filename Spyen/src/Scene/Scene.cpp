#include "Scene.h"

#include "Components.h"
#include "Core/Defines.h"
#include "Entity.h"

namespace Spyen
{
	locked_ptr<Entity> Scene::CreateEntity(const std::string& name)
	{
		SPY_CORE_ASSERT(!m_Entities.contains(name), "Entity {} already exists!", name.c_str());
		m_Entities.insert({ name, std::make_shared<Entity>(m_Registry.create(), this) });
		auto& entity = m_Entities.at(name);

		return locked_ptr<Entity>(entity);
	}
	locked_ptr<Entity> Scene::GetEntityByName(const std::string& name) const
	{
		SPY_CORE_ASSERT(m_Entities.contains(name), "Entity {} does not exists!", name.c_str());
		return locked_ptr<Entity>(m_Entities.at(name));
	}
	void Scene::OnRender(Renderer* renderer) const
	{
		const auto& view = m_Registry.view<Components::Transform, Components::Render>();

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
