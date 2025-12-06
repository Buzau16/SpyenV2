#include "spypch.h"
#include "Scene.h"
#include <Renderer/Renderer.h>
#include <Events/NodeEvents.h>

namespace Spyen {
	void Scene::OnInit()
	{
		Camera.OnInit();
		for (auto& node : NodeGraph) {
			node->OnInit();
		}
	}
	void Scene::OnUpdate(Timestep dt)
	{
		Camera.OnUpdate(dt);
		for (auto& node : NodeGraph) {
			node->OnUpdate(dt);
		}

		NodeGraph.ProccesDeffered();
	}
	void Scene::OnRender(Renderer* renderer)
	{
		for (auto& node : NodeGraph) {
			node->OnRender(renderer);
		}
	}

	void Scene::OnEvent(Event& event)
	{
		for (auto& node : NodeGraph) {
			node->OnEvent(event);
		}
	}

	void Scene::AddNode(std::unique_ptr<Node> node)
	{
		NodeGraph.AddNode(std::move(node));
	}

	void Scene::RemoveNode(Node* node)
	{
		NodeGraph.RemoveNode(node);
	}

	Node* Scene::GetNode(const std::string_view name)
	{
		return NodeGraph.GetNode(name);
	}

	std::vector<Node*> Scene::GetNodesWithTag(const std::string_view tag)
	{
		return NodeGraph.GetNodesWithTag(tag);
	}

	Camera& Scene::GetCamera() noexcept
	{
		return Camera;
	}

	NodeGraph& Scene::GetNodeGraph() noexcept
	{
		return Scene::NodeGraph;
	}

	std::unique_ptr<Scene> Scene::Create()
	{
		return std::make_unique<Scene>();
	}
}
