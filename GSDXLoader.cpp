#include "StdAfx.h"
#include "GSDXLoader.h"

GSDX::GSDX() :
	DLLHandle(nullptr),
	log(nullptr),

	// GS
	osdLog(nullptr),
	osdMonitor(nullptr),
	open(nullptr),
	open2(nullptr),
	vsync(nullptr),
	gifTransfer(nullptr),
	gifTransfer1(nullptr),
	gifTransfer2(nullptr),
	gifTransfer3(nullptr),
	gifSoftReset(nullptr),
	readFIFO(nullptr),
	readFIFO2(nullptr),
	initReadFIFO(nullptr),
	initReadFIFO2(nullptr),
	getTitleInfo2(nullptr),
	irqCallback(nullptr),
	setBaseMem(nullptr),
	setGameCRC(nullptr),
	setFrameSkip(nullptr),
	setVsync(nullptr),
	setExclusive(nullptr),
	setupRecording(nullptr),
	reset(nullptr),
	writeCSR(nullptr),
	makeSnapshot(nullptr),
	about(nullptr),
	Benchmark(nullptr),
	close(nullptr),
	configure(nullptr),
	freeze(nullptr),
	getLastTag(nullptr),
	init(nullptr),
	keyEvent(nullptr),
	Replay(nullptr),
	setSettingsDir(nullptr),
	shutdown(nullptr),
	test(nullptr),

	// PS2E
	getLibName(nullptr),
	getLibType(nullptr),
	getLibVersion2(nullptr),
	getCpuPlatform(nullptr)
{

}

GSDX::~GSDX()
{
	ResetLibrary();
}

#define LOADPROC(memberName) \
	log(GSDX_LOG_LEVEL_DEBUG, L"Load GS%s", L#memberName); \
	memberName = reinterpret_cast<_GS##memberName>(GetProcAddress(DLLHandle, "GS"#memberName)); \
	log(GSDX_LOG_LEVEL_DEBUG, L"GetProcAddress Win32 last error %lu", GetLastError()); \
	if (!memberName) \
	{ \
		ResetLibrary(); \
		log(GSDX_LOG_LEVEL_ERROR, L"Cannot load function GS%s from GSDX", L#memberName); \
		return false; \
	}

#define LOADPROC_PS2(memberName) \
	log(GSDX_LOG_LEVEL_DEBUG, L"Load PS2E%s", L#memberName); \
	memberName = reinterpret_cast<_PS2E##memberName>(GetProcAddress(DLLHandle, "PS2E"#memberName)); \
	log(GSDX_LOG_LEVEL_DEBUG, L"GetProcAddress Win32 last error %lu", GetLastError()); \
	if (!memberName) \
	{ \
		ResetLibrary(); \
		log(GSDX_LOG_LEVEL_ERROR, L"Cannot load function PS2E%s from GSDX", L#memberName); \
		return false; \
	}

bool GSDX::LoadLibrary(const wchar_t* pluginName)
{
	log(GSDX_LOG_LEVEL_INFO, L"Load GSDX library");

	if (DLLHandle)
	{
		log(GSDX_LOG_LEVEL_DEBUG, L"DLLHandle present! Resetting library...");
		ResetLibrary();
	}

	DLLHandle = ::LoadLibrary(pluginName);

	log(GSDX_LOG_LEVEL_DEBUG, L"LoadLibrary Win32 last error %lu", GetLastError());

	if (!DLLHandle)
	{
		log(GSDX_LOG_LEVEL_ERROR, L"Cannot load GSDX library %s", pluginName);
		return false;
	}

	// GS

	LOADPROC(about)
	LOADPROC(Benchmark)
	LOADPROC(close)
	LOADPROC(configure)
	LOADPROC(freeze)
	LOADPROC(getLastTag)
	LOADPROC(getTitleInfo2)
	LOADPROC(gifSoftReset)
	LOADPROC(gifTransfer)
	LOADPROC(gifTransfer1)
	LOADPROC(gifTransfer2)
	LOADPROC(gifTransfer3)
	LOADPROC(init)
	LOADPROC(initReadFIFO)
	LOADPROC(initReadFIFO2)
	LOADPROC(irqCallback)
	LOADPROC(keyEvent)
	LOADPROC(makeSnapshot)
	LOADPROC(open)
	LOADPROC(open2)
	LOADPROC(osdLog)
	LOADPROC(osdMonitor)
	LOADPROC(readFIFO)
	LOADPROC(readFIFO2)
	LOADPROC(Replay)
	LOADPROC(reset)
	LOADPROC(setBaseMem)
	LOADPROC(setExclusive)
	LOADPROC(setFrameSkip)
	LOADPROC(setGameCRC)
	LOADPROC(setSettingsDir)
	LOADPROC(setupRecording)
	LOADPROC(setVsync)
	LOADPROC(shutdown)
	LOADPROC(test)
	LOADPROC(vsync)
	LOADPROC(writeCSR)

	// PS2E
	LOADPROC_PS2(getCpuPlatform)
	LOADPROC_PS2(getLibName)
	LOADPROC_PS2(getLibType)
	LOADPROC_PS2(getLibVersion2)

	log(GSDX_LOG_LEVEL_INFO, L"Load GSDX library completed!");
	return true;
}

void GSDX::ResetLibrary()
{
	log(GSDX_LOG_LEVEL_INFO, L"Reset GSDX library");

	if (DLLHandle)
	{
		FreeLibrary(DLLHandle);
		log(GSDX_LOG_LEVEL_DEBUG, L"FreeLibrary Win32 last error: %lu", GetLastError());
		DLLHandle = nullptr;
	}

	// GS
	osdLog = nullptr;
	osdMonitor = nullptr;
	open = nullptr;
	open2 = nullptr;
	vsync = nullptr;
	gifTransfer = nullptr;
	gifTransfer1 = nullptr;
	gifTransfer2 = nullptr;
	gifTransfer3 = nullptr;
	gifSoftReset = nullptr;
	readFIFO = nullptr;
	readFIFO2 = nullptr;
	initReadFIFO = nullptr;
	initReadFIFO2 = nullptr;
	getTitleInfo2 = nullptr;
	irqCallback = nullptr;
	setBaseMem = nullptr;
	setGameCRC = nullptr;
	setFrameSkip = nullptr;
	setVsync = nullptr;
	setExclusive = nullptr;
	setupRecording = nullptr;
	reset = nullptr;
	writeCSR = nullptr;
	makeSnapshot = nullptr;
	about = nullptr;
	Benchmark = nullptr;
	close = nullptr;
	configure = nullptr;
	freeze = nullptr;
	getLastTag = nullptr;
	init = nullptr;
	keyEvent = nullptr;
	Replay = nullptr;
	setSettingsDir = nullptr;
	shutdown = nullptr;
	test = nullptr;

	// PS2E
	getLibName = nullptr;
	getLibType = nullptr;
	getLibVersion2 = nullptr;
	getCpuPlatform = nullptr;
}
