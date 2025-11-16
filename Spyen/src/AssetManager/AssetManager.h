#pragma once
#include <string>
#include <unordered_map>

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

	private:
		std::unordered_map<std::string, std::unique_ptr<Texture>> m_TextureMap;
	};

}

