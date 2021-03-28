#include "pch.h"

static int ResetLevelButton = 0x52;

void ResetLevel_Init(const IniFile* config) {
	ResetLevelButton = config->getInt("", "ResetLevelButton", ResetLevelButton);
}

void ResetLevel_OnFrame() {
	if (ResetLevelButton && GetAsyncKeyState(ResetLevelButton) & KEY_PRESSED) {
		LoadNextLevel(&g_stEngineStructure.field_1, 0);
	}
}