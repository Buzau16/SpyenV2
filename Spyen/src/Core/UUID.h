#pragma once

namespace Spyen {
	class UUID
	{
	public:
		UUID();
		///UUID()
		UUID(const UUID&) = default;
		UUID(const uint64_t uuid);

		operator uint64_t() const { return m_ID; };

	private:
		uint64_t m_ID;
	};

}

namespace std {
	template <typename T> struct hash;

	template<>
	struct hash<Spyen::UUID>
	{
		std::size_t operator()(const Spyen::UUID& uuid) const
		{
			return (uint64_t)uuid;
		}
	};

}

