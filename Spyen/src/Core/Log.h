#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <memory>
#include <Core/Defines.h>

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)

namespace Spyen {

	// Move away from spdlog
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return s_CoreLogger;
		}

		static std::shared_ptr<spdlog::logger>& GetClientLogger()
		{
			return s_ClientLogger;
		}
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}


#ifdef SP_DEBUG
// Core log macros
#define SPY_CORE_TRACE(...)    ::Spyen::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SPY_CORE_INFO(...)     ::Spyen::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SPY_CORE_WARN(...)     ::Spyen::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SPY_CORE_ERROR(...)    ::Spyen::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SPY_CORE_CRITICAL(...) ::Spyen::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define SPY_TRACE(...)         ::Spyen::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SPY_INFO(...)          ::Spyen::Log::GetClientLogger()->info(__VA_ARGS__)
#define SPY_WARN(...)          ::Spyen::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SPY_ERROR(...)         ::Spyen::Log::GetClientLogger()->error(__VA_ARGS__)
#define SPY_CRITICAL(...)      ::Spyen::Log::GetClientLogger()->critical(__VA_ARGS__)


#define SPY_ASSERT(x, ...) { if(!(x)) { SPY_ERROR("Assertion Failed: {0}", __VA_ARGS__); SP_DEBUGBRAKE()(); } }
#define SPY_CORE_ASSERT(x, ...) { if(!(x)) { SPY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); SP_DEBUGBRAKE(); } }
#else
#define SPY_ASSERT(x, ...) x
#define SPY_CORE_ASSERT(x, ...) x

#define SPY_CORE_TRACE(...)  
#define SPY_CORE_INFO(...)
#define SPY_CORE_WARN(...)
#define SPY_CORE_ERROR(...) 
#define SPY_CORE_CRITICAL(...) 

// Client log macros
#define SPY_TRACE(...)   
#define SPY_INFO(...)       
#define SPY_WARN(...)      
#define SPY_ERROR(...)      
#define SPY_CRITICAL(...) 
#endif


#pragma warning(pop)