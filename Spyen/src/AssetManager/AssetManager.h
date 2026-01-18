#pragma once
#include <string>
#include <unordered_map>
#include "Audio/Sound.h"
#include "Renderer/Texture.h"

namespace Spyen {
	class AssetManager
	{
	public:
		static Texture* LoadTexture(const std::string& name, const std::filesystem::path& path);
		static Texture* GetTexture(const char* name);
		static Texture* LoadTextureP(const std::filesystem::path& path);
		static void RemoveTexture(const std::string& name);

		static Sound* LoadSound(const std::string& name, const std::filesystem::path& path);
		static Sound* GetSound(const char* name);
		static void RemoveSound(const std::string& name);

	private:
		static std::unordered_map<std::string, std::unique_ptr<Texture>> m_TextureMap;
		static std::unordered_map<std::string, std::unique_ptr<Sound>> m_SoundMap;
	};

}

