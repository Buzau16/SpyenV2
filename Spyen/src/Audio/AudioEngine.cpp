#include "spypch.h"
#include "AudioEngine.h"
#include <Core/Defines.h>
#include <AssetManager/AssetManager.h>
#include <Core/Log.h>


namespace Spyen {
	ma_engine AudioEngine::m_Engine;

	void AudioEngine::Init()
	{
		SPY_CORE_INFO("Initializing the audio engine!");
		SPY_CORE_ASSERT(ma_engine_init(NULL, &m_Engine) == MA_SUCCESS, "Failed to intialize the audio engine!");
		SPY_CORE_INFO("Audio engine initialized!");
	}

	void AudioEngine::Destroy()
	{
		SPY_CORE_INFO("Shutting down the audio engine");
		ma_engine_stop(&m_Engine);
	}

	void AudioEngine::PlaySound(const std::string& name)
	{
		AssetManager::GetSound(name.c_str())->Play();
	}

	void AudioEngine::StopSound(const std::string& name)
	{
		AssetManager::GetSound(name.c_str())->Stop();
	}

}