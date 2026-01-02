#include "spypch.h"
#include "UniformBuffer.h"

#include <glad/glad.h>


namespace Spyen {
	UniformBuffer::UniformBuffer(size_t size, uint32_t binding)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
	}

	UniformBuffer::~UniformBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void UniformBuffer::Bind(uint32_t binding)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
	}

	void UniformBuffer::Unbind(uint32_t binding)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void UniformBuffer::SetData(const void* data, size_t size, uint32_t offset)
	{
		glNamedBufferSubData(m_RendererID, offset, size, data);
	}
}
