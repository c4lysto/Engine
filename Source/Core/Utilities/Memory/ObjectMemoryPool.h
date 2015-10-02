#ifndef _RECON_OBJECT_MEMORY_POOL_H_
#define _RECON_OBJECT_MEMORY_POOL_H_

#include <list>

#include "../UtilitiesInclude.h"

#define REGISTER_MEM_POOL(className) \
private: \
	static ObjectMemoryPool<className, __ALIGNOF(className)> m_##className##_MemPool (TO_STRING(className)); \
public: \
	void* operator new (size_t UNUSED_PARAM(count)) \
	{ \
		return (void*) m_##className##_MemPool ->Allocate(); \
	} \
	void operator delete(void* pMem) \
	{ \
		if(pMem) m_##className##_MemPool ->Free((className*)pMem); \
	}

namespace recon
{

class IMemPool
{
public:
	virtual ~IMemPool() {}

	virtual void Init(u32 poolSize) = 0;
	virtual void Shutdown();
};

template <typename classType>
class ObjectMemoryPool : public IMemPool
{
public:
	typedef classType DataType;

private:
	struct PoolIterator
	{
		union
		{
			classType* pData;
			PoolIterator* pNext;
		};
	};

private:
	std::string m_szPoolName;
	void* m_pPool;
	PoolIterator* m_pHead;

#if RECON_ASSERT
	void* m_pPoolEnd;
#endif // 

public:
	explicit ObjectMemoryPool(const char* szPoolName);
	virtual ~ObjectMemoryPool();

	void Init(u32 poolSize) override;
	void Shutdown() override;

	classType* Allocate();
	void Free(classType* pObject);

private:
	void InitializeFreeList(u32 objectCount);
};

class ObjectPoolManager
{
public:
	typedef std::list<IMemPool*> MemoryPoolList;

private:
	static MemoryPoolList m_MemoryPools;

public:
	static void RegisterMemoryPool(IMemPool* pMemPool);

	static void Init();
	static void Shutdown();

};

} // namespace recon

#endif // _RECON_OBJECT_MEMORY_POOL_H_