#pragma once
#include <Core/Defines.h>

namespace Spyen {

	enum class FramebufferAttachments : uint32_t{
		NONE = 0,
		COLOR = SP_BIT(1),
		STENCIL = SP_BIT(2),
		DEPTH = SP_BIT(3) // maybe unused
	};

	inline bool operator&(FramebufferAttachments a, FramebufferAttachments b) {
		return static_cast<uint32_t>(a) & static_cast<uint32_t>(b);
	}

	struct FramebufferSpecs {
		uint32_t Width, Height;
		FramebufferAttachments Attachments;
	};

	class Framebuffer
	{
	public:
		Framebuffer() = default;
		Framebuffer(const FramebufferSpecs& specs);

		Framebuffer(const Framebuffer&) = delete;
		Framebuffer& operator=(const Framebuffer&) = delete;

		Framebuffer(Framebuffer&& other) noexcept;
		Framebuffer& operator=(Framebuffer&& other) noexcept;

		~Framebuffer();

		void Bind() const;
		void Unbind() const;
		bool IsFramebufferComplete() const;

		uint32_t GetColorAttachment() const { return m_ColorAttachment; }
	private:
		void Cleanup();
		void GenerateColorAttachment();

		uint32_t m_RendererID;
		FramebufferSpecs m_Specs;
		uint32_t m_ColorAttachment = 0;
		uint32_t m_DepthAttachment = 0;
		uint32_t m_StencilAttachment = 0;
	};

}

