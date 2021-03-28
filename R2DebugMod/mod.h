#pragma once

// Common stuff
extern HelperFunctions helperFunctions;

#define KEY_PRESSED 0x8000

// Additional pointers
FunctionPointer(void, LoadNextLevel, (const char* name, int save), 0x4054D0);