#include "entry.h"
#include "../mapper/mapper.h"

#include "../service/runable.h"

#include "../context/configuration.h"

#include "../controller/renderer.h"
#include "../controller/dominator.h"

#include "../utils/graphics.h"
#include "../utils/logger.hpp"

#include "../font/alifont.hpp"
#include "../font/FontAewsome6.h"
#include "../font/IconsFontAwesome6.inl"
#include "../font/FontAwesome6Brands.h"
#include "../font/IconsFontAwesome6Brands.inl"

ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
IDXGISwapChain* g_pSwapChain = nullptr;
ID3D11RenderTargetView* g_MainRenderTargetView = nullptr;
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
#pragma warning(push)
#pragma warning(disable: 6387)
	ID3D11Texture2D* pBackBuffer;
	g_pSwapChain->GetBuffer(0, __uuidof(pBackBuffer), (void**)&pBackBuffer);
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_MainRenderTargetView);
	pBackBuffer->Release();
#pragma warning(pop)

	ImGui::CreateContext();

	ImGuiIO& io = imgui::GetIO();
	float font_size = 16.0f;
	float icon_size = font_size * 2.0f / 3.0f;

	ImFontConfig ifc;
	ifc.FontDataOwnedByAtlas = false;
	configurs::font_ali = io.Fonts->AddFontFromMemoryTTF((void*)alifont_data, alifont_size, 17.0f, &ifc, io.Fonts->GetGlyphRangesChineseFull());

	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA,0 };
	ImFontConfig icons_config;
	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	icons_config.GlyphMinAdvanceX = icon_size;
	configurs::icon_awesmoe = io.Fonts->AddFontFromMemoryTTF(FontAewsome6, sizeof(FontAewsome6), icon_size, &icons_config, icons_ranges);
	configurs::icon_brands = io.Fonts->AddFontFromMemoryTTF(FontAwesome6Brands, sizeof(FontAwesome6Brands), 30.0f, &icons_config, icons_ranges);

	ImGuiStyle& style = imgui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = ImColor(36, 40, 49, 255).Value;//±³¾°É«
	style.FrameRounding = 4.0f;//Ô²½Ç

	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(configurs::unrealwindow);
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

	graphics::instance()->attach(handler, nullptr, options::present);
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
		dominator dom;
		dom.window();
	}

	renderer render;
	render.render();

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
	graphics::instance()->attach(reinitialize, nullptr, options::present);
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
	graphics::instance()->attach(handler, nullptr, options::present);
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

	configurs::unrealwindow = FindWindowA("UnrealWindow", "KOFXV  ");
	g_lpOriginalWndproc = (WNDPROC)SetWindowLongPtr(configurs::unrealwindow, GWLP_WNDPROC, (LONG_PTR)WndProc);
	if (g_lpOriginalWndproc == nullptr) {
		throw std::exception("SetWindowLongPtr failed");
		return false;
	}

	graphics* graphic = graphics::instance();
	if (graphic->initialize(configurs::unrealwindow) == false) {
		throw std::exception("graphics initialize failed");
		return false;
	}

	loggers::initialize();
	graphic->attach(initialize, &present, options::present);
	graphic->attach(change, &resize, options::resize);
	return true;
}