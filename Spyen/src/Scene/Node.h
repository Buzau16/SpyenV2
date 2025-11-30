#pragma once
#include "Components.h"
#include <Time/TimeStep.h>
#include <Core/Defines.h>

namespace Spyen {
	class Renderer;

	class Node
	{
	public:
		Node() = default;
		virtual ~Node() = default;

		virtual void OnInit() {};
		virtual void OnUpdate(Timestep dt) {};
		virtual void OnRender(Renderer* renderer) {};

		SP_SYNTHESIZE(glm::vec2, Position, Position);
		SP_SYNTHESIZE(glm::vec2, Scale, Scale);
		SP_SYNTHESIZE_NR(float, Rotation, Rotation);

		void AddChild(std::unique_ptr<Node> child);

		static std::unique_ptr<Node> Create();
	private:
		std::vector<std::unique_ptr<Node>> m_Children;
	protected:
		glm::vec2 Position{ 0,0 };
		glm::vec2 Scale{ 100.f, 100.f };
		float Rotation = 0.f;
	private:
		Node* m_Parent = nullptr;	
	};


}
