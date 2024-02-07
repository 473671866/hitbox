#include "entry.h"
#include "../imgui/alifont.hpp"

ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
IDXGISwapChain* g_pSwapChain = nullptr;
ID3D11RenderTargetView* g_MainRenderTargetView = nullptr;
HWND g_hUnrealWindow = nullptr;
WNDPROC g_lpOriginalWndproc = nullptr;

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

	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, __uuidof(pBackBuffer), (void**)&pBackBuffer);
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_MainRenderTargetView);
	pBackBuffer->Release();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImFontConfig ifc;
	ifc.FontDataOwnedByAtlas = false;
	io.Fonts->AddFontFromMemoryTTF((void*)alifont_data, alifont_size, 18.0f, &ifc, io.Fonts->GetGlyphRangesChineseFull());
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
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

	draws* draw = draws::instance();
	if (open) {
		ImGui::Begin("hitbox");
		draw->menus();
		ImGui::End();
	}

	draw->draw();
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

	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, __uuidof(pBackBuffer), (void**)&pBackBuffer);
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_MainRenderTargetView);
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

void entry(HMODULE hmodule) {
	mappers* mapper = mappers::instance();
	if (mapper->initliaze() == false) {
		MessageBoxA(nullptr, "mappers initialize failed", "warning", MB_OK);
		return;
	}

	services* service = services::instance();
	if (service->initliaze(mapper) == false) {
		MessageBoxA(nullptr, "services initialize failed", "warning", MB_OK);
		return;
	}

	draws* draw = draws::instance();
	if (draw->initialize(service, mapper) == false) {
		MessageBoxA(nullptr, "draws initialize failed", "warning", MB_OK);
		return;
	}

	g_hUnrealWindow = FindWindowA("UnrealWindow", "KOFXV  ");
	graphics* graphic = graphics::instance();
	if (graphic->initialize(g_hUnrealWindow) == false) {
		MessageBoxA(nullptr, "graphics initialize failed", "warning", MB_OK);
		return;
	}

	graphic->hook(initialize, &present, options::present);
	graphic->hook(change, &resize, options::resize);
	g_lpOriginalWndproc = (WNDPROC)SetWindowLongPtr(g_hUnrealWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);
	if (g_lpOriginalWndproc == nullptr) {
		int error = GetLastError();
		char buffer[512]{};
		sprintf(buffer, "error code: %d", error);
		MessageBoxA(nullptr, buffer, "warning", MB_OK);
		return;
	}
	return;
}