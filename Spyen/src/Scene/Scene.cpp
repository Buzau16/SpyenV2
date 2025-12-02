#include "spypch.h"
#include "Scene.h"
#include <Renderer/Renderer.h>

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
	}
	void Scene::OnRender(Renderer* renderer)
	{
		for (auto& node : NodeGraph) {
			node->OnRender(renderer);
		}
	}

	void Scene::AddNode(std::unique_ptr<Node> node)
	{
		NodeGraph.AddNode(std::move(node));
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
