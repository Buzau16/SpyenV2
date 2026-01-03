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
    struct Renderable {
        const TransformComponent* Transform;
        const SpriteRenderComponent* Sprite;
    };

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
        entity.AddComponent<ParentComponent>();

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

    void Scene::OnUpdate(Timestep ts)
    {
        const auto& view = m_Registry.view<ScriptComponent>();
        for (const auto& [e, sc] : view.each()) {
            Entity entity = { e, this };
            ScriptEngine::InvokeOnUpdate(entity, ts);
        }

        auto cldrn = m_Registry.view<TransformComponent, ParentComponent>();

        for (auto [entity, gchildTransform, pc] : cldrn.each()) {
            if (pc.Parent == entt::null) {
                continue;
            }
            else {
                auto& parentTransform = m_Registry.get<TransformComponent>(pc.Parent);
                gchildTransform.Position = parentTransform.Position + pc.PositionOffset;
            }

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

        SkyComponent sky;
        const auto skys = m_Registry.view<SkyComponent>();
        for (auto [entity, sc] : skys.each()) {
            sky.Color = sc.Color;
            sky.LightIntensity = sc.LightIntensity;
        }

        const auto entities = m_Registry.view<TransformComponent, SpriteRenderComponent>();
        auto lights = m_Registry.view<TransformComponent, LightComponent>();

        std::vector<Renderable> renderables;
        renderables.reserve(entities.size_hint());

        for (auto [entity, tc, src] : entities.each()) {
            renderables.push_back({ &tc, &src });
        }

        std::sort(renderables.begin(), renderables.end(), [](const Renderable& a, const Renderable& b) {
            if (a.Transform->ZIndex != b.Transform->ZIndex) {
                return a.Transform->ZIndex < b.Transform->ZIndex;
            }
            else {
                return a.Transform->Position.y < b.Transform->Position.y;
            }
            });

        // Geometry pass
        renderer->BeginFrame(FramebufferTarget::GEOMETRY, camera, width, height);
        RenderCommand::ClearColor({ 1.f, 1.f, 1.f });
        RenderCommand::Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto& renderable : renderables) {
            if (renderable.Sprite->Texture == nullptr) {
                renderer->DrawQuad(Math::ToGLMVec2(renderable.Transform->Position), Math::ToGLMVec2(renderable.Transform->Scale), renderable.Transform->Rotation, renderable.Sprite->Color);
            }
            else {
                renderer->DrawQuad(Math::ToGLMVec2(renderable.Transform->Position), Math::ToGLMVec2(renderable.Transform->Scale), renderable.Transform->Rotation, renderable.Sprite->Texture);
            }
        }

        /*for (auto [entity, tc, src] : entities.each()) {
            if (src.Texture == nullptr) {
                renderer->DrawQuad(Math::ToGLMVec2(tc.Position), Math::ToGLMVec2(tc.Scale), tc.Rotation, src.Color);
            }
            else {
                renderer->DrawQuad(Math::ToGLMVec2(tc.Position), Math::ToGLMVec2(tc.Scale), tc.Rotation, src.Texture);
                SPY_CORE_INFO("Rendering Quad: x: {}, y: {}", tc.Position.x, tc.Position.y);
            }
        }*/

        renderer->EndFrame();

        //// Light Pass
        renderer->BeginFrame(FramebufferTarget::LIGHT, camera, width, height);
        RenderCommand::ClearColor(sky.Color * sky.LightIntensity, 1.0f);
        RenderCommand::Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        glDisable(GL_DEPTH_TEST);

        for (auto [entity, tc, lc] : lights.each()) {
            renderer->DrawLight(Math::ToGLMVec2(tc.Position), Math::ToGLMVec3(lc.Color), lc.Radius, lc.Intensity);
        }
        renderer->EndFrame();
        glDisable(GL_BLEND);



        renderer->CompositeFinalImage();
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
