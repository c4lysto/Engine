#ifndef _RECON_GLOBAL_DEFINES_H_
#define _RECON_GLOBAL_DEFINES_H_

#include "FeatureLevelDefines.h"

#include <inttypes.h>

typedef int8_t s8;
typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef int32_t s32;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;

typedef float f32;
typedef double f64;


#ifndef SSE_AVAILABLE
	#if defined(_M_IX86) || defined(_M_AMD64)
		#define SSE_AVAILABLE (1)
	#else
		#define SSE_AVAILABLE (0)
	#endif
#endif // SSE_AVAILABLE

#ifndef ALIGN
	#if RECON_MSC_COMPILER
		#define ALIGN(byteAlign) __declspec(align(byteAlign))
	#elif RECON_GCC_COMPILER
		#define ALIGN(byteAlign) __attribute__((aligned(byteAlign)))
	#else
		#warning "#define ALIGN NOT SUPPORTED FOR THIS COMPILER TYPE!"
		#define ALIGN(byteAlign)
	#endif
#endif

#ifndef RESTRICT
	#define RESTRICT __restrict
#endif // RESTRICT

#ifndef GLOBALCONST
	#if RECON_MSC_COMPILER
		#define GLOBALCONST extern const __declspec(selectany)
	#elif RECON_GCC_COMPILER
		#define GLOBALCONST extern const __attribute__((weak))
	#else
		#warning "#define GLOBALCONST NOT SUPPORTED FOR THIS COMPILER TYPE!"
		#define GLOBALCONST
	#endif
#endif

#ifndef THREADLOCAL
	#if RECON_MSC_COMPILER
		#define THREADLOCAL __declspec(thread)
	#elif RECON_GCC_COMPILER
		#define THREADLOCAL __thread
	#else
		#warning "#define THREADLOCAL NOT SUPPORTED FOR THIS COMPILER TYPE!"
		#define THREADLOCAL
	#endif
#endif

#ifndef NOINLINE
	#if RECON_MSC_COMPILER
		#define NOINLINE __declspec(noinline)
	#elif RECON_GCC_COMPILER
		#define NOINLINE __attribute__((noinline))
	#else
		#warning "#define NOINLINE NOT SUPPORTED FOR THIS COMPILER TYPE!"
		#define NOINLINE
	#endif
#endif 

#ifndef FORCEINLINE_DEFINED
	#define FORCEINLINE_DEFINED
	#if RECON_GCC_COMPILER
		#define __forceinline __attribute__((always_inline))
	#elif !RECON_MSC_COMPILER
		#warning "#define __forceinline NOT SUPPORTED FOR THIS COMPILER TYPE 'inline' will be used in place of __forceinline"
		#define __forceinline inline
	#endif
#endif // FORCEINLINE_DEFINED

#ifndef SAFE_DELETE
	#define SAFE_DELETE(del) do{ delete del; del = nullptr; } while(0)
#endif

#ifndef SAFE_CHECK_DELETE
	#define SAFE_CHECK_DELETE(del) do{ if(del) {delete del; del = nullptr;} } while(0)
#endif

#ifndef SAFE_RELEASE
	#define SAFE_RELEASE(rel) do{ if(rel) {rel->Release(); rel = nullptr;} } while(0)
#endif

#ifndef NUMELEM
	template<typename T, size_t N>
	char(&ArraySizeHelper(T(&array)[N]))[N];
	#define NUMELEM(arr) (sizeof(ArraySizeHelper(arr)))
#endif

#ifndef UNUSED_PARAM
	#define UNUSED_PARAM(x)
#endif // UNUSED_PARAM

#ifndef COMMENT
	#define COMMENT(...)
#endif // COMMENT

#ifndef WARN_UNUSED_RESULT
	#if RECON_MSC_COMPILER && defined(_SAL_VERSION)
		#define WARN_UNUSED_RESULT(x) _Check_return_ x
	#elif RECON_GCC_COMPILER
		#define WARN_UNUSED_RESULT(x) __attribute__(warn_unused_result) x
	#else
		#define WARN_UNUSED_RESULT(x) x
#endif
#endif // WARN_UNUSED_RESULT

#ifndef TO_STRING
	#define TO_STRING(str) #str
#endif

#define ONE_OVER_255 (1.0f/255.0f)

#define CHAR_MASK (0xFFui8)
#define U8_MASK CHAR_MASK

#define SHORT_MASK (0xFFFFui16)
#define U16_MASK SHORT_MASK

#define INT_MASK (0xFFFFFFFFui32)
#define LONG_MASK INT_MASK
#define U32_MASK INT_MASK

#define LONG_LONG_MASK (0xFFFFFFFFFFFFFFFFui64)
#define U64_MASK LONG_LONG_MASK


#define S8_MIN		(-128i8)
#define S8_MAX		(127i8)
#define U8_MAX		(0xFFui8)

#define S16_MIN		(-32768i16)
#define S16_MAX		(32767i16)
#define U16_MAX		(0xFFFFui16)

#define S32_MIN		(-2147483648i32)
#define S32_MAX		(2147483647i32)
#define U32_MAX		(0xFFFFFFFFui32)

#define S64_MIN		(-9223372036854775808i64)
#define S64_MAX		(9223372036854775807i64)
#define U64_MAX		(0xFFFFFFFFFFFFFFFFui64)

#ifndef INFINITE
	#define INFINITE	0xFFFFFFFF
#endif // INFINITE

#define BIT(bit) (1<<bit)
#define BIT0 BIT(0)
#define BIT1 BIT(1)
#define BIT2 BIT(2)
#define BIT3 BIT(3)
#define BIT4 BIT(4)
#define BIT5 BIT(5)
#define BIT6 BIT(6)
#define BIT7 BIT(7)
#define BIT8 BIT(8)
#define BIT9 BIT(9)
#define BIT10 BIT(10)
#define BIT11 BIT(11)
#define BIT12 BIT(12)
#define BIT13 BIT(13)
#define BIT14 BIT(14)
#define BIT15 BIT(15)
#define BIT16 BIT(16)
#define BIT17 BIT(17)
#define BIT18 BIT(18)
#define BIT19 BIT(19)
#define BIT20 BIT(20)
#define BIT21 BIT(21)
#define BIT22 BIT(22)
#define BIT23 BIT(23)
#define BIT24 BIT(24)
#define BIT25 BIT(25)
#define BIT26 BIT(26)
#define BIT27 BIT(27)
#define BIT28 BIT(28)
#define BIT29 BIT(29)
#define BIT30 BIT(30)
#define BIT31 BIT(31)

#define S8_SIGN_BIT BIT7
#define S16_SIGN_BIT BIT15
#define S32_SIGN_BIT BIT31
#define S64_SIGN_BIT BIT(63)

#define F32_SIGN_BIT BIT31
#define f64_SIGN_BIT BIT(63)

#endif