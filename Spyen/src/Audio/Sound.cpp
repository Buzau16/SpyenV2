#include "Sound.h"
#include <filesystem>
#include <Core/Defines.h>

namespace Spyen {
	Sound::Sound(const std::filesystem::path& path, ma_engine* pEngine)
	{
		SPY_CORE_ASSERT(ma_sound_init_from_file(pEngine, path.string().c_str(), MA_SOUND_FLAG_DECODE, NULL, NULL, &m_Sound) == MA_SUCCESS, "Failed to load sound!");
	}

	Sound::~Sound()
	{
		ma_sound_uninit(&m_Sound);
	}

	void Sound::Play()
	{
		SPY_CORE_ASSERT(ma_sound_seek_to_pcm_frame(&m_Sound, 0) == MA_SUCCESS, "Failed to reset playback position!");
		SPY_CORE_ASSERT(ma_sound_start(&m_Sound) == MA_SUCCESS, "Failed to start sound playback!");
	}

	void Sound::Stop()
	{
		if (!m_IsPlaying) return;
		SPY_CORE_ASSERT(ma_sound_stop(&m_Sound) == MA_SUCCESS, "Failed to stop sound playback!");
		m_IsPlaying = false;
	}

}
