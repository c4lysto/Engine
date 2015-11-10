#include "GraphicsDevice.h"

#include "../Application/AppEntryPoint.h"
#include "../Application/AppWindow_Windows.h"

namespace recon
{

GraphicsDevice* GraphicsDevice::ms_Instance = nullptr;

void GraphicsDevice::CreateInstance()
{
	if(Verify(!ms_Instance))
	{
		ms_Instance = new GraphicsDevice();
	}
}

void GraphicsDevice::DestroyInstance()
{
	if(ms_Instance)
	{
		delete ms_Instance;
		ms_Instance = nullptr;
	}
}

GraphicsDevice::GraphicsDevice()
{
	for(int i = 0; i < ms_FrameCount; ++i)
	{
		m_pRenderTargets[i] = nullptr;
		m_pCommandAllocators[i] = nullptr;
	}
}

GraphicsDevice::~GraphicsDevice()
{
	Shutdown();
}

void GraphicsDevice::Init(u32 screenWidth, u32 screenHeight)
{
#define GRAPHICSINIT_ON_FAILED(failCondition, errorMessage, ...) \
	do { \
		if(failCondition) \
		{ \
			Assertf(false, errorMessage, __VA_ARGS__); \
			return; \
		} \
	} while(0)

	HRESULT hr;

#if RECON_DEBUG
	ID3D12Debug* debugInterface;
	hr = D3D12GetDebugInterface(__uuidof(ID3D12Debug), (void**)&debugInterface);
	if(Verifyf(SUCCEEDED(hr), "Failed To Create Graphics Debug Interface! Error Code: '%d'", hr))
	{
		debugInterface->EnableDebugLayer();
	}
#endif // RECON_DEBUG

	hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), (void**)&m_pDevice);
	GRAPHICSINIT_ON_FAILED(FAILED(hr), "Failed To Create D3D12 Device! Error Code: '%d'", hr);

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	hr = m_pDevice->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), (void**)&m_pCommandQueue);
	GRAPHICSINIT_ON_FAILED(FAILED(hr), "Failed To Create D3D12 Command Queue! Error Code: '%d'", hr);

	// NOTE:	rasterTek does a bunch of extra stuff here before creating the swap chain
	//			to potentially help performance? But the Directx 12 Samples don't do this.
	//			may want to investigate in the future

	IDXGIFactory4* pFactory = nullptr;
	hr = CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&pFactory);
	GRAPHICSINIT_ON_FAILED(FAILED(hr), "Failed To Create DXGI Factory! Error Code: '%d'", hr);

	HWND hWnd = ((AppWindow_Windows*)AppEntryPoint::GetWindow())->GetWindowHandle();

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = ms_FrameCount;
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.Windowed = TRUE;

	// Multisampling
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	// Flags
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;

	IDXGISwapChain* pSwapChain = nullptr;
	hr = pFactory->CreateSwapChain(m_pCommandQueue, &swapChainDesc, &pSwapChain);
	GRAPHICSINIT_ON_FAILED(FAILED(hr), "Failed To Create Swap Chain! Error Code: '%d'", hr);

	hr = pSwapChain->QueryInterface(__uuidof(IDXGISwapChain3), (void**)&m_pSwapChain);
	GRAPHICSINIT_ON_FAILED(FAILED(hr), "Failed To Create Swap Chain 3! Error Code: '%d'", hr);

	// We're done with the factory
	pFactory->Release();
	pFactory = nullptr;

	m_FrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();


	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = ms_FrameCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	hr = m_pDevice->CreateDescriptorHeap(&rtvHeapDesc, __uuidof(ID3D12DescriptorHeap), (void**)&m_pRTVHeap);
	GRAPHICSINIT_ON_FAILED(FAILED(hr), "Failed To Create RTV Descriptor Heap! Error Code: '%d'", hr);

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_pRTVHeap->GetCPUDescriptorHandleForHeapStart();
	u32 rtvHeapIncSize = m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	for(int i = 0; i < ms_FrameCount; ++i)
	{
		hr = m_pSwapChain->GetBuffer(i, __uuidof(ID3D12Resource), (void**)&m_pRenderTargets[i]);
		GRAPHICSINIT_ON_FAILED(FAILED(hr), "Failed To Get RTV (%d) From Swap Chain! Error Code: '%d'", i, hr);

		m_pDevice->CreateRenderTargetView(m_pRenderTargets[i], nullptr, rtvHandle);
		rtvHandle.ptr += rtvHeapIncSize;

		hr = m_pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&m_pCommandAllocators[i]);
		GRAPHICSINIT_ON_FAILED(FAILED(hr), "Failed To Create GPU Command Allocator! Error Code: '%d'", i, hr);
	}

	// Will want to move this to another class once multithreaded rendering is supported
	hr = m_pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_pCommandAllocators[0], nullptr, __uuidof(ID3D12GraphicsCommandList), (void**)&m_pGraphicsCommandList);
	GRAPHICSINIT_ON_FAILED(FAILED(hr), "Failed To Create GPU Command Allocator! Error Code: '%d'", hr);

	hr = m_pGraphicsCommandList->Close();
	GRAPHICSINIT_ON_FAILED(FAILED(hr), "Failed To Close Graphics Command List! Error Code: '%d'", hr);

	hr = m_pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, __uuidof(ID3D12Fence), (void**)&m_pRenderFence);
	GRAPHICSINIT_ON_FAILED(FAILED(hr), "Failed To Create Render Fence! Error Code: '%d'", hr);

	m_pRenderFenceEvent = CreateEvent(nullptr, false, false, nullptr);
	GRAPHICSINIT_ON_FAILED(m_pRenderFenceEvent == nullptr, "Failed To Create Render Fence Event! Error Code: '%d'", GetLastError());

#undef GRAPHICSINIT_ON_FAILED
}

void GraphicsDevice::Shutdown()
{
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pCommandQueue);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pRTVHeap);
	SAFE_RELEASE(m_pGraphicsCommandList);
	SAFE_RELEASE(m_pRenderFence);

	CloseHandle(m_pRenderFenceEvent);

	for(int i = 0; i < ms_FrameCount; ++i)
	{
		SAFE_RELEASE(m_pRenderTargets[i]);
		SAFE_RELEASE(m_pCommandAllocators[i]);
	}
}

void GraphicsDevice::PreBuildCommandLists()
{
	m_pCommandAllocators[m_FrameIndex]->Reset();

	m_pGraphicsCommandList->Reset(m_pCommandAllocators[m_FrameIndex], nullptr);

	D3D12_RESOURCE_BARRIER backBufferBarrier = {};
	backBufferBarrier.Transition.pResource = m_pRenderTargets[m_FrameIndex];
	backBufferBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	backBufferBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	backBufferBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

	m_pGraphicsCommandList->ResourceBarrier(1, &backBufferBarrier);

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_pRTVHeap->GetCPUDescriptorHandleForHeapStart();
	if(m_FrameIndex == 1)
	{
		rtvHandle.ptr += m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	m_pGraphicsCommandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);

	FLOAT color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_pGraphicsCommandList->ClearRenderTargetView(rtvHandle, color, 0, nullptr);
}

void GraphicsDevice::PostBuildCommandLists()
{
	D3D12_RESOURCE_BARRIER presentBarrier = {};
	presentBarrier.Transition.pResource = m_pRenderTargets[m_FrameIndex];
	presentBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	presentBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	presentBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

	m_pGraphicsCommandList->ResourceBarrier(1, &presentBarrier);

	m_pGraphicsCommandList->Close();
}

void GraphicsDevice::BeginFrame()
{

}

void GraphicsDevice::ExecuteFrame()
{
	ID3D12CommandList* pCommandLists[] = { m_pGraphicsCommandList };
	m_pCommandQueue->ExecuteCommandLists(NUMELEM(pCommandLists), pCommandLists);
}

void GraphicsDevice::EndFrame()
{
	u32 bVsync = true;
	m_pSwapChain->Present(bVsync, 0);

	const u64 currFrameCount = m_FrameCount;
	m_pCommandQueue->Signal(m_pRenderFence, m_FrameCount);
	++m_FrameCount;

	m_FrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();

	if(m_pRenderFence->GetCompletedValue() < currFrameCount)
	{
		m_pRenderFence->SetEventOnCompletion(currFrameCount, m_pRenderFenceEvent);
		WaitForSingleObject(m_pRenderFenceEvent, INFINITE);
	}
}

} // namespace recon