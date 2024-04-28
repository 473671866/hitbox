#include "graphics.h"

bool graphics::initialize(HWND hwnd)
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	UINT createDeviceFlags = 0;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &chain, NULL, &featureLevel, NULL) != S_OK) {
		return false;
	}

	virtual_table = *reinterpret_cast<void***>(chain);
	return true;
}

bool graphics::attach(void* handler, void* original, options op) {
	if (original == nullptr) {
		return false;
	}

	if (virtual_table == nullptr || handler == nullptr) {
		return false;
	}

	unsigned long protect = 0;
	if (!VirtualProtect(virtual_table, 1, PAGE_EXECUTE_READWRITE, &protect)) {
		return false;
	}

	int index = static_cast<int>(op);
	*reinterpret_cast<void**>(original) = virtual_table[index];
	virtual_table[index] = handler;
	VirtualProtect(virtual_table, 1, protect, &protect);
	return true;
}