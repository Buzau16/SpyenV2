#pragma once
#include <cstdint>

namespace Spyen {
	class UniformBuffer
	{
	public:
		UniformBuffer() = default;
		UniformBuffer(size_t size, uint32_t binding);
		~UniformBuffer();

		void SetData(const void* data, size_t size, uint32_t offset = 0);
	private:
		uint32_t m_RendererID;
	};

}

