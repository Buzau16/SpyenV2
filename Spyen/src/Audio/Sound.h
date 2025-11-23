#pragma once
#include <miniaudio/miniaudio.h>


namespace Spyen {
	class Sound
	{
	public:
		Sound(const std::filesystem::path& path, ma_engine* pEngine);
		~Sound();

		void Play();
		void Stop();

		inline bool HasPlaybackEnded() const { return ma_sound_at_end(&m_Sound); }
		inline bool IsPlaying() const { return m_IsPlaying; }

	private:
		ma_sound m_Sound;
		bool m_IsPlaying = false;
	};

}

