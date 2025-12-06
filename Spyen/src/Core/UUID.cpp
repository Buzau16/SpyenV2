#include "spypch.h"
#include "UUID.h"

//#include <random>
#include <Math/Common.h>

namespace Spyen {
	/*static std::random_device s_RandomDevice;
	static std::mt19937_64 s_Engine(s_RandomDevice());
	static std::uniform_int_distribution<uint64_t> s_UnformDist;*/

	UUID::UUID() : m_ID(Math::Random<uint64_t>())
	{
	}

	UUID::UUID(const uint64_t uuid) : m_ID(uuid)
	{
	}

}
