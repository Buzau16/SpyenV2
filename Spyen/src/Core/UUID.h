#pragma once

namespace Spyen {
	class UUID
	{
	public:
		UUID();
		///UUID()
		UUID(const UUID&) = default;
		UUID(const uint64_t uuid);


	private:
		uint64_t m_ID;
	};

}

