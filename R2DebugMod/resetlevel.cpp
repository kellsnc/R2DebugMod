#include "pch.h"

static int ResetLevelButton = 0x52;

void ResetLevel_Init(const IniFile* config) {
	ResetLevelButton = config->getInt("", "ResetLevelButton", ResetLevelButton);
}

void ResetLevel_OnFrame() {
	if (ResetLevelButton && GetAsyncKeyState(ResetLevelButton) & KEY_PRESSED) {
		GAM_fn_vAskToChangeLevel(fn_p_szGetNextLevelName(), 0);
		helperFunctions.PrintDebug("[Debug] Resetting level...\n");
	}
}