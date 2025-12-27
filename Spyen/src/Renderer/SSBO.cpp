#include "spypch.h"
#include "SSBO.h"

#include <glad/glad.h>


namespace Spyen
{
	SSBO::SSBO(const void* data, size_t size) : m_BufferSize(size)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_RendererID);
		glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_COPY);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	SSBO::~SSBO()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void SSBO::Bind(uint32_t slot) const
	{
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, slot, m_RendererID);
	}

	void SSBO::Unbind() const
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	void SSBO::SetData(const void* data, size_t size, size_t offset)
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_RendererID);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
	}
}
