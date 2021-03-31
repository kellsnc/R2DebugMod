#include "pch.h"

HelperFunctions helperFunctions;

static bool CannotDie = false;

extern "C" {
    __declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions_) {
        helperFunctions = helperFunctions_;

        const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

        TestSpawn_Init(config);
        ResetLevel_Init(config);
        Teleport_Init(config);

        CannotDie = config->getBool("", "CannotDie", CannotDie);

        delete config;
    }

    __declspec(dllexport) void __cdecl OnFrame() {
        if (g_stEngineStructure.engineMode == ENGINE_STATE_INGAME) {
            TestSpawn_OnFrame();
            ResetLevel_OnFrame();
            Teleport_OnFrame();

            if (CannotDie == true) {
                *GetDataPointerPath<uint32_t>(0x500584, { 0x245 }) = 99;
            }
        }
    }

    __declspec(dllexport) ModInfo Rayman2ModInfo = { ModLoaderVer };
}