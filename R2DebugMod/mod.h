#pragma once

#define KEY_PRESSED 0x8000
#define TARGET_DYNAMIC(name) ((decltype(name##_r)*)name##_t->Target())

extern HelperFunctions helperFunctions;