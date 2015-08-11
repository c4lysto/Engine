#ifndef _RECON_FUNCTION_H_
#define _RECON_FUNCTION_H_

#include <functional>
#include <type_traits>

#include "UtilitiesInclude.h"

namespace recon
{

template<typename _FuncType> class Function;
template<typename _FuncPtrType> class StaticFunction;
template<typename _ClassName, typename _FuncPtrType> class MemberFunction;

template<typename _FuncPtrType>
struct _FuncPointerContainer
{
	typedef _FuncPtrType Type;

private:
	Type m_FuncPtr;

public:
	_FuncPointerContainer(const _FuncPtrType& funcPtr) :
		m_FuncPtr(funcPtr)
	{
	}
	
	const Type& Get() const
	{
		return m_FuncPtr;
	}

	Type& Get()
	{
		return m_FuncPtr;
	}
};

template<typename _RetType, typename... _tArgs>
class _IntermediateFuncPtr
{
public:
	virtual ~_IntermediateFuncPtr() = 0 {}

	virtual _RetType CallFunc(_tArgs&&... args) const = 0;

	virtual _IntermediateFuncPtr<_RetType, _tArgs...>* CreateCopy() const = 0;
};

template<typename _FuncPtrType, typename _RetType, typename... _tArgs>
class _IntermediateStaticFuncPtr : public _IntermediateFuncPtr<_RetType, _tArgs...>, public _FuncPointerContainer<_FuncPtrType>
{
public:
	_IntermediateStaticFuncPtr(const _IntermediateStaticFuncPtr& rhs) : _FuncPointerContainer(rhs.Get()){}
	_IntermediateStaticFuncPtr(_IntermediateStaticFuncPtr&& rhs) : _FuncPointerContainer(rhs.Get()) {}
	_IntermediateStaticFuncPtr(const _FuncPtrType& pFunc) : _FuncPointerContainer(pFunc) {}
	virtual ~_IntermediateStaticFuncPtr() {}

	virtual __forceinline _RetType CallFunc(_tArgs&&... args) const override
	{
		return (Get())(std::forward<_tArgs...>(args...));
	}

	virtual _IntermediateFuncPtr<_RetType, _tArgs...>* CreateCopy() const override
	{
		return new _IntermediateStaticFuncPtr<_FuncPtrType, _RetType, _tArgs...>(*this);
	}
};

template<typename _ClassObjType, typename _FuncPtrType, typename _RetType, typename... _tArgs>
class _IntermediateMemberFuncPtr : public _IntermediateFuncPtr<_RetType, _tArgs...>, public _FuncPointerContainer<_FuncPtrType>
{
protected:
	_ClassObjType m_InvokingObject;

public:
	_IntermediateMemberFuncPtr(const _IntermediateMemberFuncPtr& rhs) : _FuncPointerContainer(rhs.Get()), m_InvokingObject(rhs.m_InvokingObject) {}
	_IntermediateMemberFuncPtr(_IntermediateMemberFuncPtr&& rhs) : _FuncPointerContainer(rhs.Get()), m_InvokingObject(rhs.m_InvokingObject) {}
	_IntermediateMemberFuncPtr(_ClassObjType&& invokingObject, const _FuncPtrType& pFunc) : _FuncPointerContainer(pFunc), m_InvokingObject(invokingObject) {}

	virtual ~_IntermediateMemberFuncPtr() {};

	virtual __forceinline _RetType CallFunc(_tArgs&&... args) const override
	{
		return CallFunc_Internal(m_InvokingObject, std::forward<_tArgs...>(args...));
	}

	virtual _IntermediateFuncPtr<_RetType, _tArgs...>* CreateCopy() const override
	{
		return new _IntermediateMemberFuncPtr<_ClassObjType, _FuncPtrType, _RetType, _tArgs...>(*this);
	}

private:
	template<typename _ClassName>
	__forceinline _RetType CallFunc_Internal(_ClassName& classObj, _tArgs&&... args) const
	{
		return (classObj.*Get())(std::forward<_tArgs...>(args...));
	}

	template<typename _ClassName>
	__forceinline _RetType CallFunc_Internal(const _ClassName& classObj, _tArgs&&... args) const
	{
		return (classObj.*Get())(std::forward<_tArgs...>(args...));
	}

	template<typename _ClassName>
	__forceinline _RetType CallFunc_Internal(_ClassName* classObj, _tArgs&&... args) const
	{
		return (classObj->*Get())(std::forward<_tArgs...>(args...));
	}

	template<typename _ClassName>
	__forceinline _RetType CallFunc_Internal(const _ClassName* classObj, _tArgs&&... args) const
	{
		return (classObj->*Get())(std::forward<_tArgs...>(args...));
	}
};

namespace _IntermediateFuncPtrCreation
{
	template<typename _FuncPtrType, typename _RetType, typename... _tArgs>
	_IntermediateFuncPtr<_RetType, _tArgs...>* Create(_FuncPtrType&& funcPtr)
	{
		typedef typename std::decay<_FuncPtrType>::type _RealFuncPtrType;

		if(std::_Test_callable(funcPtr))
		{
			return new _IntermediateStaticFuncPtr<_RealFuncPtrType, _RetType, _tArgs...>(std::forward<_RealFuncPtrType>(funcPtr));
		}

		return nullptr;
	}

	template<typename _ClassObjType, typename _FuncPtrType, typename _RetType, typename... _tArgs>
	_IntermediateFuncPtr<_RetType, _tArgs...>* Create(_ClassObjType&& classObj, _FuncPtrType&& funcPtr)
	{
		typedef typename std::decay<_FuncPtrType>::type _RealFuncPtrType;

		if(std::_Test_callable(funcPtr))
		{
			return new _IntermediateMemberFuncPtr<_ClassObjType, _RealFuncPtrType, _RetType, _tArgs...>(std::forward<_ClassObjType>(classObj), std::forward<_RealFuncPtrType>(funcPtr));
		}

		return nullptr;
	}
}

template<typename _RetType, typename... _tArgs>
class _FuncPtrBase
{
protected:
	typedef _FuncPtrBase<_RetType, _tArgs...> _MyType;
	typedef _RetType ReturnType;

private:
	_IntermediateFuncPtr<_RetType, _tArgs...>* m_pIntermediateFuncPtr;

protected:
	void Set(nullptr_t)
	{
		SAFE_DELETE(m_pIntermediateFuncPtr);
	}

	template<typename funcPtrType>
	void Set(funcPtrType&& funcPtr)
	{
		SAFE_DELETE(m_pIntermediateFuncPtr);
		m_pIntermediateFuncPtr = _IntermediateFuncPtrCreation::Create<funcPtrType, _RetType, _tArgs...>(std::forward<funcPtrType>(funcPtr));
	}

	template<typename classObjType, typename funcPtrType>
	void Set(classObjType&& classObj, funcPtrType&& funcPtr)
	{
		SAFE_DELETE(m_pIntermediateFuncPtr);
		m_pIntermediateFuncPtr = _IntermediateFuncPtrCreation::Create<classObjType, funcPtrType, _RetType, _tArgs...>(std::forward<classObjType>(classObj), std::forward<funcPtrType>(funcPtr));
	}

	__forceinline void Copy(const _MyType& rhs)
	{
		SAFE_DELETE(m_pIntermediateFuncPtr);
		if(rhs.m_pIntermediateFuncPtr)
			m_pIntermediateFuncPtr = rhs.m_pIntermediateFuncPtr->CreateCopy();
	}

public:
	_FuncPtrBase() : m_pIntermediateFuncPtr(nullptr) {}
	_FuncPtrBase(const _MyType& rhs)
	{
		if(rhs.m_pIntermediateFuncPtr)
		{
			m_pIntermediateFuncPtr = m_pIntermediateFuncPtr->CreateCopy();
		}
	}

	_FuncPtrBase(_MyType&& rhs) : m_pIntermediateFuncPtr(rhs.m_pIntermediateFuncPtr)
	{
		rhs.m_pIntermediateFuncPtr = nullptr;
	}

	~_FuncPtrBase()
	{
		SAFE_DELETE(m_pIntermediateFuncPtr);
	}

	__forceinline _MyType& operator=(const _MyType& rhs)
	{
		if(this != &rhs)
		{
			Copy(rhs);
		}
		return *this;
	}

	__forceinline _MyType& operator=(_MyType&& rhs)
	{
		if(this != &rhs)
		{
			SAFE_DELETE(m_pIntermediateFuncPtr);
			m_pIntermediateFuncPtr = rhs.m_pIntermediateFuncPtr;

			rhs.m_pIntermediateFuncPtr = nullptr;
		}
		return *this;
	}

	__forceinline ReturnType operator()(_tArgs... args) const
	{
		Assertf(m_pIntermediateFuncPtr, "_FuncPtrBase - Invalid Function Implementation!");
		return m_pIntermediateFuncPtr->CallFunc(std::forward<_tArgs...>(args...));
	}

	__forceinline operator bool() const {return m_pIntermediateFuncPtr != nullptr; }
};

template<typename _FuncPtrType>
struct _FunctionTraits;

template<typename _RetType, typename... _tArgs>
struct _FunctionTraits <_RetType(_tArgs...)>
{
	typedef _RetType(*DefaultPointerType)(_tArgs...);
	typedef _FuncPtrBase<_RetType, _tArgs...> InterfaceType;
};


#pragma warning(disable : 4521) // multiple copy constructors specified
#pragma warning(disable : 4522) // multiple assignment operators specified

// Lightweight Wrapper Around The C++ Default Style Function Pointer
template<typename _FuncPtrType>
class StaticFunction
{
	friend class Function<_FuncPtrType>;

	typedef StaticFunction<_FuncPtrType> _MyType;

public:
	typedef typename _FunctionTraits<_FuncPtrType>::DefaultPointerType PointerType;

private:
	PointerType m_pFunc;

public:
	StaticFunction() :
		m_pFunc(nullptr)
	{
	}

	StaticFunction(const _MyType& rhs) :
		m_pFunc(rhs.m_pFunc)
	{
	}

	StaticFunction(_MyType& rhs) :
		m_pFunc(rhs.m_pFunc)
	{
	}

	explicit StaticFunction(nullptr_t) :
		m_pFunc(nullptr)
	{
	}

	template<typename funcPtrType>
	StaticFunction(funcPtrType& funcPtr) :
		m_pFunc(funcPtr)
	{
	}

	_MyType& operator=(const _MyType& rhs)
	{
		if(this != &rhs)
		{
			m_pFunc = rhs.m_pFunc;
		}
		return *this;
	}

	 _MyType& operator=(_MyType& rhs)
	{
		if(this != &rhs)
		{
			m_pFunc = rhs.m_pFunc;
		}
		return *this;
	}

	__forceinline _MyType& operator=(nullptr_t)
	{
		m_pFunc = nullptr;
		return *this;
	}

	template<typename funcPtrType>
	__forceinline _MyType& operator=(funcPtrType&& rhs)
	{
		m_pFunc = rhs;
		return *this;
	}

	__forceinline operator PointerType() const
	{
		return m_pFunc;
	}
};


template<typename _RetType, typename _ClassName, typename... _tArgs>
class _MemberFunctionImplementation
{
	friend class Function<_RetType(_tArgs...)>;

	typedef _MemberFunctionImplementation<_RetType, _ClassName, _tArgs...> _MyType;

public:
	typedef _RetType ReturnType;
	typedef _RetType(_ClassName::*PointerType)(_tArgs...);
	typedef _RetType(_ClassName::*PointerTypeConst)(_tArgs...) const;

private:
	_ClassName* m_pInvokingObject;
	PointerType m_pFunc;

public:
	_MemberFunctionImplementation() :
		m_pInvokingObject(nullptr),
		m_pFunc(nullptr)
	{
	}

	_MemberFunctionImplementation(const _MyType& rhs) :
		m_pInvokingObject(rhs.m_pInvokingObject),
		m_pFunc(rhs.m_pFunc)
	{
	}

	explicit _MemberFunctionImplementation(nullptr_t) :
		m_pInvokingObject(nullptr),
		m_pFunc(nullptr)
	{
	}

	_MemberFunctionImplementation(const _ClassName* pInvokingObject, PointerTypeConst pFunc) :
		m_pInvokingObject((_ClassName*)pInvokingObject),
		m_pFunc((PointerType)pFunc)
	{
	}

	_MemberFunctionImplementation(_ClassName* pInvokingObject, PointerTypeConst pFunc) :
		m_pInvokingObject(pInvokingObject),
		m_pFunc((PointerType)pFunc)
	{
	}

	_MemberFunctionImplementation(_ClassName* pInvokingObject, PointerType pFunc) :
		m_pInvokingObject(pInvokingObject),
		m_pFunc(pFunc)
	{
	}

	_MyType& operator=(const _MyType& rhs)
	{
		if(this != &rhs)
		{
			m_pInvokingObject = rhs.m_pInvokingObject;
			m_pFunc = rhs.m_pFunc;
		}
		return *this;
	}

	_MyType& operator=(nullptr_t)
	{
		m_pInvokingObject = nullptr;
		m_pFunc = nullptr;
		return *this;
	}

	_MyType& operator=(PointerTypeConst pFunc)
	{
		m_pFunc = (PointerType)pFunc;
		return *this;
	}

	_MyType& operator=(PointerType pFunc)
	{
		m_pFunc = pFunc;
		return *this;
	}

	__forceinline void SetInvokingObject(const _ClassName* pInvokingObject) { m_pInvokingObject = (_ClassName*)pInvokingObject; }
	__forceinline void SetInvokingObject(_ClassName* pInvokingObject) { m_pInvokingObject = pInvokingObject; }

	__forceinline PointerType Get() { return m_pFunc; }

	__forceinline operator bool() const { return m_pFunc != nullptr; }

	__forceinline ReturnType operator()(_tArgs... args) const
	{
		Assertf(m_pFunc, "_MemberFunctionImplementation - Invalid Function Pointer!");
		return (m_pInvokingObject->*m_pFunc)(args...);
	}
};


template<typename _ClassName, typename _FuncPtrType>
struct _MemberFunctionTraits;

template<typename _RetType, typename _ClassName, typename... _tArgs>
struct _MemberFunctionTraits <_ClassName, _RetType(_tArgs...)>
{
	typedef _RetType(_ClassName::*DefaultPointerType)(_tArgs...);
	typedef _RetType(_ClassName::*DefaultPointerTypeConst)(_tArgs...) const;
	typedef _MemberFunctionImplementation<_RetType, _ClassName, _tArgs...> InterfaceType;
};


template<typename _ClassName, typename _FuncPtrType>
class MemberFunction : public _MemberFunctionTraits<_ClassName, _FuncPtrType>::InterfaceType
{
public:
	typedef _ClassName _Class;
	typedef MemberFunction<_ClassName, _FuncPtrType> _MyType;
	typedef typename _MemberFunctionTraits<_ClassName, _FuncPtrType>::InterfaceType _MyBase;


public:
	MemberFunction()
	{
	}

	MemberFunction(const _MyType& rhs) :
		_MyBase(rhs)
	{
	}

	explicit MemberFunction(nullptr_t) :
		_MyBase(nullptr)
	{
	}

	MemberFunction(const _ClassName* pInvokingObject, typename _MyBase::PointerTypeConst pFunc) :
		_MyBase(pInvokingObject, pFunc)
	{
	}

	MemberFunction(_ClassName* pInvokingObject, typename _MyBase::PointerTypeConst pFunc) :
		_MyBase(pInvokingObject, pFunc)
	{
	}

	MemberFunction(_ClassName* pInvokingObject, typename _MyBase::PointerType pFunc) :
		_MyBase(pInvokingObject, pFunc)
	{
	}

	_MyType& operator=(const _MyType& rhs)
	{
		_MyBase::operator=(rhs);
		return *this;
	}

	_MyType& operator=(nullptr_t)
	{
		_MyBase::operator=(nullptr);
		return *this;
	}
};


#define CREATE_MEM_FUNC_TRAITS(createFuncWrap, callConv) \
								createFuncWrap(callConv, const, &, ) \
								createFuncWrap(callConv, const, &, const) \
								createFuncWrap(callConv, , &, const) \
								createFuncWrap(callConv, , &, ) \
								createFuncWrap(callConv, const, *, ) \
								createFuncWrap(callConv, const, *, const) \
								createFuncWrap(callConv, , *, const) \
								createFuncWrap(callConv, , *, )


#if _WIN64
#define CREATE_MEM_FUNC_TRAITS_ALL(createFuncWrap) \
		CREATE_MEM_FUNC_TRAITS(createFuncWrap, __cdecl) \
		CREATE_MEM_FUNC_TRAITS(createFuncWrap, __vectorcall) //\
		CREATE_MEM_FUNC_TRAITS(createFuncWrap, __clrcall)
#else // if !_WIN64
#define CREATE_MEM_FUNC_TRAITS_ALL(createFuncWrap) \
		CREATE_MEM_FUNC_TRAITS(createFuncWrap, __stdcall) \
		CREATE_MEM_FUNC_TRAITS(createFuncWrap, __cdecl) \
		CREATE_MEM_FUNC_TRAITS(createFuncWrap, __fastcall) \
		CREATE_MEM_FUNC_TRAITS(createFuncWrap, __vectorcall) \
		CREATE_MEM_FUNC_TRAITS(createFuncWrap, __thiscall) //\
		CREATE_MEM_FUNC_TRAITS(createFuncWrap, __clrcall)
#endif // !_WIN64


#define CONSTRUCTOR_MEM_FUNC_IMPL(callConv, callerConst, callerType, constQualifier) \
	template<typename _RetType, typename _ClassType, typename... _tArgs>\
	Function(callerConst _ClassType callerType classObj, _RetType (callConv _ClassType::*classFuncPtr)(_tArgs...) constQualifier) \
	{ \
		typedef callerConst _ClassType callerType _ClassObjType; \
		typedef _RetType (callConv _ClassType::*_ClassFuncPtrType)(_tArgs...) constQualifier; \
		Set(std::forward<_ClassObjType>(classObj), std::forward<_ClassFuncPtrType>(classFuncPtr)); \
	}


template<typename _FuncPtrType>
class Function : public _FunctionTraits<_FuncPtrType>::InterfaceType
{
	typedef typename _FunctionTraits<_FuncPtrType>::InterfaceType _MyBase;
	typedef Function<_FuncPtrType> _MyType;

public:
	Function() {}

	Function(const _MyType& rhs) :
		_MyBase(rhs)
	{
	}

	Function(_MyType& rhs) :
		_MyBase((const _MyType&)rhs)
	{
	}

	Function(_MyType&& rhs) :
		_MyBase(std::forward<_MyType>(rhs))
	{
	}

	explicit Function(nullptr_t){}

	explicit Function(const StaticFunction<_FuncPtrType>& staticFuncPtr)
	{
		Set(std::forward<StaticFunction<_FuncPtrType>::PointerType>(staticFuncPtr.m_pFunc));
	}

	explicit Function(StaticFunction<_FuncPtrType>& staticFuncPtr)
	{
		Set(std::forward<StaticFunction<_FuncPtrType>::PointerType>(staticFuncPtr.m_pFunc));
	}

	template<typename _ClassName>
	explicit Function(const MemberFunction<_ClassName, _FuncPtrType>& memberFuncPtr)
	{
		Set(std::forward<_ClassName*>(memberFuncPtr.m_pInvokingObject), std::forward<typename MemberFunction<_ClassName, _FuncPtrType>::_MyBase::PointerType>(memberFuncPtr.m_pFunc));
	}

	template<typename _ClassName>
	explicit Function(MemberFunction<_ClassName, _FuncPtrType>& memberFuncPtr)
	{
		Set(std::forward<_ClassName*>(memberFuncPtr.m_pInvokingObject), std::forward<typename MemberFunction<_ClassName, _FuncPtrType>::_MyBase::PointerType>(memberFuncPtr.m_pFunc));
	}

	template<typename funcPtrType>
	Function(funcPtrType& funcPtr)
	{
		Set(std::forward<funcPtrType>(funcPtr));
	}

CREATE_MEM_FUNC_TRAITS_ALL( CONSTRUCTOR_MEM_FUNC_IMPL )

	_MyType& operator=(const _MyType& rhs)
	{
		_MyBase::operator=(rhs);
		return *this;
	}

	_MyType& operator=(_MyType& rhs)
	{
		_MyBase::operator=((const _MyType&)rhs);
		return *this;
	}

	_MyType& operator=(_MyType&& rhs)
	{
		_MyBase::operator=(std::move(rhs));
		return *this;
	}

	_MyType& operator=(const StaticFunction<_FuncPtrType>& staticFuncPtr)
	{
		Set(std::forward<StaticFunction<_FuncPtrType>::PointerType>(staticFuncPtr.m_pFunc));
		return *this;
	}

	_MyType& operator=(StaticFunction<_FuncPtrType>& staticFuncPtr)
	{
		Set(std::forward<StaticFunction<_FuncPtrType>::PointerType>(staticFuncPtr.m_pFunc));
		return *this;
	}

	template<typename _ClassName>
	_MyType& operator=(const MemberFunction<_ClassName, _FuncPtrType>& memberFuncPtr)
	{
		Set(std::forward<_ClassName*>(memberFuncPtr.m_pInvokingObject), std::forward<typename MemberFunction<_ClassName, _FuncPtrType>::_MyBase::PointerType>(memberFuncPtr.m_pFunc));
		return *this;
	}

	template<typename _ClassName>
	_MyType& operator=(MemberFunction<_ClassName, _FuncPtrType>& memberFuncPtr)
	{
		Set(std::forward<_ClassName*>(memberFuncPtr.m_pInvokingObject), std::forward<typename MemberFunction<_ClassName, _FuncPtrType>::_MyBase::PointerType>(memberFuncPtr.m_pFunc));
		return *this;
	}

	template<typename funcPtrType>
	_MyType& operator=(funcPtrType&& funcPtr)
	{
		Set(std::forward<funcPtrType>(funcPtr));
		return *this;
	}

	_MyType& operator=(nullptr_t)
	{
		Set(nullptr);
		return *this;
	}
};

#pragma warning(default : 4521) // multiple copy constructors specified
#pragma warning(default : 4522) // multiple assignment operators specified

#undef CONSTRUCTOR_MEM_FUNC_IMPL
#undef CREATE_MEM_FUNC_TRAITS_ALL
#undef CREATE_MEM_FUNC_TRAITS

} // namespace recon

#endif // _RECON_FUNCTION_H_
