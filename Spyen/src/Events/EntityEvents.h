#pragma once

#include <Events/Event.h>
#include <Scene/Entity.h>

namespace Spyen {
	class NodeEvent : public Event {
	public:
		inline Entity GetEntity() const { return m_Entity; }
	protected:
		NodeEvent(Entity& entity) : m_Entity(entity) {};
		virtual ~NodeEvent() = default;

		Entity& m_Entity;
	};

	class NodeHitEvent : public NodeEvent {
	public:
		NodeHitEvent(Entity& hitter, Entity& target) : NodeEvent(hitter), m_Target(target) {};
		inline Entity& GetTarget() const { return m_Target; }

		SP_SYNTHESIZE_EVENT_FUNC(EntityHit)
	private:
		Entity& m_Target;
	};
}