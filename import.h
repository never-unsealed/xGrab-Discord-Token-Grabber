#pragma once
#include "external.h"

typedef struct s_IN_MEMORY_ORDER_MODULE_LIST {
	DWORD nextStruct;
	DWORD unk_0;
	DWORD unk_1;
	DWORD unk_2;
	DWORD base;
	DWORD unk_3;
	DWORD unk_4;
	DWORD unk_5;
	DWORD dllPath;
	DWORD unk_6;
	DWORD name;
} IN_MEMORY_ORDER_MODULE_LIST, * PIN_MEMORY_ORDER_MODULE_LIST;

HMODULE loadDll(PWSTR dllName);
FARPROC getFunctionAddress(HMODULE mod, DWORD functionHash, WORD loword, WORD hiword);
HMODULE getModuleBase(DWORD moduleHash);

