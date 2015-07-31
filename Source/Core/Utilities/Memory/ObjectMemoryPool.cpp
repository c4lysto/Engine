#include "ObjectMemoryPool.h"

#include <malloc.h>

namespace recon
{

ObjectPoolManager::MemoryPoolList ObjectPoolManager::m_MemoryPools;

template<typename classType, u8 alignment>
ObjectMemoryPool<classType, alignment>::ObjectMemoryPool(const char* szPoolName) : 
	m_szPoolName(szPoolName),
	m_pPool(nullptr),
	m_pHead(nullptr)
{
	ObjectPoolManager::RegisterMemoryPool(this);
}

template<typename classType, u8 alignment>
ObjectMemoryPool<classType, alignment>::~ObjectMemoryPool()
{
	Shutdown();
}

template<typename classType, u8 alignment>
void ObjectMemoryPool<classType, alignment>::Init(u32 poolSize)
{
	Assert(poolSize, "Cannot Allocate A Memory Mool Of Size 0!!!");

	u32 objectCount = poolSize / sizeof(classType);
	objectCount += (u32)((poolSize % objectCount) != 0);

	m_pPool = _aligned_malloc(sizeof(classType)*objectCount, alignment);

	InitializeFreeList(objectCount);
}

template<typename classType, u8 alignment>
void ObjectMemoryPool<classType, alignment>::Shutdown()
{
	if(m_pPool)
	{
		_aligned_free(m_pPool);
		m_pPool = nullptr;
	}
}

template<typename classType, u8 alignment>
classType* ObjectMemoryPool<classType, alignment>::Allocate()
{
	if(Verify(m_pHead, "Object Memory Pool Is Out Of Free Entries! Increase Pool Size!"))
	{
		classType* pObject = m_pHead->pData;

		if(pObject)
		{
			pObject = new (void*)pObject classType();

			m_pHead = m_pHead->pNext;
		}

		return pObject;
	}

	return nullptr;
}

template<typename classType, u8 alignment>
void ObjectMemoryPool<classType, alignment>::Free(classType* pObject)
{
	if(pObject)
	{
		Assert(pObject >= m_pPool && pObject < m_pPoolEnd, "Trying to Free Memory That Doesn't Exist In This Memory Pool");

		pObject->~classType();

		PoolIterator* pIter = reinterpret_cast<PoolIterator*>(pObject);

		pIter->pNext = m_pHead;
		m_pHead = pIter;
	}
}

template<typename classType, u8 alignment>
void ObjectMemoryPool<classType, alignment>::InitializeFreeList(u32 objectCount)
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

#if __ASSERT
	m_pPoolEnd = pEndNode;
#endif // __ASSERT
}

void ObjectPoolManager::RegisterMemoryPool(IMemPool* pMemPool)
{
	if(Verify(pMemPool, "Trying To Register An Invalid Object Memory Pool!"))
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