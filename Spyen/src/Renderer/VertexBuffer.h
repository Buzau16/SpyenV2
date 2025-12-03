#pragma once
#include "Renderer/BufferLayout.h"
#include <cstdint>

namespace Spyen {
	class VertexBuffer
	{
	public:
		VertexBuffer(const void* data, size_t size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
		void SetData(const void* data, size_t size);
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; };
		const BufferLayout& GetLayout() const { return m_Layout; };
		uint32_t& GetRendererID() { return m_RendererID; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

}