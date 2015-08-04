#ifndef _RECON_UTILITIES_INCLUDE_H_
#define _RECON_UTILITIES_INCLUDE_H_

#define USING_WINDOWS ((defined(WIN32) && WIN32) || (defined(RECON_OS_WINDOWS && RECON_OS_64BIT) && RECON_OS_WINDOWS && RECON_OS_64BIT))

#if 1
#include <Windows.h>
#endif

#pragma warning(disable : 4127) // Conditional Expression is Constant
#pragma warning(disable : 4512) // Assignment Operator Was Implicitly Defined As Deleted
#pragma warning(disable : 4010) // Single-Line Comment Contains Line-Continuation Character
#pragma warning(disable : 4201) // nonstandard extension used : nameless struct/union
#pragma warning(disable : 4714) // marked as FORCEINLINE not inlined

#include "GlobalDefines.h"
#include "Debugging/DebugHelp.h"

#endif //_RECON_UTILITIES_INCLUDE_H_