#include "pch.h"
#include "testspawn.h"

HelperFunctions helperFunctions;

extern "C" {
    __declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions_) {
        helperFunctions = helperFunctions_;

        const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

        TestSpawn_Init(config);

        delete config;
    }

    __declspec(dllexport) void __cdecl OnFrame() {
        if (g_stEngineStructure.engineMode == LEVEL_STATE_LOADED) {
            TestSpawn_OnFrame();
        }
    }

    __declspec(dllexport) ModInfo Rayman2ModInfo = { ModLoaderVer };
}