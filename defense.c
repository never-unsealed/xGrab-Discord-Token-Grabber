#include "defense.h"

BOOL checkDebuggerPEB() {

	PPEB peb = (PPEB)__readfsdword(0x30);

	nt_set_information_thread(NtCurrentThread(), 0x11, NULL, 0);
	return peb->BeingDebugged;
}

BOOL checkDebuggerGlobalFlags() {

	PPEB peb = (PPEB)__readfsdword(0x30);
	DWORD krnlGlobal = *(PDWORD)((PBYTE)peb + 0x68);
	PVOID heap = (PVOID) * (PDWORD_PTR)((PBYTE)peb + 0x18);
	PDWORD heapFlagsPtr = (PDWORD)((PBYTE)heap + 0x40);
	PDWORD heapForceFlagsPtr = (PDWORD)((PBYTE)heap + 0x44);

	if (krnlGlobal & NT_GLOBAL_FLAG_DEBUGGED || *heapFlagsPtr & ~HEAP_GROWABLE || *heapForceFlagsPtr != 0) {

		return TRUE;
	}
	else {

		return FALSE;
	}

}

BOOL checkDebuggerQuery() {

	UINT32 checkDebugger = 0;

	if (NT_SUCCESS(nt_query_information_process(NtCurrentProcess(), 7, &checkDebugger, sizeof(UINT32), NULL)) && checkDebugger != 0) {

		return TRUE;
	}
	else {

		return FALSE;
	}
}


//TODO: Add some VM detections