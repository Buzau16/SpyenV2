#include "spypch.h"
#include "Texture.h"
#include <stb_image/stb_image.h>

#include "Core/Defines.h"
#include "Core/Log.h"

#include <glad/glad.h>

namespace Spyen
{
	Texture::Texture(const std::filesystem::path& path)
	{
		unsigned char* data = stbi_load(path.string().c_str(), reinterpret_cast<int*>(&m_Specs.Width), reinterpret_cast<int*>(&m_Specs.Height), reinterpret_cast<int*>(&m_Specs.BitDepth), 0);
		SPY_CORE_ASSERT(data, "Failed to load texture image!");

		m_Specs.InternalFormat = m_Specs.BitDepth == 4 ? GL_RGBA8 : GL_RGB8;
		m_Specs.DataFormat = m_Specs.BitDepth == 4 ? GL_RGBA : GL_RGB;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_Specs.InternalFormat, m_Specs.Width, m_Specs.Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Specs.Width, m_Specs.Height, m_Specs.DataFormat, GL_UNSIGNED_BYTE, data);

		m_TextureHandle = glGetTextureHandleARB(m_RendererID);
		glMakeTextureHandleResidentARB(m_TextureHandle);

		stbi_image_free(data);

	}
	Texture::Texture(const TextureSpecification& specs)
	{
		m_Specs = specs;
		m_Specs.InternalFormat = (m_Specs.BitDepth == 4) ? GL_RGB8 : GL_RGBA8;
		m_Specs.DataFormat = (m_Specs.BitDepth == 4) ? GL_RGB : GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_Specs.InternalFormat, m_Specs.Width, m_Specs.Height);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		m_TextureHandle = glGetTextureHandleARB(m_RendererID);
		glMakeTextureHandleResidentARB(m_TextureHandle);
	}

	Texture::~Texture()
	{
		if (m_RendererID != 0) {
			glMakeTextureHandleNonResidentARB(m_TextureHandle);
			glDeleteTextures(1, &m_RendererID);
		}
	}

	void Texture::SetData(const void* data, size_t size) const
	{
		glMakeTextureHandleNonResidentARB(m_TextureHandle);
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Specs.Width, m_Specs.Height, m_Specs.DataFormat, GL_UNSIGNED_BYTE, data);
		glMakeTextureHandleResidentARB(m_TextureHandle);
	}
}

