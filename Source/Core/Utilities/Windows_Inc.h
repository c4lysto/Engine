#ifndef _RECON_WINDOWS_INC_H
#define _RECON_WINDOWS_INC_H

#ifndef _RECON_FEATURE_LEVEL_DEFINES_H_
#include "FeatureLevelDefines.h"
#endif // _RECON_FEATURE_LEVEL_DEFINES_H_

#if RECON_OS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#undef SendMessage
#undef DeleteFile
#undef PostMessage
#undef Yield
#undef GetObject
#undef GetCharWidth
#endif // RECON_OS_WINDOWS

#endif // _RECON_WINDOWS_INC_H
