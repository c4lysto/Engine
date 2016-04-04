#ifndef _RECON_LINEARMEMORYPOOL_H_
#define _RECON_LINEARMEMORYPOOL_H_

#include "MemPool.h"

#include "../Atomic.h"

namespace recon
{

class LinearMemoryPool
{
private:
	u8* m_pPool;
	AtomicSizeT m_MemoryAllocatedSize;
	size_t m_PoolSize;

public:
	LinearMemoryPool();
	LinearMemoryPool(size_t poolSize);

	~LinearMemoryPool();

	void Init(size_t poolSize);
	void Shutdown();

	void Reset();

	// Allocate uses atomic operations and IS thread safe
	void* Allocate(size_t allocSize, size_t alignment = 16);
	
	template<typename _ObjType>
	void* Allocate() { return Allocate(sizeof(_ObjType), __alignof(_ObjType)); }

};

} // namespace recon

#endif // _RECON_LINEARMEMORYPOOL_H_
