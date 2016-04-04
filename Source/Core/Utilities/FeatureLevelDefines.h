#ifndef _RECON_FEATURE_LEVEL_DEFINES_H_
#define _RECON_FEATURE_LEVEL_DEFINES_H_

/* Start: Compiler Detection */

/* Start: Microsoft Visual C++ Detection */
#define RECON_MSC_COMPILER (0)

#if defined(_MSC_VER)
	#undef RECON_MSC_COMPILER
	#define RECON_MSC_COMPILER (1)
#endif // defined(_MSC_VER)
/* End: Microsoft Visual C++ Detection */


/* Start: GCC Compiler Detection */
#define RECON_GCC_COMPILER (0)

#if defined(__GNUC__) || defined(__GNUG__)
	#undef RECON_GCC_COMPILER
	#define RECON_GCC_COMPILER (1)
#endif // defined(__GNUC__) || defined(__GNUG__)
/* End: GCC Compiler Detection */

/* End: Compiler Detection */


/*	Start: OS Detection	*/

#define RECON_OS_32BIT (1)
#define RECON_OS_64BIT (0)
#define RECON_OS_DETECTED (0)

/*	Start: Window Detection	*/
#define RECON_OS_WINDOWS (0)

#if !RECON_OS_DETECTED && (defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__))
	#undef RECON_OS_WINDOWS
	#define RECON_OS_WINDOWS (1)

	#if defined(_WIN64)
		#undef RECON_OS_64BIT
		#define RECON_OS_64BIT (1)
	#endif // Windows Version Detection

	// Let Code Know That We've Detected an OS
	#undef RECON_OS_DETECTED
	#define RECON_OS_DETECTED (1)

	#include "Windows_Inc.h"
#endif 
/*	End: Window Detection	*/


/*	Start: Apple Detection	*/
#define RECON_OS_MAC (0)
#define RECON_OS_IOS (0)

#if !RECON_OS_DETECTED && (defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__)))

	#if ((defined(__APPLE__) && defined(__MACH__)) && defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__))
		#undef RECON_OS_IOS
		#define RECON_OS_IOS (1)
	#else
		#undef RECON_OS_MAC
		#define RECON_OS_MAC (1)
	#endif

	// Let Code Know That We've Detected an OS
	#undef RECON_OS_DETECTED
	#define RECON_OS_DETECTED (1)
#endif
/*	End: Apple Detection	*/


/*	Start: Linux Detection	*/
#define RECON_OS_LINUX (0)

#if !RECON_OS_DETECTED && (defined(linux) || defined(__linux))
	#undef RECON_OS_LINUX
	#define RECON_OS_LINUX (1)
	// Let Code Know That We've Detected an OS
	#undef RECON_OS_DETECTED
	#define RECON_OS_DETECTED (1)
#endif
/*	End: Linux Detection	*/


/*	Start: Android Detection	*/
#define RECON_OS_ANDROID (0)

#if !RECON_OS_DETECTED && (defined(__ANDROID__))
	#undef RECON_OS_ANDROID
	#define RECON_OS_ANDROID (1)
	// Let Code Know That We've Detected an OS
	#undef RECON_OS_DETECTED
	#define RECON_OS_DETECTED (1)
#endif 
/*	End: Android Detection		*/

#if !RECON_OS_DETECTED
#error "FAILED TO DETECT THE OPERATING SYSTEM!!!"
#endif // !RECON_OS_DETECTED

/*	End: OS Detection	*/


/*	Start: C++ Feature Detection	*/

#ifndef CPP11
	#if defined(__cplusplus) && __cplusplus >= 201103L
		#define CPP11 (1)
	#else
		#define CPP11 (0)
	#endif // defined(__cplusplus) && __cplusplus >= 201103L
#endif // CPP11

#if RECON_MSC_COMPILER

// Disable some stupid compiler warnings
#pragma warning(disable : 4127) // Conditional Expression is Constant
#pragma warning(disable : 4512) // Assignment Operator Was Implicitly Defined As Deleted
#pragma warning(disable : 4010) // Single-Line Comment Contains Line-Continuation Character
#pragma warning(disable : 4201) // nonstandard extension used : nameless struct/union
#pragma warning(disable : 4714) // marked as __forceinline not inlined

#if (_MSC_VER >= 1800)
#define VS2013_FEATURE_LEVEL (1)
#define VS2012_FEATURE_LEVEL (1)
#define VS2010_FEATURE_LEVEL (1)
#elif (_MSC_VER >= 1700)
#define VS2013_FEATURE_LEVEL (0)
#define VS2012_FEATURE_LEVEL (1)
#define VS2010_FEATURE_LEVEL (1)
#elif (_MSC_VER >= 1600)
#define VS2013_FEATURE_LEVEL (0)
#define VS2012_FEATURE_LEVEL (0)
#define VS2010_FEATURE_LEVEL (1)
#else
#define VS2013_FEATURE_LEVEL (0)
#define VS2012_FEATURE_LEVEL (0)
#define VS2010_FEATURE_LEVEL (0)
#endif // !(_MSC_VER >= **)

#if VS2013_FEATURE_LEVEL
#define CPP_FEATURE_EXPLICIT_TYPE_CONV (1)
#define CPP_FEATURE_VARIADIC_TEMPLATES (1)
#define CPP_FEATURE_FUNCTION_DEFAULT (1)
#define CPP_FEATURE_FUNCTION_DELETION (1)
#endif // VS2013_FEATURE_LEVEL

#if VS2012_FEATURE_LEVEL
#define CPP_FEATURE_STRONGLY_TYPED_ENUMS (1)
#define CPP_FEATURE_FORWARD_DECLARED_ENUMS (1)
#define CPP_FEATURE_RANGE_BASED_LOOP (1)
#endif // VS2012_FEATURE_LEVEL

// Not Supported Yet: Damned Fools!
//#if (VS20 _FEATURE_LEVEL && CPP11)
//#define CPP_FEATURE_CONSTEXPR (1)
//#endif // 

//#if (VS20 _FEATURE_LEVEL && CPP11)
//#define CPP_FEATURE_USER_DEFINED_LITERALS (1)
//#endif // 

#else // if !defined(_MSC_VER)

#define RECON_MSC_COMPILER (0)
#define VS2013_FEATURE_LEVEL (0)
#define VS2012_FEATURE_LEVEL (0)
#define VS2010_FEATURE_LEVEL (0)

#if CPP11
#define CPP_FEATURE_EXPLICIT_TYPE_CONV (1)
#define CPP_FEATURE_VARADIC_TEMPLATES (1)
#define CPP_FEATURE_STRONGLY_TYPED_ENUMS (1)
#define CPP_FEATURE_FORWARD_DECLARED_ENUMS (1)
#define CPP_FEATURE_CONSTEXPR (1)
#define CPP_FEATURE_USER_DEFINED_LITERALS (1)
#define CPP_FEATURE_FUNCTION_DEFAULT (1)
#define CPP_FEATURE_FUNCTION_DELETION (1)
#define CPP_FEATURE_RANGE_BASED_LOOP (1)
#endif // CPP11

#endif // !defined(_MSC_VER)

#ifndef CPP_FEATURE_VARADIC_TEMPLATES
#define CPP_FEATURE_VARADIC_TEMPLATES (0)
#endif // CPP_FEATURE_VARADIC_TEMPLATES

#ifndef CPP_FEATURE_EXPLICIT_TYPE_CONV
#define CPP_FEATURE_EXPLICIT_TYPE_CONV (0)
#endif // CPP_FEATURE_EXPLICIT_TYPE_CONV

#ifndef CPP_FEATURE_STRONGLY_TYPED_ENUMS
#define CPP_FEATURE_STRONGLY_TYPED_ENUMS (0)
#endif // CPP_FEATURE_STRONGLY_TYPED_ENUMS

#ifndef CPP_FEATURE_FORWARD_DECLARED_ENUMS
#define CPP_FEATURE_FORWARD_DECLARED_ENUMS (0)
#endif // CPP_FEATURE_FORWARD_DECLARED_ENUMS

#ifndef CPP_FEATURE_CONSTEXPR
#define CPP_FEATURE_CONSTEXPR (0)
#endif // CPP_FEATURE_CONSTEXPR

#ifndef CPP_FEATURE_USER_DEFINED_LITERALS
#define CPP_FEATURE_USER_DEFINED_LITERALS (0)
#endif // CPP_FEATURE_USER_DEFINED_LITERALS

#ifndef CPP_FEATURE_FUNCTION_DEFAULT
#define CPP_FEATURE_FUNCTION_DEFAULT (0)
#endif // CPP_FEATURE_FUNCTION_DEFAULT

#ifndef CPP_FEATURE_FUNCTION_DELETION
#define CPP_FEATURE_FUNCTION_DELETION (0)
#endif // CPP_FEATURE_FUNCTION_DELETION

#ifndef CPP_FEATURE_RANGE_BASED_LOOP
#define CPP_FEATURE_RANGE_BASED_LOOP (0)
#endif // CPP_FEATURE_RANGE_BASED_LOOP

/*	End: C++ Feature Detection	*/



#endif // _RECON_FEATURE_LEVEL_DEFINES_H_