#include "pch.h"

Trampoline* PreDrawLanguageText_t = nullptr;

#define CopyPosButton 0x43
#define PastePosButton 0x56

static bool EnableTeleport = true;
static bool ShowCopyNotPaste = false;
static int TeleportTimer = 0;
static Vector3 SavedPosition = {};

void __cdecl PreDrawLanguageText_r(int context) {
    TARGET_DYNAMIC(PreDrawLanguageText)(context);

    Text2D text = {};
    Vector3* pos = GetPlayerPosition();
    std::string string = "Position: " + std::to_string(pos->x) + ", " + std::to_string(pos->z) + ", " + std::to_string(pos->y);

    text.text = string.c_str();
    text.positionX = 10;
    text.positionY = 10;
    text.size = 5;
    text.alphaByte = 255;

    _DrawText(0x5004D4, &text);

    if (SavedPosition.length() != 0) {
        if (TeleportTimer > 0) {
            string = ShowCopyNotPaste == true ? "Position saved!" : "Teleported!";
        }
        else {
            string = "Saved position: " + std::to_string(SavedPosition.x) + ", " + std::to_string(SavedPosition.z) + ", " + std::to_string(SavedPosition.y);
        }

        text.text = string.c_str();
        text.positionY = 30;
        text.size = 3;
        text.alphaByte = TeleportTimer > 0 ? TeleportTimer : 255;

        _DrawText(0x5004D4, &text);
    }
}

void Teleport_OnFrame() {
    if (EnableTeleport && TeleportTimer <= 0) {
        if (GetAsyncKeyState(CopyPosButton) & KEY_PRESSED) {
            SavedPosition = *GetPlayerPosition();
            ShowCopyNotPaste = true;
            TeleportTimer = 255;
        }
        else if (GetAsyncKeyState(PastePosButton) & KEY_PRESSED) {
            if (SavedPosition.length() != 0) {
                SetPlayerPosition(&SavedPosition);
                ShowCopyNotPaste = false;
                TeleportTimer = 255;
            }
        }
    }

    if (TeleportTimer > 0) {
        TeleportTimer -= 10;
    }
}

void Teleport_Init(const IniFile* config) {
    EnableTeleport = config->getBool("", "EnableTeleport", EnableTeleport);

    if (config->getBool("", "ShowPosition", false)) {
        PreDrawLanguageText_t = new Trampoline((int)PreDrawLanguageText, (int)PreDrawLanguageText + 0x5, PreDrawLanguageText_r);
    }
}