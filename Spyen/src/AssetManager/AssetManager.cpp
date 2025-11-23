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
		m_TextureMap.insert({ name, std::make_unique<Texture>(path) });
		SPY_CORE_INFO("Loading texture {0} at {1}", name, path.string());
		return m_TextureMap.at(name).get();
	}

	Texture* AssetManager::GetTexture(const char* name)
	{
		SPY_CORE_ASSERT(m_TextureMap.contains(name), "Texture {} doesn't exist!", name);
		return m_TextureMap.at(name).get();
	}

	Sound* AssetManager::LoadSound(const std::string& name, const std::filesystem::path& path)
	{
		SPY_CORE_ASSERT(!m_SoundMap.contains(name), "Sound {} already exists!", name);
		m_SoundMap.insert({ name, std::make_unique<Sound>(path) });
		SPY_CORE_INFO("Loading sound {0} at {1}", name, path.string());
	}

	Sound* AssetManager::GetSound(const char* name)
	{
		SPY_CORE_ASSERT(m_SoundMap.contains(name), "Sound {} doesn't exist!", name);
		return m_SoundMap.at(name).get();
	}
}
