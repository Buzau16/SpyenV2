#pragma once
#include "NodeGraph.h"
#include "Camera.h"
#include <Time/TimeStep.h>
#include <memory>
#include "Node.h"

#define CREATE_MOVE(type) \
	std::move(std::make_unique<type>())


namespace Spyen {
	class Renderer;

	class Scene{
	public:
		Scene() = default;
		~Scene() = default;

		void OnInit();
		void OnUpdate(Timestep dt);
		void OnRender(Renderer* renderer);

		void AddNode(std::unique_ptr<Node> node);

		Camera& GetCamera() noexcept;
		NodeGraph& GetNodeGraph() noexcept;

		static std::unique_ptr<Scene> Create();

	protected:
		Camera Camera;
		NodeGraph NodeGraph;
	};
}


