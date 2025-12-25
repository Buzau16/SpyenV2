#pragma once

namespace Spyen {
	class Framebuffer
	{
	public:
		Framebuffer();
		~Framebuffer();

		void Bind();
		void Unbind();
		bool IsFramebufferComplete() const;
	private:
		uint32_t m_RendererID;

	};

}

