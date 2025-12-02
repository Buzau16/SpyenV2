#pragma once
#include <Audio/miniaudio/miniaudio.h>
#include <string>


namespace Spyen {
	class AudioEngine
	{
	public:
		AudioEngine();
		~AudioEngine();

		void PlaySound(const std::string& name);
		void StopSound(const std::string& name);

	private:
		ma_engine m_Engine;
		friend class IAudioEngine;
	};

}

