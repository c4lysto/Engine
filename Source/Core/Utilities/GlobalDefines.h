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

// Too Risky To Redefine NULL!
//#if !defined(__cplusplus) || (defined(_MSC_VER) && _MSC_VER < 1600)
//	#define NULL 0
//#else
//	#define NULL nullptr
//#endif

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
	#define NUMELEM(arr) (sizeof(arr)/(*(arr)))
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

#define CHAR_MASK (0xFFL)
#define SHORT_MASK (0xFFFFL)
#define INT_MASK (0xFFFFFFFFL)
#define LONG_MASK INT_MASK
#define LONG_LONG_MASK (0xFFFFFFFFFFFFFFFFLL)

#ifndef CHAR_MIN
	#define CHAR_MIN	(-128i8)
#endif // CHAR_MIN

#ifndef S8_MIN
	#define S8_MIN		CHAR_MIN
#endif // S8_MIN

#ifndef CHAR_MAX
	#define CHAR_MAX	(127i8)
#endif // CHAR_MAX

#ifndef S8_MAX
	#define S8_MAX		CHAR_MAX
#endif // S8_MAX

#ifndef UCHAR_MAX
	#define UCHAR_MAX	(0xFFui8)
#endif // UCHAR_MAX

#ifndef U8_MAX
	#define U8_MAX		UCHAR_MAX
#endif // U8_MAX

#ifndef SHORT_MIN
	#define SHORT_MIN	(-32768i16)
#endif // SHORT_MIN

#ifndef S16_MIN
	#define S16_MIN		SHORT_MIN
#endif // S8_MIN

#ifndef SHORT_MAX
	#define SHORT_MAX	(32767i16)
#endif // SHORT_MAX

#ifndef S16_MAX
	#define S16_MAX		SHORT_MAX
#endif // S8_MAX

#ifndef USHORT_MAX
	#define USHORT_MAX	(0xFFFFui16)
#endif // USHORT_MAX

#ifndef U16_MAX
	#define U16_MAX		USHORT_MAX
#endif // S8_MAX

#ifndef INT_MIN
	#define INT_MIN		(-2147483648i32)
#endif // INT_MIN

#ifndef LONG_MIN
	#define LONG_MIN	INT_MIN
#endif // LONG_MIN

#ifndef S32_MIN
	#define S32_MIN		INT_MIN
#endif // S32_MIN

#ifndef INT_MAX
	#define	INT_MAX		(2147483647i32)
#endif // INT_MAX

#ifndef LONG_MAX
	#define LONG_MAX	INT_MAX
#endif // LONG_MAX

#ifndef S32_MAX
	#define S32_MAX		INT_MAX
#endif // S32_MAX

#ifndef UINT_MAX
	#define	UINT_MAX	(0xFFFFFFFFui32)
#endif // UINT_MAX

#ifndef ULONG_MAX
	#define ULONG_MAX	UINT_MAX
#endif // ULONG_MAX

#ifndef U32_MAX
	#define U32_MAX		UINT_MAX
#endif // U32_MAX

#ifndef LLONG_MIN
	#define LLONG_MIN	(-9223372036854775808i64)
#endif // LLONG_MIN

#ifndef S64_MIN
	#define S64_MIN		LLONG_MIN
#endif // S64_MIN

#ifndef LLONG_MAX
	#define LLONG_MAX	(9223372036854775807i64)
#endif // LLONG_MAX

#ifndef S64_MAX
	#define S64_MAX		LLONG_MAX
#endif // S64_MAX

#ifndef ULLONG_MAX
	#define ULLONG_MAX	(0xFFFFFFFFFFFFFFFFui64)
#endif // ULLONG_MAX

#ifndef U64_MAX
	#define U64_MAX		ULLONG_MAX
#endif // U64_MAX

#ifndef INFINITE
	#define INFINITE	(0xFFFFFFFF)
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
#define FLOAT_SIGN_BIT BIT31

__forceinline void Prefetch_Impl(void* pMem)
{
#if SSE_AVAILABLE
	//_mm_prefetch((const s8*)pMem, _MM_HINT_NTA);
#else // if !SSE_AVAILABLE
	CompileTimeAssert(false, "Do NOT use Prefetch_Impl Directly, Use Prefetch Instead!");
#endif // !SSE_AVAILABLE
}

#ifndef Prefetch
	#if SSE_AVAILABLE
		#define Prefetch(p) Prefetch_Impl(p) 
	#else // if !SSE_AVAILABLE
		#define Prefetch(p) 
	#endif // !SSE_AVAILABLE
#endif // Prefetch

#endif