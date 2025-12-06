#pragma once

namespace Spyen {
	class UUID
	{
	public:
		UUID();
		///UUID()
		UUID(const UUID&) = delete;
		UUID(const uint64_t uuid);


	private:
		uint64_t m_ID;
	};

}

