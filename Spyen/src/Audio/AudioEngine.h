#pragma once
#include <miniaudio/miniaudio.h>
#include <string>


namespace Spyen {
	class AudioEngine
	{
	public:

		static void Init();
		static void Destroy();
		static void PlaySound(const std::string& name);
		static void StopSound(const std::string& name);

		static ma_engine* GetEngine() { return &m_Engine; };

	private:
		static ma_engine m_Engine;
		friend class IAudioEngine;
	};

}

