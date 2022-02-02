#pragma once
#include "external.h"

DWORD strlA(PSTR str);
DWORD strlW(PWSTR str);
DWORD hashStringW(PWSTR str);
DWORD hashStringA(PSTR str);
void deobfuscateA(CHAR str[], SIZE_T messageLen);
void deobfuscateW(WCHAR str[], SIZE_T messageLen);
PSTR splitFunction(PSTR str, int ch);
int cAtoi(PSTR str);
void toUnicode(PSTR in, PWSTR out);

