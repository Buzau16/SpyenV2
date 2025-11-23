#pragma once

#ifdef SP_DEBUG
#define SPY_ASSERT(x, ...) { if(!(x)) { SPY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define SPY_CORE_ASSERT(x, ...) { if(!(x)) { SPY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define SPY_ASSERT(x, ...) x
#define SPY_CORE_ASSERT(x, ...) x
#endif