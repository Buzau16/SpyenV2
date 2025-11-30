#pragma once
#include <string>
#include <unordered_map>
#include "Audio/Sound.h"

#include "Renderer/Texture.h"

namespace Spyen {
	class AssetManager
	{
	public:
		//AssetManager() = default;
		AssetManager();
		~AssetManager() = default;

		Texture* LoadTexture(const std::string& name, const std::filesystem::path& path);
		Texture* GetTexture(const char* name);
		Texture* LoadTextureP(const std::filesystem::path& path);
		void RemoveTexture(const std::string& name);

		Sound* LoadSound(const std::string& name, const std::filesystem::path& path);
		Sound* GetSound(const char* name);
		void RemoveSound(const std::string& name);

	private:
		std::unordered_map<std::string, std::unique_ptr<Texture>> m_TextureMap;
		std::unordered_map<std::string, std::unique_ptr<Sound>> m_SoundMap;
	};

}

