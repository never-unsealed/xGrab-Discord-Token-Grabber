#include "util.h"
#include "strings.h"
#include "import.h"

HMODULE unhookDll(HMODULE dllModule, PWSTR dllPathShort) {

	HMODULE retVal = NULL, dllFile, dllMapped;
	PVOID moduleBase = (PVOID)dllModule, dllMappingAddress;
	PIMAGE_DOS_HEADER dosHeader;
	PIMAGE_NT_HEADERS ntHeaders;
	PIMAGE_SECTION_HEADER sectionHeader;
	DWORD oldProt;
	BOOL isProtected;
	WCHAR fullPath[MAX_PATH], dir[MAX_PATH];

	if (dllModule) {

		get_system_directory(dir, 100);
		StringCchCopyW(fullPath, MAX_PATH, dir);
		StringCchCatW(fullPath, MAX_PATH, dllPathShort);

		dllFile = create_file(fullPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		dllMapped = create_file_mapping(dllFile, NULL, PAGE_READONLY | SEC_IMAGE, 0, 0, NULL);
		dllMappingAddress = map_view_of_file(dllMapped, FILE_MAP_READ, 0, 0, 0);
		dosHeader = (PIMAGE_DOS_HEADER)moduleBase;

		if (dllFile && dllMapped) {

			ntHeaders = (PIMAGE_NT_HEADERS)((DWORD_PTR)moduleBase + dosHeader->e_lfanew);

			for (DWORD i = 0; i < ntHeaders->FileHeader.NumberOfSections; i++) {
				sectionHeader = (PIMAGE_SECTION_HEADER)((DWORD_PTR)IMAGE_FIRST_SECTION(ntHeaders) + ((DWORD_PTR)IMAGE_SIZEOF_SECTION_HEADER * i));

				if (hashStringA(sectionHeader->Name) == 192987352) {

					oldProt = 0;

					isProtected = virtual_protect((PVOID)((DWORD_PTR)moduleBase + (DWORD_PTR)sectionHeader->VirtualAddress), sectionHeader->Misc.VirtualSize, PAGE_EXECUTE_READWRITE, &oldProt);
					memcpy((PVOID)((DWORD_PTR)moduleBase + (DWORD_PTR)sectionHeader->VirtualAddress), (PVOID)((DWORD_PTR)dllMappingAddress + (DWORD_PTR)sectionHeader->VirtualAddress), sectionHeader->Misc.VirtualSize);
					isProtected = virtual_protect((PVOID)((DWORD_PTR)moduleBase + (DWORD_PTR)sectionHeader->VirtualAddress), sectionHeader->Misc.VirtualSize, oldProt, &oldProt);
				}
			}

			close_handle(dllFile);
			close_handle(dllMapped);
		}
	}

	return getModuleBase(hashStringW(dllPathShort + 1));
}