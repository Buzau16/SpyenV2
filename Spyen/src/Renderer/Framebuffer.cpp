#include "spypch.h"
#include "FrameBuffer.h"

#include "glad/glad.h"

namespace Spyen {
	void Framebuffer::Cleanup()
	{
		if (m_ColorAttachment) glDeleteTextures(1, &m_ColorAttachment);
		if (m_DepthAttachment) glDeleteTextures(1, &m_DepthAttachment);
		if (m_RendererID) glDeleteFramebuffers(1, &m_RendererID);

		m_RendererID = 0;
		m_ColorAttachment = 0;
		m_DepthAttachment = 0;
	}

	Framebuffer::Framebuffer(const FramebufferSpecs& specs) : m_Specs(specs)
	{
		glCreateFramebuffers(1, &m_RendererID);
		glViewport(0, 0, m_Specs.Width, m_Specs.Height);
		Bind();
		if (m_Specs.Attachments & FramebufferAttachments::COLOR) {
			GenerateColorAttachment();
		}
		Unbind();
	}
	Framebuffer::Framebuffer(Framebuffer&& other) noexcept
		: m_RendererID(other.m_RendererID),
		m_ColorAttachment(other.m_ColorAttachment),
		m_DepthAttachment(other.m_DepthAttachment),
		m_Specs(std::move(other.m_Specs))
	{
		other.m_RendererID = 0;
		other.m_ColorAttachment = 0;
		other.m_DepthAttachment = 0;
	}
	Framebuffer& Framebuffer::operator=(Framebuffer&& other) noexcept
	{
		if (this != &other)
		{
			Cleanup();

			m_RendererID = other.m_RendererID;
			m_ColorAttachment = other.m_ColorAttachment;
			m_DepthAttachment = other.m_DepthAttachment;
			m_Specs = std::move(other.m_Specs);

			other.m_RendererID = 0;
			other.m_ColorAttachment = 0;
			other.m_DepthAttachment = 0;
		}
		return *this;
	}
	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		if (m_ColorAttachment) {
			glDeleteTextures(1, &m_ColorAttachment);
		}
	}
	void Framebuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	}
	void Framebuffer::GenerateColorAttachment()
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);

		glTextureStorage2D(m_ColorAttachment, 1, GL_RGBA8, m_Specs.Width, m_Specs.Height);

		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glNamedFramebufferTexture(m_RendererID, GL_COLOR_ATTACHMENT0, m_ColorAttachment, 0);
	}
	void Framebuffer::Unbind() const
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