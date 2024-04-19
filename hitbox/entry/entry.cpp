#include "entry.h"

#include "../font/msyh.h"
#include "../font/FontAewsome6.h"
#include "../font/IconsFontAwesome6.inl"
#include "../font/FontAwesome6Brands.h"
#include "../font/IconsFontAwesome6Brands.inl"

#include "../utils/graphics.h"
#include "../controller/dominator.h"
#include "../mapper/mapper.h"
#include "../service/runable.h"

ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
IDXGISwapChain* g_pSwapChain = nullptr;
ID3D11RenderTargetView* g_MainRenderTargetView = nullptr;
HWND g_hUnrealWindow = nullptr;
WNDPROC g_lpOriginalWndproc = nullptr;

dominator* dom = nullptr;
HRESULT(*present)(IDXGISwapChain* This, UINT SyncInterval, UINT Flags) = nullptr;
HRESULT(*resize)(IDXGISwapChain* This, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) = nullptr;

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HRESULT initialize(IDXGISwapChain* This, UINT SyncInterval, UINT Flags);
HRESULT handler(IDXGISwapChain* This, UINT SyncInterval, UINT Flags);
HRESULT change(IDXGISwapChain* This, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
HRESULT reinitialize(IDXGISwapChain* This, UINT SyncInterval, UINT Flags);

HRESULT initialize(IDXGISwapChain* This, UINT SyncInterval, UINT Flags) {
	g_pSwapChain = This;
	g_pSwapChain->GetDevice(__uuidof(g_pd3dDevice), (void**)&g_pd3dDevice);
	g_pd3dDevice->GetImmediateContext(&g_pd3dDeviceContext);
#pragma warning(push)
#pragma warning(disable: 6387)
	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, __uuidof(pBackBuffer), (void**)&pBackBuffer);
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_MainRenderTargetView);
	pBackBuffer->Release();
#pragma warning(pop)

	ImGui::CreateContext();

	dom = dominator::instance();
	dom->hwnd = g_hUnrealWindow;

	ImGuiStyle& style = imgui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = ImColor(36, 40, 49, 255).Value;//±³¾°É«
	style.FrameRounding = 4.0f;//Ô²½Ç

	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(g_hUnrealWindow);
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

	graphics::instance()->hook(handler, nullptr, options::present);
	return present(This, SyncInterval, Flags);
}

HRESULT handler(IDXGISwapChain* This, UINT SyncInterval, UINT Flags) {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	static bool open = true;
	static bool pressed = false;
	short state = GetAsyncKeyState(VK_F1) & 0x8000;
	if (state and !pressed) open = !open;
	pressed = state;

	if (open) {
		dom->principal();
	}

	dom->draw();
	dom->ruler();
	dom->frame();
	ImGui::Render();
	g_pd3dDeviceContext->OMSetRenderTargets(1, &g_MainRenderTargetView, nullptr);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return present(This, SyncInterval, Flags);
}

HRESULT change(IDXGISwapChain* This, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	if (g_pd3dDevice != nullptr) {
		g_pd3dDevice->Release();
		g_pd3dDevice = nullptr;
		g_MainRenderTargetView->Release();
		g_MainRenderTargetView = nullptr;
	}
	ImGui_ImplDX11_Shutdown();
	graphics::instance()->hook(reinitialize, nullptr, options::present);
	return resize(This, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

HRESULT reinitialize(IDXGISwapChain* This, UINT SyncInterval, UINT Flags) {
	g_pSwapChain = This;
	g_pSwapChain->GetDevice(__uuidof(g_pd3dDevice), (void**)&g_pd3dDevice);
	g_pd3dDevice->GetImmediateContext(&g_pd3dDeviceContext);
#pragma warning(push)
#pragma warning(disable: 6387)
	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, __uuidof(pBackBuffer), (void**)&pBackBuffer);
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_MainRenderTargetView);
#pragma warning(pop)

	pBackBuffer->Release();

	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
	graphics::instance()->hook(handler, nullptr, options::present);
	return present(This, SyncInterval, Flags);
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;
	return ::CallWindowProcA(g_lpOriginalWndproc, hWnd, msg, wParam, lParam);
}

bool entry(HMODULE hmodule)
{
	mapper* mapping = mapper::instance();
	if (mapping->initliaze() == false) {
		throw std::exception("mappers initialize failed");
		return false;
	}

	runable* invoke = runable::instance();

	if (invoke->initialize(mapping->uworld, mapping->WorldToScreen) == false) {
		throw std::exception("runable initialize failed");
		return false;
	}

	g_hUnrealWindow = FindWindowA("UnrealWindow", "KOFXV  ");
	g_lpOriginalWndproc = (WNDPROC)SetWindowLongPtr(g_hUnrealWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);
	if (g_lpOriginalWndproc == nullptr) {
		throw std::exception("SetWindowLongPtr failed");
		return false;
	}

	graphics* graphic = graphics::instance();
	if (graphic->initialize(g_hUnrealWindow) == false) {
		throw std::exception("graphics initialize failed");
		return false;
	}

	graphic->hook(initialize, &present, options::present);
	graphic->hook(change, &resize, options::resize);
	return true;
}