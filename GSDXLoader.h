#pragma once

#include "GS.h"

// NOTE: GSreadFIFOX/GSwriteCSR functions CANNOT use XMM/MMX regs
// If you want to use them, need to save and restore current ones
typedef void(CALLBACK* _GSosdLog)(const char* utf8, u32 color);
typedef void(CALLBACK* _GSosdMonitor)(const char* key, const char* value, u32 color);
typedef s32(CALLBACK* _GSopen)(void* pDsp, const char* Title, int multithread);
typedef s32(CALLBACK* _GSopen2)(void* pDsp, u32 flags);
typedef void(CALLBACK* _GSvsync)(int field);
typedef void(CALLBACK* _GSgifTransfer)(const u32* pMem, u32 size);
typedef void(CALLBACK* _GSgifTransfer1)(u32* pMem, u32 addr);
typedef void(CALLBACK* _GSgifTransfer2)(u32* pMem, u32 size);
typedef void(CALLBACK* _GSgifTransfer3)(u32* pMem, u32 size);
typedef void(CALLBACK* _GSgifSoftReset)(u32 mask);
typedef void(CALLBACK* _GSreadFIFO)(u64* pMem);
typedef void(CALLBACK* _GSreadFIFO2)(u64* pMem, int qwc);
typedef void(CALLBACK* _GSinitReadFIFO)(u64* pMem);
typedef void(CALLBACK* _GSinitReadFIFO2)(u64* pMem, int qwc);

typedef void(CALLBACK* _GSchangeSaveState)(int, const char* filename);
typedef void(CALLBACK* _GSgetTitleInfo2)(char* dest, size_t length);
typedef void(CALLBACK* _GSirqCallback)(void (*callback)());
typedef void(CALLBACK* _GSsetBaseMem)(void*);
typedef void(CALLBACK* _GSsetGameCRC)(int, int);
typedef void(CALLBACK* _GSsetFrameSkip)(int frameskip);
typedef void(CALLBACK* _GSsetVsync)(int enabled);
typedef void(CALLBACK* _GSsetExclusive)(int isExclusive);
typedef std::wstring* (CALLBACK* _GSsetupRecording)(int);
typedef void(CALLBACK* _GSreset)();
typedef void(CALLBACK* _GSwriteCSR)(u32 value);
typedef void(CALLBACK* _GSmakeSnapshot)(const char* path);
typedef int(CALLBACK* _GSinit)(void);
typedef void(CALLBACK* _GSshutdown)(void);
typedef int(CALLBACK* _GStest)(void);
typedef void(CALLBACK* _GSabout)(void);
typedef void(CALLBACK* _GSclose)(void);
typedef void(CALLBACK* _GSconfigure)(void);
typedef int(CALLBACK* _GSfreeze)(int mode, GSFreezeData* data);
typedef void(CALLBACK* _GSgetLastTag)(uint32_t* tag);
typedef void(CALLBACK* _GSkeyEvent)(GSKeyEventData* e);
typedef void(CALLBACK* _GSsetSettingsDir)(const char* dir);
typedef void(CALLBACK* _GSReplay)(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow);
typedef void(CALLBACK* _GSBenchmark)(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow);

enum LogLevel
{
	GSDX_LOG_LEVEL_ERROR,
	GSDX_LOG_LEVEL_INFO,
	GSDX_LOG_LEVEL_DEBUG,
};

typedef void(CALLBACK* _GSDXLog)(unsigned char level, const wchar_t* format, ...);

class GSDX
{
private:
	HMODULE DLLHandle;

public:
	_GSDXLog log;

	// GS

	_GSosdLog osdLog;
	_GSosdMonitor osdMonitor;
	_GSopen open;
	_GSopen2 open2;
	_GSvsync vsync;
	_GSgifTransfer gifTransfer;
	_GSgifTransfer1 gifTransfer1;
	_GSgifTransfer2 gifTransfer2;
	_GSgifTransfer3 gifTransfer3;
	_GSgifSoftReset gifSoftReset;
	_GSreadFIFO readFIFO;
	_GSreadFIFO2 readFIFO2;
	_GSinitReadFIFO initReadFIFO;
	_GSinitReadFIFO2 initReadFIFO2;
	_GSgetTitleInfo2 getTitleInfo2;
	_GSirqCallback irqCallback;
	_GSsetBaseMem setBaseMem;
	_GSsetGameCRC setGameCRC;
	_GSsetFrameSkip setFrameSkip;
	_GSsetVsync setVsync;
	_GSsetExclusive setExclusive;
	_GSsetupRecording setupRecording;
	_GSreset reset;
	_GSwriteCSR writeCSR;
	_GSmakeSnapshot makeSnapshot;
	_GSabout about;
	_GSBenchmark Benchmark;
	_GSclose close;
	_GSconfigure configure;
	_GSfreeze freeze;
	_GSgetLastTag getLastTag;
	_GSinit init;
	_GSkeyEvent keyEvent;
	_GSReplay Replay;
	_GSsetSettingsDir setSettingsDir;
	_GSshutdown shutdown;
	_GStest test;
	
	// PS2E

	_PS2EgetLibName getLibName;
	_PS2EgetLibType getLibType;
	_PS2EgetLibVersion2 getLibVersion2;
	_PS2EgetCpuPlatform getCpuPlatform;

	// Class members

	GSDX();
	~GSDX();

	bool LoadLibrary(const wchar_t* pluginName);
	void ResetLibrary();

};
