#include <array>
#include <fstream>

#include "StdAfx.h"
#include "GSDXLoader.h"

#undef ERROR

extern void execGs2(GSDX* g);

static inline const wchar_t* getLevelLogger(unsigned char level)
{
	switch (level)
	{
	case GSDX_LOG_LEVEL_DEBUG:
		return L"DEBUG";
	case GSDX_LOG_LEVEL_ERROR:
		return L"ERROR";
	case GSDX_LOG_LEVEL_INFO:
		return L"INFO";
	default:
		break;
	}

	return L"UNKNOWN";
}

static void CALLBACK stdioLogger(unsigned char level, const wchar_t* format, ...)
{
#ifndef _DEBUG
	if (level == GSDX_LOG_LEVEL_DEBUG)
		return;
#endif

	va_list va;

	va_start(va, format);

	wprintf(L"LOG %s ", getLevelLogger(level));
	vwprintf(format, va);
	wprintf(L"\n");

	va_end(va);
}

#define INFO(fmt, ...) stdioLogger(GSDX_LOG_LEVEL_INFO, L#fmt, ##__VA_ARGS__)
#define ERROR(fmt, ...) stdioLogger(GSDX_LOG_LEVEL_ERROR, L#fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) stdioLogger(GSDX_LOG_LEVEL_DEBUG, L#fmt, ##__VA_ARGS__)

/*static LRESULT CALLBACK DummyMessageBox(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, Msg, wParam, lParam);
}*/

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(nCmdShow);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(hPrevInstance);

	if (!AllocConsole())
	{
		MessageBox(nullptr, L"AllocConsole failed", L"Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	FILE* fpd = nullptr;
	freopen_s(&fpd, "CONOUT$", "w", stdout);

	GSDX gsdx;
	
	gsdx.log = stdioLogger;

	if (!gsdx.LoadLibraryW(L"GSdx32-AVX2.dll"))
	{
		return 0;
	}

#if 0 // Shows some information of GSDX
	wchar_t buf[2048];
	_snwprintf_s(buf, _countof(buf), L"CPU %u LibName %S LibType %u Version %u", gsdx.getCpuPlatform(), gsdx.getLibName(), gsdx.getLibType(), gsdx.getLibVersion2(0));
	MessageBoxW(nullptr, buf, L"GSDX Info", MB_OK);
#endif

	if (gsdx.test() != 0)
	{
		ERROR(GSdx32 AVX2 support: fail);
		return -1;
	}

	INFO(GSdx32 AVX2 support: yes);

#if 0 // Shows the configuration screen of GSDX
	gsdx.configure();
#endif

	if (gsdx.init() != 0)
	{
		ERROR(GSDX32 Init failed);
		return 0;
	}

	HWND gsHwnd;
	if (gsdx.open(&gsHwnd, "G S D X 3 2", 1) != 0)
	{
		gsdx.shutdown();
		ERROR(GSDX32 Open failed);
		return 0;
	}

	execGs2(&gsdx);

	MSG msg = { 0 };

	while (msg.message != WM_CLOSE && msg.message != WM_DESTROY)
	{
		if (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	// Shutdown GSDX
	gsdx.close(); 
	gsdx.shutdown();

	FreeConsole();

	return 0;
}
