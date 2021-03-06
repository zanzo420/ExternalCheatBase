#include "HaxAppMain.h"
#include "../HaxEngine/HaxApp.h"

#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "dbghelp.lib")
#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "winmm.lib")

#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "d3d_x86/d3d9.lib")
#pragma comment(lib, "d3d_x86/d3dx9.lib")

HINSTANCE g_hInstance = nullptr;
extern std::shared_ptr <CROS_ESP_Hax> g_pROSHax;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR CmdLine, int CmdShow)
{
	g_hInstance = hInstance;

	// Initialize hax app
	auto pHaxApp = std::make_shared<CHaxApp>("ros.exe");

	if (pHaxApp == nullptr || pHaxApp.get() == nullptr)
	{
		OutputDebugStringA(XOR("App Init fail!\n"));
		abort();
		return 0;
	}

	// Initialize hax engine
	auto pHaxEngine = std::make_unique<CHaxEngine>(GAME_CODE_ROS);

	if (pHaxEngine == nullptr || pHaxEngine.get() == nullptr)
	{
		OutputDebugStringA(XOR("Engine Init fail!\n"));
		abort();
		return 0;
	}

	// Init hax class
	g_pROSHax = std::make_shared<CROS_ESP_Hax>();

	if (g_pROSHax == nullptr || g_pROSHax.get() == nullptr)
	{
		OutputDebugStringA(XOR("Hax class Init fail!\n"));
		abort();
		return 0;
	}

	// Register hax app from static library
	pHaxEngine->RegisterHaxApp(pHaxApp);

	// Hax app init routine
	pHaxApp->PreInitialize();
	pHaxApp->Initialize(std::bind(&CHaxEngine::OnAppNotification, pHaxEngine.get(), std::placeholders::_1));

#ifdef _DEBUG
	printf(XOR(" # PROCESS WORK COMPLETED! # \n"));
	getchar();
#endif

    return 0;
}

