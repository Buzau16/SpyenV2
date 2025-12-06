#pragma once

#include <Events/Event.h>
#include <Scene/Node.h>

namespace Spyen {
	class NodeEvent : public Event {
	public:
		inline Node* GetNode() const { return m_Node; }
	protected:
		NodeEvent(Node* node) :m_Node(node) {};
		virtual ~NodeEvent() = default;

		Node* m_Node;
	};

	class NodeHitEvent : public NodeEvent {
	public:
		NodeHitEvent(Node* hitter, Node* target) : NodeEvent(hitter), m_Target(target) {};
		inline Node* GetTarget() const { return m_Target; }

		SP_SYNTHESIZE_EVENT_FUNC(NodeHit)
	private:
		Node* m_Target = nullptr;
	};
}