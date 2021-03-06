#include "ObjectMemoryPool.h"

#include <malloc.h>

namespace recon
{

ObjectPoolManager::MemoryPoolList ObjectPoolManager::m_MemoryPools;

template<typename _ClassType>
ObjectMemoryPool<_ClassType>::ObjectMemoryPool(const char* szPoolName) :
	m_szPoolName(szPoolName),
	m_pPool(nullptr),
	m_pHead(nullptr)
{
	ObjectPoolManager::RegisterMemoryPool(this);
}

template<typename _ClassType>
ObjectMemoryPool<_ClassType>::~ObjectMemoryPool()
{
	Shutdown();
}

template<typename _ClassType>
void ObjectMemoryPool<_ClassType>::Init(u32 poolSize)
{
	Assertf(poolSize, "Cannot Allocate A Memory Mool Of Size 0!!!");

	u32 objectCount = poolSize / sizeof(_ClassType);
	objectCount += (u32)((poolSize % objectCount) != 0);

	m_pPool = _aligned_malloc(sizeof(_ClassType)*objectCount, __alignof(_ClassType));

	InitializeFreeList(objectCount);
}

template<typename _ClassType>
void ObjectMemoryPool<_ClassType>::Shutdown()
{
	if(m_pPool)
	{
		_aligned_free(m_pPool);
		m_pPool = nullptr;
	}
}

template<typename _ClassType>
_ClassType* ObjectMemoryPool<_ClassType>::Allocate()
{
	if(Verifyf(m_pHead, "Object Memory Pool Is Out Of Free Entries! Increase Pool Size!"))
	{
		_ClassType* pObject = m_pHead->pData;

		if(pObject)
		{
			pObject = new (void*)pObject _ClassType();

			m_pHead = m_pHead->pNext;
		}

		return pObject;
	}

	return nullptr;
}

template<typename _ClassType>
void ObjectMemoryPool<_ClassType>::Free(_ClassType* pObject)
{
	if(pObject)
	{
		Assertf(pObject >= m_pPool && pObject < m_pPoolEnd, "Trying to Free Memory That Doesn't Exist In This Memory Pool");

		pObject->~_ClassType();

		PoolIterator* pIter = reinterpret_cast<PoolIterator*>(pObject);

		pIter->pNext = m_pHead;
		m_pHead = pIter;
	}
}

template<typename _ClassType>
void ObjectMemoryPool<_ClassType>::InitializeFreeList(u32 objectCount)
{
	m_pHead = (PoolIterator*)m_pPool;

	PoolIterator* pCurrNode = m_pHead;
	PoolIterator* pPoolEnd = m_pHead->pData + objectCount;
	while(true)
	{
		pCurrNode->pNext = (PoolIterator*)(pCurrNode->pData + 1);

		if(pCurrNode->pNext == m_pPoolEnd)
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