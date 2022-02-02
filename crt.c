#include "crt.h"

void memset(void* str, char ch, size_t n) {
    char* s = (char*)str;

    for (size_t i = 0; i < n; i++) {
        s[i] = ch;
    }
}

void memcpy(void* dest, void* src, size_t n) {
    char* csrc = (char*)src;
    char* cdest = (char*)dest;

    for (size_t i = 0; i < n; i++) {
        cdest[i] = csrc[i];
    }
}

int memcmp(const void* str1, const void* str2, size_t count) {
    const unsigned char* s1 = str1;
    const unsigned char* s2 = str2;
    while (count-- > 0) {

        if (*s1++ != *s2++)
            return s1[-1] < s2[-1] ? -1 : 1;
    }
    return 0;
}