#pragma once
#include <cstdint>
#include <filesystem>

namespace Spyen
{

	struct TextureSpecification
	{
		uint32_t Width = 0, Height = 0, BitDepth = 0;
		uint32_t InternalFormat, DataFormat;
	};

	class Texture
	{
	public:
		Texture(const std::filesystem::path& path);
		Texture(const TextureSpecification& specs);
		~Texture();

		uint64_t GetTextureHandle() const { return m_TextureHandle; }

		void SetData(const void* data, size_t size) const;

	private:
		TextureSpecification m_Specs;
		uint64_t m_TextureHandle;
		uint32_t m_RendererID;
	};
} 


