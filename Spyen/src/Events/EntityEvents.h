#pragma once

#include <Events/Event.h>
#include <Scene/Entity.h>

namespace Spyen {
	class EntityEvent : public Event {
	public:
		inline Entity GetEntity() const { return m_Entity; }
	protected:
		EntityEvent(Entity& entity) : m_Entity(entity) {};
		virtual ~EntityEvent() = default;

		Entity& m_Entity;
	};

	class EntityHitEvent : public EntityEvent {
	public:
		EntityHitEvent(Entity& hitter, Entity& target) : EntityEvent(hitter), m_Target(target) {};
		inline Entity& GetTarget() const { return m_Target; }

		SP_SYNTHESIZE_EVENT_FUNC(EntityHit)
	private:
		Entity& m_Target;
	};
}