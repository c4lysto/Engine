#include "LinearMemoryPool.h"

namespace recon
{

LinearMemoryPool::LinearMemoryPool() :
	m_pPool(nullptr),
	m_MemoryAllocatedSize(0),
	m_PoolSize(0)
{

}

LinearMemoryPool::LinearMemoryPool(size_t poolSize) :
	m_pPool(nullptr),
	m_MemoryAllocatedSize(0),
	m_PoolSize(0)
{
	Init(poolSize);
}

LinearMemoryPool::~LinearMemoryPool()
{
	Shutdown();
}

void LinearMemoryPool::Init(size_t poolSize)
{
	void* pNewPool = _aligned_malloc(poolSize, 16);//new u8[poolSize];
	Assertf(pNewPool, "Failed To Allocate New Linear Memory Pool, Alloc Size: %d", poolSize);

	if(pNewPool)
	{
		void* pOldPool = m_pPool;

		m_MemoryAllocatedSize = 0;
		m_PoolSize = poolSize;
		m_pPool = (u8*)pNewPool;

		//delete[] pOldPool;
		_aligned_free(pOldPool);
	}
}

void LinearMemoryPool::Shutdown()
{
	m_PoolSize = 0;
	m_MemoryAllocatedSize = 0;

	//delete[] m_pPool;
	_aligned_free(m_pPool);
	m_pPool = nullptr;
}

void LinearMemoryPool::Reset()
{
	m_MemoryAllocatedSize = 0;
}

void* LinearMemoryPool::Allocate(size_t allocSize, size_t alignment /*= 16*/)
{
	Assertf(alignment == 1 || (alignment & (alignment - 1)) == 0, "Alignment Must Be A Power Of 2!");

	// Align All Alloc Sizes to 16-Bytes
	// We can adjust to the alignment parameter later
	allocSize += 0xF;
	allocSize &= 0xFFFFFFF0;

	size_t alignmentStep = 0;
	if(alignment > 16)
	{
		// NOTE: If it's a power of 2 then it's already guaranteed to be a power of 16
		alignmentStep += alignment - 16;
		allocSize += alignmentStep;
	}

	void* pData = nullptr;

	if(Verifyf(m_pPool, "Linear Memory Pool has not been allocated yet!") && allocSize > 0)
	{
		AtomicSizeT::Type allocationStart = m_MemoryAllocatedSize.FetchAdd(allocSize);

		if(allocationStart < m_PoolSize)
		{
			pData = m_pPool + allocationStart + alignmentStep;

			Assertf(allocationStart + allocSize < m_PoolSize, "Attempting to allocate memory out of bounds of the linear memory pool. Pool Overflow '%d', Max Pool Size: '%d'", (allocationStart + allocSize) - m_PoolSize, m_PoolSize);
		}
#if RECON_ASSERT
		else
		{
			Assertf(false, "Linear Memory Pool Is Full! Current allocation size: '%d', after attempt to allocate '%d' bytes. Max Pool Size: '%d'", allocationStart, allocSize, m_PoolSize);
		}
#endif // RECON_ASSERT
	}

	return pData;
}

} // namespace recon
