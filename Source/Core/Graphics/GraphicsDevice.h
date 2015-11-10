#ifndef _RECON_GRAPHICSDEVICE_H_
#define _RECON_GRAPHICSDEVICE_H_

#include "../Utilities/UtilitiesInclude.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#include <d3d12.h>
#include <dxgi1_4.h>

namespace recon
{

	class GraphicsDevice
	{
	private:
		// We can actually have more than 2 may want to look into making this better in the future
		static const u32 ms_FrameCount = 2;

	private:
		ID3D12Device* m_pDevice = nullptr;
		ID3D12CommandQueue* m_pCommandQueue = nullptr;
		IDXGISwapChain3* m_pSwapChain = nullptr;
		ID3D12DescriptorHeap* m_pRTVHeap = nullptr;
		ID3D12Resource* m_pRenderTargets[ms_FrameCount];
		ID3D12CommandAllocator* m_pCommandAllocators[ms_FrameCount];
		ID3D12GraphicsCommandList* m_pGraphicsCommandList = nullptr;
		ID3D12Fence* m_pRenderFence = nullptr;
		HANDLE m_pRenderFenceEvent = nullptr;

		u64 m_FrameCount = 0;
		u32 m_FrameIndex = 0;

	private:
		static GraphicsDevice* ms_Instance;

	public:
		static void CreateInstance();
		static void DestroyInstance();
		static GraphicsDevice* GetInstance() { Assert(ms_Instance); return ms_Instance; }

	public:
		GraphicsDevice();
		~GraphicsDevice();

		void Init(u32 screenWidth, u32 screenHeight);
		void Shutdown();

		void PreBuildCommandLists();
		void PostBuildCommandLists();

		void BeginFrame();
		void ExecuteFrame();
		void EndFrame();
	};

} // namespace recon

#endif // _RECON_GRAPHICSDEVICE_H_