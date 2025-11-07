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
			return m_Instance->LoadTexture(name, path);
		}
		static inline Texture* GetTexture(const char* name)
		{
			return m_Instance->GetTexture(name);
		}
	private:
		static AssetManager* m_Instance;
		friend class Engine;
	};
}


