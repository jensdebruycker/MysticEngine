#pragma once

#ifdef MS_PLATFORM_WINDOWS
	#ifdef MS_BUILD_DLL
		#define MYSTIC_API __declspec(dllexport)
	#else
		#define MYSTIC_API __declspec(dllimport)
	#endif
#else
	#error MysticEngine only supports windows!
#endif

#define BIT(x) (1 << x)