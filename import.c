#include "import.h"
#include "strings.h"

HMODULE loadDll(PWSTR dllName) {

	HMODULE retVal = NULL;
	UNICODE_STRING dllNameUni;

	if ((retVal = getModuleBase(hashStringW(dllName))) == NULL) {

		rtl_init_unicode_string(&dllNameUni, dllName);
		ldr_load_dll(NULL, 0, &dllNameUni, (PHANDLE)&retVal);
	}

	return retVal;
}

FARPROC getFunctionAddress(HMODULE mod, DWORD functionHash, WORD loword, WORD hiword) {

	DWORD_PTR baseAddress = (DWORD)mod;
	FARPROC address = NULL;
	HMODULE forward = NULL;
	PSTR functionName;
	ANSI_STRING functionNameA;

	PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)baseAddress;
	PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)(baseAddress + dosHeader->e_lfanew);
	PIMAGE_OPTIONAL_HEADER optHeader = &ntHeaders->OptionalHeader;
	PIMAGE_DATA_DIRECTORY dataDir = (PIMAGE_DATA_DIRECTORY)(&optHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]);
	PIMAGE_EXPORT_DIRECTORY exportDir = (PIMAGE_EXPORT_DIRECTORY)(baseAddress + dataDir->VirtualAddress);
	PWORD ordinals = (PWORD)(baseAddress + exportDir->AddressOfNameOrdinals);
	PULONG names = (PULONG)(baseAddress + exportDir->AddressOfNames);

	CHAR dllName[255];
	WCHAR dllNameW[255];

	for (DWORD i = 0; i < exportDir->NumberOfFunctions; i++) {

		if (hashStringA((PSTR)(baseAddress + (DWORD_PTR)names[i])) == functionHash) {

			address = (FARPROC)(baseAddress + ((PULONG)(baseAddress + exportDir->AddressOfFunctions))[ordinals[i]]);
			break;
		}
	}

	if (((PSTR)address >= (PSTR)exportDir && (PSTR)address < (PSTR)exportDir + dataDir->Size) && address != NULL) {

		StringCchCopyA(dllName, strlA((PSTR)address) + 1, (PSTR)address);

		address = NULL;
		functionName = splitFunction(dllName, '.');
		*functionName++ = 0;

		if (*functionName == '#') {
			functionName = (PSTR)(USHORT)(cAtoi(++functionName));
		}

		toUnicode(dllName, dllNameW);
		forward = loadDll(dllNameW);

		if (forward && forward == mod && ((hiword == 0) ? LOWORD(functionName) == loword : hashStringA(functionName) == functionHash)) {

			functionNameA.Buffer = functionName;
			functionNameA.Length = (USHORT)strlA(functionName);
			functionNameA.MaximumLength = functionNameA.Length + 1;

			ldr_get_procedure_address(forward, &functionNameA, 0, (PVOID*)&address);
		}
		else if (forward) {

			address = getFunctionAddress(forward, hashStringA(functionName), LOWORD(functionName), HIWORD(functionName));
		}

	}

	return address;
}

HMODULE getModuleBase(DWORD moduleHash) {

	PIN_MEMORY_ORDER_MODULE_LIST list;
	HMODULE retVal = NULL;

	__asm {

		mov		edx, dword ptr fs : [0x30]
		mov		edx, [edx + 0x0C]
		mov		edx, [edx + 0x14]
		mov		[list], edx
	}

	while (list->name) {

		if (hashStringW((PWSTR)list->name) == moduleHash || moduleHash == 0) {

			retVal = (HMODULE)list->base;
		}

		list = (PIN_MEMORY_ORDER_MODULE_LIST)list->nextStruct;
	}


	return retVal;
}