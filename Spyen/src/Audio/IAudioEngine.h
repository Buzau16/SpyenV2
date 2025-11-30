#pragma once
#include "AudioEngine.h"


namespace Spyen {
	class IAudioEngine
	{
	public:
		inline static void PlaySound(const std::string& name) {
			s_Engine->PlaySound(name);
		}

		inline static void StopSound(const std::string& name) {
			s_Engine->StopSound(name);
		}


	private:
		static AudioEngine* s_Engine;
		static inline ma_engine* GetEngine() {
			return &s_Engine->m_Engine;
		}
		friend class Sound;
		friend class Engine;
	};

}

