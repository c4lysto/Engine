#ifndef _RECON_MEM_POOL_H_
#define _RECON_MEM_POOL_H_

#include "../UtilitiesInclude.h"

namespace recon
{

class IMemPool
{
public:
	virtual ~IMemPool() {}

	virtual void Init(u32 poolSize) = 0;
	virtual void Shutdown() = 0;
};

} // namespace recon

#endif // _RECON_MEM_POOL_H_