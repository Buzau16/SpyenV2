#include "spypch.h"
#include "Sound.h"
#include <filesystem>
#include "Audio/IAudioEngine.h"
#include <Core/Defines.h>
#include <Core/Log.h>

namespace Spyen {
	Sound::Sound(const std::filesystem::path& path)
	{
		SPY_CORE_ASSERT(ma_sound_init_from_file(IAudioEngine::GetEngine(), path.string().c_str(), MA_SOUND_FLAG_DECODE, NULL, NULL, &m_Sound) == MA_SUCCESS, "Failed to load sound!");
	}

	Sound::~Sound()
	{
		ma_sound_uninit(&m_Sound);
	}

	void Sound::Play()
	{
		if (!(!IsPlaying() || HasPlaybackEnded()))
			return;

		SPY_CORE_ASSERT(ma_sound_seek_to_pcm_frame(&m_Sound, 0) == MA_SUCCESS, "Failed to reset playback position!");
		SPY_CORE_ASSERT(ma_sound_start(&m_Sound) == MA_SUCCESS, "Failed to start sound playback!");

		m_IsPlaying = true;
	}

	void Sound::Stop()
	{
		if (!m_IsPlaying) return;
		SPY_CORE_ASSERT(ma_sound_stop(&m_Sound) == MA_SUCCESS, "Failed to stop sound playback!");
		m_IsPlaying = false;
	}

}
