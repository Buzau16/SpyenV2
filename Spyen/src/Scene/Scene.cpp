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

    void Scene::AmbientLightPass(const Framebuffer& fb)
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

    void Scene::GeometryPass(const Framebuffer& fb, const SceneCamera& camera, Renderer* renderer, uint32_t width, uint32_t height)
    {
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

    void Scene::LightPass(const Framebuffer& fb, const SceneCamera& camera, Renderer* renderer, uint32_t width, uint32_t height)
    {
        auto lights = m_Registry.view<TransformComponent, LightComponent>();

    //    /*auto occluders = m_Registry.view<TransformComponent, LightOccluderComponent>();
    //    for (auto [entity, tc, loc] : occluders.each()) {
    //        switch (loc.Shape) {
    //        case LightOccluderComponent::OccluderShape::QUAD:
    //            Vec2 st = tc.Position - tc.Scale / 2;
    //            Vec2 nd = { st.x, st.y + tc.Scale.y };
    //            Vec2 rd = st + tc.Scale;
    //            Vec2 th = { st.x + tc.Scale.x, st.y };
    //            loc.Vertices.reserve(4);
    //            loc.Vertices.emplace_back(st);
    //            loc.Vertices.emplace_back(nd);
    //            loc.Vertices.emplace_back(rd);
    //            loc.Vertices.emplace_back(th);
    //        }
    //    }*/

        fb.Bind();
        RenderCommand::ClearColor({ 0.f, 0.f, 0.f }, 0.0f);
        RenderCommand::Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        glDisable(GL_DEPTH_TEST);
        renderer->BeginFrame(camera, width, height);
        for (auto [entity, tc, lc] : lights.each()) {
            renderer->DrawLight(Math::ToGLMVec2(tc.Position), Math::ToGLMVec3(lc.Color), lc.Radius, lc.Intensity);
        }
        renderer->EndFrame();

        glDisable(GL_BLEND);
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

    void Scene::OnRender(Renderer* renderer, uint32_t width, uint32_t height) noexcept
    {
        SceneCamera camera;
        // Get the camera if exists
        const auto cameras = m_Registry.view<CameraComponent>();
        for (auto [entity, cc] : cameras.each()) {
            if (cc.MainCamera) {
                camera = cc.Camera;
            }
        }

        Framebuffer ambient_light_buffer = Framebuffer(FramebufferSpecs{width, height, FramebufferAttachments::COLOR });
        Framebuffer geometry_buffer = Framebuffer(FramebufferSpecs{ width, height, FramebufferAttachments::COLOR });
        Framebuffer light_buffer = Framebuffer(FramebufferSpecs{ width, height, FramebufferAttachments::COLOR });

        AmbientLightPass(ambient_light_buffer);
        GeometryPass(geometry_buffer, camera, renderer, width, height);
        LightPass(light_buffer, camera, renderer, width, height);
        
        renderer->CompositeFinalImage(geometry_buffer, ambient_light_buffer, light_buffer);
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
