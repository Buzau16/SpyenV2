#pragma once
#include "NodeGraph.h"
#include "Camera.h"
#include <Time/TimeStep.h>
#include <memory>
#include "Node.h"
#include <Events/Event.h>


namespace Spyen {
	class Renderer;

	class Scene{
	public:
		Scene() = default;
		~Scene() = default;

		void OnInit();
		void OnUpdate(Timestep dt);
		void OnRender(Renderer* renderer);
		void OnEvent(Event& event);

		void AddNode(std::unique_ptr<Node> node);
		void RemoveNode(Node* node);
		Node* GetNode(const std::string_view name);
		std::vector<Node*> GetNodesWithTag(const std::string_view tag);
		std::vector<RigidBody> GetRigidBodies();
		std::vector<Node*> GetNodesWithRigidBodies();
		std::vector<Node*> GetNodes();

		SP_SYNTHESIZE(std::string, Name, Name);

		Camera& GetCamera() noexcept;
		NodeGraph& GetNodeGraph() noexcept;

		static std::unique_ptr<Scene> Create();

	protected:
		std::string Name;
		Camera Camera;
		NodeGraph NodeGraph;
	};
}


