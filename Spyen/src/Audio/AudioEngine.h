#pragma once
#include <miniaudio/miniaudio.h>


namespace Spyen {
	class AudioEngine
	{
	public:
		AudioEngine();
		~AudioEngine();

		void PlaySound(const char* name);
		void StopSound(const char* name);

	private:
		ma_engine m_Engine;
	};

}

