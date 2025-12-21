#include "spypch.h"
#include "Scene.h"

#include <Scene/Entity.h>
#include <Scene/Components.h>
#include <Renderer/Renderer.h>
#include <Scripting/ScriptEngine.h>
#include <Scripting/Script.h>

namespace Spyen {
    Entity Scene::CreateEntity(const std::string& name)
    {
        return CreateEntityWithUUID(UUID(), name);
    }

    Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& name)
    {
        Entity entity = { m_Registry.create(), this };
        entity.AddComponent<IDComponent>(uuid);
        entity.AddComponent<TransformComponent>();
        entity.AddComponent<TagComponent>().Tag = name.empty() ? "Entity" : name;

        m_EntityMap[uuid] = entity.m_EntityHandle;
        return entity;
    }

    Entity Scene::FindEntityByName(const std::string& name)
    {
        auto view = m_Registry.view<TagComponent>();
        for (const auto& [entity, tc] : view.each()) {
            if (tc.Tag == name)
                return Entity{ entity, this };
        }

        return {};
    }

    void Scene::OnInit()
    {
        const auto& view = m_Registry.view<ScriptComponent>();
        for (const auto& [e, sc] : view.each()) {
            Entity entity = { e, this };
            sc.ScriptInstance->m_Parent = entity;
            ScriptEngine::InvokeOnCreate(entity);
        }
    }

    void Scene::OnUpdate(Timestep ts)
    {
        const auto& view = m_Registry.view<ScriptComponent>();
        for (const auto& [e, sc] : view.each()) {
            Entity entity = { e, this };
            ScriptEngine::InvokeOnUpdate(entity, ts);
        }
    }

    void Scene::OnRender(Renderer* renderer, uint32_t width, uint32_t height) const noexcept
    {
        SceneCamera camera;
        // Get the camera if exists
        const auto cameras = m_Registry.view<CameraComponent>();
        for (auto [entity, cc] : cameras.each()) {
            if (cc.MainCamera) {
                camera = cc.Camera;
            }
        }

        // Drawing quads
        const auto entities = m_Registry.view<TransformComponent, SpriteRenderComponent>();

        renderer->BeginFrame(camera, width, height);
        for (auto [entity, tc, src] : entities.each()) {
            if (src.Texture == nullptr) {
                renderer->DrawQuad(Math::ToGLMVec2(tc.Position), Math::ToGLMVec2(tc.Scale), tc.Rotation, src.Color);
            }
            else {
                renderer->DrawQuad(Math::ToGLMVec2(tc.Position), Math::ToGLMVec2(tc.Scale), tc.Rotation, src.Texture);
            }
        }
        renderer->EndFrame();
    }

    void Scene::OnRemove()
    {
    }

    std::unique_ptr<Scene> Scene::Create()
    {
        auto default_scene = std::make_unique<Scene>();
        default_scene->CreateEntity("Camera").AddComponent<CameraComponent>();
        return default_scene;
    }

}
