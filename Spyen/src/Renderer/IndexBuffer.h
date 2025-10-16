#pragma once
#include <stdint.h>

namespace Spyen {
	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t* indices, uint32_t count);
		~IndexBuffer();
		void Bind() const;
		void Unbind() const;
		uint32_t GetCount() const { return m_Count; }
		uint32_t& GetRendererID() { return m_RendererID; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}