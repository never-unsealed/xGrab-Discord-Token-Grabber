#include "strings.h"


DWORD strlA(PSTR str) {

	DWORD retVal = 0;

	while (str && *str != '\0') {
		str++;
		retVal++;
	}

	return retVal;
}

DWORD strlW(PWSTR str) {

	DWORD retVal = 0;

	while (str && *str != '\0') {
		str++;
		retVal++;
	}

	return retVal;
}

DWORD hashStringA(PSTR str) {

	DWORD retVal = 5381;
	int c;

	while (c = *str++) {
		retVal = ((retVal << 5) + retVal) + c;
	}

	return retVal;
}

DWORD hashStringW(PWSTR str) {

	DWORD retVal = 5381;
	int c;

	while (c = *str++) {
		retVal = ((retVal << 5) + retVal) + c;
	}

	return retVal;
}

void deobfuscateA(CHAR str[], SIZE_T messageLen) {

	CHAR key[] = { 0x17, 0x2E, 0x36, 0x0C, 0x3F, 0x18, 0x76, 0x5F, 0x5A, 0x23, 0x0C, 0x21, 0x2A, 0x20, 0x12, 0x49, 0x5E, 0x28 };

	for (SIZE_T i = 0; i < messageLen; i++) {
		str[i] = str[i] ^ key[i % 18];
	}
}

void deobfuscateW(WCHAR str[], SIZE_T messageLen) {

	WCHAR key[] = { 0x17, 0x2E, 0x36, 0x0C, 0x3F, 0x18, 0x76, 0x5F, 0x5A, 0x23, 0x0C, 0x21, 0x2A, 0x20, 0x12, 0x49, 0x5E, 0x28 };

	for (SIZE_T i = 0; i < messageLen; i++) {
		str[i] = str[i] ^ key[i % 18];
	}

}

PSTR splitFunction(PSTR str, int ch) {

	do {

		if (*str == ch) return str;
	} while (*str++);

	return NULL;
}

int cAtoi(PSTR str) {

	int sign = 1, base = 0, i = 0;

	while (str[i] == ' ') {
		i++;
	}

	if (str[i] == '-' || str[i] == '+') {
		sign = 1 - 2 * (str[i++] == '-');
	}

	while (str[i] >= '0' && str[i] <= '9') {
		if (base > 2147483647 / 10 || (base == 2147483647 / 10 && str[i] - '0' > 7)) {
			if (sign == 1) {
				return 2147483647;
			}
			else {
				return 2147483648;
			}
		}
		base = 10 * base + (str[i++] - '0');
	}
	return base * sign;
}

void toUnicode(PSTR in, PWSTR out) {

	DWORD len = strlA(in);

	for (DWORD i = 0; i < len; i++) {
		out[i] = (WCHAR)in[i];
	}

	out[len] = '\0';
}