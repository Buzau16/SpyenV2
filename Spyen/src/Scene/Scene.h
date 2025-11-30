#pragma once
#if 0

namespace Spyen
{
	class Renderer;
	class Entity;

	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		Entity CreateEntity(const std::string& name);
		[[nodiscard]] Entity GetEntityByName(const std::string& name) const;


		void OnRender(Renderer* renderer) const;
		void OnUpdate() {}; // to be implemented

		template<typename... TComponents>
		auto GetEntitiesWith()
		{
			return m_Registry.view<TComponents...>();
		}

		inline void MakeSceneCamera(const glm::vec2& position, const glm::ivec2& bounds, float zoom = 1.0f)
		{
			m_MainCamera = std::make_unique<Camera>(position, bounds, zoom);
		}

	private:
		entt::registry m_Registry;
		//std::unordered_map<std::string, Entity> m_Entities;
		std::unique_ptr<Camera> m_MainCamera = nullptr;
		friend class Entity;
		friend class Engine;
	};
}

#else

#include <Scene/Node.h>

namespace Spyen {

	//TODO: find a way to make the camera a node and make a camera controller class

	class Scene{
	public:
		Scene() = default;
		virtual ~Scene() = default;

		virtual void OnInit() {};
		virtual void OnUpdate(Timestep dt);
		virtual void OnRender(Renderer* renderer);

		void AddNode(std::unique_ptr<Node> node);

		static std::unique_ptr<Scene> Create();

	private:
		std::vector<std::unique_ptr<Node>> m_Nodes;
	};
}

#endif


