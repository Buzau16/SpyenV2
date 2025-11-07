#include "AssetManager.h"

#include "Core/Defines.h"
#include "Core/Log.h"


namespace Spyen
{
	AssetManager::AssetManager()
	{
		SPY_CORE_INFO("Initializing Asset Manager");
	}

	Texture* AssetManager::LoadTexture(const std::string& name, const std::filesystem::path& path)
	{
		SPY_CORE_ASSERT(!m_TextureMap.contains(name), "Texture {} already exists!", name);
		m_TextureMap.insert({ name, Texture(path) });
		SPY_CORE_INFO("Loading texture {0} at {1}", name, path.string());
		return &m_TextureMap.at(name);
	}

	Texture* AssetManager::GetTexture(const char* name)
	{
		SPY_CORE_ASSERT(m_TextureMap.contains(name), "Texture {} already exists!", name);
		return &m_TextureMap.at(name);
	}
}
