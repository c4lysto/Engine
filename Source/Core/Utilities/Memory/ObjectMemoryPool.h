#ifndef _RECON_OBJECT_MEMORY_POOL_H_
#define _RECON_OBJECT_MEMORY_POOL_H_

#include <list>

#include "MemPool.h"
#include "../Mutex.h"

#define REGISTER_OBJ_MEM_POOL(className) \
private: \
	static ObjectMemoryPool<className> ms_##className##_MemPool (TO_STRING(className)); \
public: \
	void* operator new (size_t UNUSED_PARAM(count)) \
	{ \
		return (void*) ms_##className##_MemPool ->Allocate(); \
	} \
	void operator delete(void* pMem) \
	{ \
		if(pMem) ms_##className##_MemPool ->Free((className*)pMem); \
	}

namespace recon
{

template <typename _ObjType>
class ObjectMemoryPool : public IMemPool
{
public:
	typedef _ObjType DataType;

private:
	struct PoolIterator
	{
		union
		{
			_ObjType* pData;
			PoolIterator* pNext;
		};
	};

private:
	std::string m_szPoolName;
	void* m_pPool;
	PoolIterator* m_pHead;
	Mutex m_poolMutex;

#if RECON_ASSERT
	void* m_pPoolEnd;
#endif // 

public:
	explicit ObjectMemoryPool(const char* szPoolName);
	virtual ~ObjectMemoryPool();

	// poolSize: Number Of Objects In The Pool
	void Init(u32 poolSize) override;
	void Shutdown() override;

	_ObjType* Allocate();
	void Free(_ObjType* pObject);

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