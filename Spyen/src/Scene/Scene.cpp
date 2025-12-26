#include "spypch.h"
#include "Scene.h"

#include <Scene/Entity.h>
#include <Scene/Components.h>
#include <Renderer/Renderer.h>
#include <Scripting/ScriptEngine.h>
#include <Scripting/Script.h>
#include <Events/Event.h>
#include <Renderer/Framebuffer.h>
#include <Renderer/RenderCommand.h>
#include <glad/glad.h>

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

    void Scene::DestroyEntity(Entity& entity)
    {
        m_DestroyQueue.push_back(entity.m_EntityHandle);
    }

    void Scene::OnAttach()
    {
        const auto& view = m_Registry.view<ScriptComponent>();
        for (const auto& [e, sc] : view.each()) {
            Entity entity = { e, this };
            ScriptEngine::InitializeScript(entity);
            ScriptEngine::InvokeOnCreate(entity);
        }
    }

    void Scene::FlushDestroyQueue()
    {
        // possible memory leak
        for (auto e : m_DestroyQueue) {
            if (m_Registry.valid(e))
                m_Registry.destroy(e);
        }
        m_DestroyQueue.clear();
    }

    void Scene::AmbientLightPass(const Framebuffer& fb) const
    {
        Vec3 sky_color = { 0.f, 0.f, 0.f };
        float intensity = 0.f;
        const auto sky = m_Registry.view<SkyComponent>();
        for (auto [entity, sc] : sky.each()) {
            sky_color = sc.Color;
            intensity = sc.LightIntensity;
        }
        
        fb.Bind();
        RenderCommand::ClearColor(sky_color - (1.f - intensity));
        RenderCommand::Clear(GL_COLOR_BUFFER_BIT);
        fb.Unbind();
    }

    void Scene::GeometryPass(const Framebuffer& fb, Renderer* renderer, uint32_t width, uint32_t height) const
    {
        SceneCamera camera;
        // Get the camera if exists
        const auto cameras = m_Registry.view<CameraComponent>();
        for (auto [entity, cc] : cameras.each()) {
            if (cc.MainCamera) {
                camera = cc.Camera;
            }
        }

        const auto entities = m_Registry.view<TransformComponent, SpriteRenderComponent>();

        fb.Bind();
        RenderCommand::ClearColor({ 1.f, 1.f, 1.f });
        RenderCommand::Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
        fb.Unbind();
    }

    void Scene::OnUpdate(Timestep ts)
    {
        const auto& view = m_Registry.view<ScriptComponent>();
        for (const auto& [e, sc] : view.each()) {
            Entity entity = { e, this };
            ScriptEngine::InvokeOnUpdate(entity, ts);
        }

        FlushDestroyQueue();
    }

    void Scene::OnRender(Renderer* renderer, uint32_t width, uint32_t height) const noexcept
    {
        Framebuffer ambient_light_buffer = Framebuffer(FramebufferSpecs{width, height, FramebufferAttachments::COLOR });
        AmbientLightPass(ambient_light_buffer);

        Framebuffer geometry_buffer = Framebuffer(FramebufferSpecs{ width, height, FramebufferAttachments::COLOR });
        GeometryPass(geometry_buffer, renderer, width, height);
        
        renderer->CompositeFinalImage(geometry_buffer, ambient_light_buffer);
    }

    void Scene::OnEvent(Event& event)
    {
        const auto& view = m_Registry.view<ScriptComponent>();
        for (const auto& [entity, sc] : view.each()) {
            Entity e = { entity, this };
            ScriptEngine::InvokeOnEvent(e, event);
        }
    }

    void Scene::OnDetach()
    {
        const auto& view = m_Registry.view<ScriptComponent>();
        for (const auto& [e, sc] : view.each()) {
            Entity entity = { e, this };
            ScriptEngine::CleanupScript(entity);
        }
    }

    std::unique_ptr<Scene> Scene::Create()
    {
        auto default_scene = std::make_unique<Scene>();
        default_scene->CreateEntity("Camera").AddComponent<CameraComponent>();
        return default_scene;
    }

}
