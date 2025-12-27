#pragma once
#include <cstdint>

namespace Spyen
{
	class SSBO
	{
	public:
		SSBO() = default;
		SSBO(const void* data, size_t size);
		~SSBO();

		void Bind(uint32_t slot = 0) const;
		void Unbind() const;
		void SetData(const void* data, size_t size, size_t offset = 0);
		size_t GetBufferSize() const { return m_BufferSize; }

	private:
		uint32_t m_RendererID;
		size_t m_BufferSize = 0;
	};
}


