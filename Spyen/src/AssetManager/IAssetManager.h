#pragma once
#include "AssetManager.h"

namespace Spyen
{
	// Interface for accessing the asset manager globally
	class IAssetManager
	{
	public:
		static inline Texture* LoadTexture(const std::string& name, const std::filesystem::path& path)
		{
			return s_Instance->LoadTexture(name, path);
		}
		static inline Texture* GetTexture(const char* name)
		{
			return s_Instance->GetTexture(name);
		}

		static inline Texture* LoadTexture(const std::filesystem::path& path) {
			return s_Instance->LoadTextureP(path);
		}

		static inline Sound* LoadSound(const std::string& name, const std::filesystem::path& path) {
			return s_Instance->LoadSound(name, path);
		}

		static inline Sound* GetSound(const char* name) {
			return s_Instance->GetSound(name);
		}

	private:
		static AssetManager* s_Instance;
		friend class Engine;
	};
}


