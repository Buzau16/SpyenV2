#include "spypch.h"
#include "VertexBuffer.h"

#include <glad/glad.h>

namespace Spyen {
	VertexBuffer::VertexBuffer(const void* data, size_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);

		GLenum error = glGetError();
		if (!error == GL_NO_ERROR) {
			SPY_CORE_CRITICAL("Failed to create vertex buffer: {}", error);
		}
		SPY_CORE_ASSERT(error == GL_NO_ERROR, "Failed to create vertex buffer");
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}
	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void VertexBuffer::SetData(const void* data, size_t size)
	{
		Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
}