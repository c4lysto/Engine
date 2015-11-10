#include "ObjectMemoryPool.h"

#include <malloc.h>

namespace recon
{

ObjectPoolManager::MemoryPoolList ObjectPoolManager::m_MemoryPools;

template<typename _ObjType>
ObjectMemoryPool<_ObjType>::ObjectMemoryPool(const char* szPoolName) :
	m_szPoolName(szPoolName),
	m_pPool(nullptr),
	m_pHead(nullptr)
{
	ObjectPoolManager::RegisterMemoryPool(this);
}

template<typename _ObjType>
ObjectMemoryPool<_ObjType>::~ObjectMemoryPool()
{
	Shutdown();
}

// poolSize: Number Of Objects In The Pool
template<typename _ObjType>
void ObjectMemoryPool<_ObjType>::Init(u32 poolSize)
{
	Assertf(poolSize, "Cannot Allocate A Memory Mool Of Size 0!!!");

	m_pPool = _aligned_malloc(sizeof(_ObjType)*poolSize, alignof(_ObjType));

	InitializeFreeList(poolSize);
}

template<typename _ObjType>
void ObjectMemoryPool<_ObjType>::Shutdown()
{
	if(m_pPool)
	{
		_aligned_free(m_pPool);
		m_pPool = nullptr;
	}

	m_pHead = nullptr;
}

template<typename _ObjType>
_ObjType* ObjectMemoryPool<_ObjType>::Allocate()
{
	AutoMutex(m_poolMutex);

	if(Verifyf(m_pHead, "Object Memory Pool Is Out Of Free Entries! Increase Pool Size!"))
	{
		_ObjType* pObject = m_pHead->pData;

		if(pObject)
		{
			pObject = new (void*)pObject _ObjType();

			m_pHead = m_pHead->pNext;
		}

		return pObject;
	}

	return nullptr;
}

template<typename _ObjType>
void ObjectMemoryPool<_ObjType>::Free(_ObjType* pObject)
{
	if(pObject)
	{
		pObject->~_ObjType();

		PoolIterator* pIter = reinterpret_cast<PoolIterator*>(pObject);

		AutoMutex(m_poolMutex);

		Assertf(pObject >= m_pPool && pObject < m_pPoolEnd, "Trying to Free Memory That Doesn't Exist In This Memory Pool");

		pIter->pNext = m_pHead;
		m_pHead = pIter;
	}
}

template<typename _ObjType>
void ObjectMemoryPool<_ObjType>::InitializeFreeList(u32 objectCount)
{
	AutoMutex(m_poolMutex);

	m_pHead = (PoolIterator*)m_pPool;

	PoolIterator* pCurrNode = m_pHead;
	PoolIterator* pPoolEnd = m_pHead->pData + (sizeof(_ObjType)* objectCount);
	while(true)
	{
		pCurrNode->pNext = (PoolIterator*)((char*)pCurrNode->pData + sizeof(_ObjType));

		if(pCurrNode->pNext == pPoolEnd)
		{
			pCurrNode->pNext = nullptr;
			break;
		}

		pCurrNode = pCurrNode->pNext;
	}

#if RECON_ASSERT
	m_pPoolEnd = pEndNode;
#endif // RECON_ASSERT
}

void ObjectPoolManager::RegisterMemoryPool(IMemPool* pMemPool)
{
	if(Verifyf(pMemPool, "Trying To Register An Invalid Object Memory Pool!"))
	{
		for(MemoryPoolList::const_iterator iter = m_MemoryPools.begin(); iter != m_MemoryPools.end(); ++iter)
		{
			if(pMemPool == *iter)
			{
				return;
			}
		}
	}
}

/*COMMENT(static)*/ void ObjectPoolManager::Init()
{ 
	static u32 defaultSize = 1;
	for(MemoryPoolList::const_iterator iter = m_MemoryPools.begin(); iter != m_MemoryPools.end(); ++iter)
	{
		if(*iter)
		{
			(*iter)->Init(1 * 1000);
		}
	}
}

/*COMMENT(static)*/ void ObjectPoolManager::Shutdown()
{
	for(MemoryPoolList::const_iterator iter = m_MemoryPools.begin(); iter != m_MemoryPools.end(); ++iter)
	{
		if(*iter)
		{
			(*iter)->Shutdown();
		}
	}
}

} // namespace recon