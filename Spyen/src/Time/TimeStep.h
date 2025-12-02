#pragma once



namespace Spyen {
	class Timestep
	{
	public:
		Timestep(double time = 0.0f)
			: m_Time(time)
		{
		}
		Timestep(const Timestep& other) = default;
		Timestep(Timestep&& other) noexcept : m_Time(other.m_Time) { other.m_Time = 0; }

		operator double() const { return m_Time; }
		Timestep& operator=(float time) { m_Time = time; return *this; }

		double GetSeconds() const { return m_Time; }
		double GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		double m_Time;
	};
}