#ifndef _RECON_DEBUGHELP_H_
#define _RECON_DEBUGHELP_H_

#define RECON_DEBUG (_DEBUG || DEBUG_HELP_OVERRIDE)

#if RECON_DEBUG
#define DEBUG_ONLY(...) __VA_ARGS__
#else
#define DEBUG_ONLY(...)
#endif

#if RECON_DEBUG
#include <crtdbg.h>
#include <assert.h>

	#if RECON_OS_WINDOWS
		#include <Windows.h>
	#endif // RECON_OS_WINDOWS
#endif

#include "DebugWindow.h"

#if RECON_DEBUG
	#if RECON_OS_WINDOWS
		#define DEBUG_TRACK_MEMORY_LEAKS(allocNum) \
		do { \
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); \
			_CrtSetBreakAlloc(allocNum); \
		} while(0)
	#endif
#endif
#ifndef DEBUG_TRACK_MEMORY_LEAKS
	#define DEBUG_TRACK_MEMORY_LEAKS(allocNum)
#endif // DEBUG_TRACK_MEMORY_LEAKS

#ifndef DisplayDebugString
	#if RECON_DEBUG
		#if RECON_OS_WINDOWS
			#define DisplayDebugString(x, ...) \
				do { \
				char buff[512]; \
				sprintf_s(buff, 512, x, __VA_ARGS__); \
				OutputDebugStringA(buff); \
				} while(0)
		#endif // !RECON_OS_WINDOWS
	#endif RECON_DEBUG
#endif // #ifndef DisplayDebugString
#ifndef DisplayDebugString
	#define DisplayDebugString(x, ...)
#endif // DisplayDebugString

#ifndef Assertf
	#if RECON_DEBUG
		#define RECON_ASSERT 1

		#if RECON_OS_WINDOWS
			#define Assertf(condition, message, ...) \
				(void) ((!!(condition)) || \
						(1 != _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, _CRT_WIDE(message), __VA_ARGS__)) || \
						(__debugbreak(), 0))			
		#endif // !RECON_OS_WINDOWS
	#endif // RECON_DEBUG
#endif // ifndef Assertf
#ifndef RECON_ASSERT
	#define RECON_ASSERT 0
#endif // RECON_ASSERT
#ifndef Assertf
	#define Assertf(condition, message, ...)
#endif // Assertf

#ifndef Assert
	#if RECON_DEBUG
		#define Assert(condition) Assertf(condition, "")
	#else // !RECON_DEBUG
		#define Assert(condition)
	#endif // !RECON_DEBUG
#endif // ifndef Assert

#if RECON_ASSERT
	#define ASSERT_ONLY(x) (x)
#else // !RECON_ASSERT
	#define ASSERT_ONLY(x)
#endif // !RECON_ASSERT

#ifndef Verifyf
	#if RECON_DEBUG
		#if RECON_OS_WINDOWS
			#define Verifyf(condition, message, ...) \
				((condition) || \
				(1 != _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, _CRT_WIDE(message), __VA_ARGS__)) || \
				(__debugbreak(), 0))
		#endif // RECON_OS_WINDOWS			
	#endif // !RECON_DEBUG
#endif // ifndef Verifyf
#ifndef Verifyf
#define Verifyf(condition, message, ...) (condition)
#endif // Verifyf

#ifndef Verify
#if RECON_DEBUG
	#define Verify(condition) Verifyf(condition, "")
#else // !RECON_DEBUG
	#define Verify(condition) (condition)
#endif // !RECON_DEBUG
#endif // ifndef Verify

#ifndef Warning
	#if RECON_DEBUG
		#define Warning(message, ...) DisplayDebugString(message, __VA_ARGS__)
	#else // !RECON_DEBUG
		#define Warning(message, ...) 
	#endif
#endif // // ifndef Warning

#endif // _RECON_DEBUGHELP_H_