#include "spypch.h"
#include "FrameBuffer.h"

#include "glad/glad.h"

namespace Spyen {
	Framebuffer::Framebuffer()
	{
		glGenFramebuffers(1, &m_RendererID);
	}
	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
	}
	void Framebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	}
	void Framebuffer::Unbind()
	{
		if (!IsFramebufferComplete()) {
			return;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	bool Framebuffer::IsFramebufferComplete() const
	{
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
			return true;
		else return false;
	}
}