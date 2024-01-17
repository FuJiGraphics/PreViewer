#pragma once

#ifdef PV_PLATFORM_WINDOWS
	#ifdef PV_SHARED_DLL
		#ifdef PV_BUILD_DLL
			#define PV_API	__declspec(dllexport)
		#else
			#define PV_API	__declspec(dllimport)
		#endif
	#else
		#define PV_API
	#endif
#endif

#pragma region Asserts
	#ifdef PV_ENABLE_ASSERTS
		#define PV_CLIENT_ASSERT(x, ...)	{ if(!(x)){ PV_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
		#define PV_CORE_ASSERT(x, ...)		{ if(!(x)){ PV_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#else 
		#define PV_CLIENT_ASSERT(x, ...)
		#define PV_CORE_ASSERT(x, ...)
	#endif 
#pragma endregion
