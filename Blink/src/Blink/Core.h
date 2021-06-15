#pragma once

#ifdef BL_PLATFORM_WINDOWS
	#ifdef BL_BUILD_DLL
		#define BLINK_API __declspec(dllexport)
	#else
		#define BLINK_API __declspec(dllimport)
	#endif
#else 
	#error Blink only supports Windows!
#endif

#define BIT(x) (1 << x)