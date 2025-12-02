#pragma once
#include <Audio/miniaudio/miniaudio.h>
#include <filesystem>


namespace Spyen {
	class Sound
	{
	public:
		Sound(const std::filesystem::path& path);
		~Sound();

		void Play();
		void Stop();

		inline bool HasPlaybackEnded() const { return ma_sound_at_end(&m_Sound); }
		inline bool IsPlaying() const { return m_IsPlaying; }

		inline static Sound* Create(std::filesystem::path& path) {
			Sound* sound = new Sound(path);
			return sound;
		}

	private:
		ma_sound m_Sound;
		bool m_IsPlaying = false;
	};

}

