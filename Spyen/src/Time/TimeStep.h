#pragma once
#include "Core/Core.h"


namespace Spyen {
	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{
		}
		Timestep(const Timestep& other) = default;
		Timestep(Timestep&& other) noexcept : m_Time(other.m_Time) { other.m_Time = 0; }

		operator float() const { return m_Time; }
		Timestep& operator=(float time) { m_Time = time; return *this; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};
}