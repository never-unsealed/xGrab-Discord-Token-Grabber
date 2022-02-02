#pragma once
#include <stdlib.h>

void memset(void* str, char ch, size_t n);
void memcpy(void* dest, void* src, size_t n);
int memcmp(const void* str1, const void* str2, size_t count);
