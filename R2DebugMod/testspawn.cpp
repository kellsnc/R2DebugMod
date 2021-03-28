/*

Rayman2 Debug Mod
TestSpawn

Loads the game directly into a level by either using the config file, or the "-l [name]" command.

*/

#include "pch.h"

static std::string LevelName;
static bool SpawnLevelLoaded;

void SetSpawnLevel(const std::string& name) {
    if (name.empty() == false) {
        LevelName = name;
        helperFunctions.PrintDebug("[Debug] Loading level \"%s\".\n", name.c_str());
    }
}

void TestSpawn_OnFrame() {
    if (SpawnLevelLoaded == false && LevelName.empty() == false) {
        LoadNextLevel(LevelName.c_str(), 0);
        SpawnLevelLoaded = true;
    }
}

void TestSpawn_Init(const IniFile* config) {
    std::string lines = cmdline;
    size_t pos = lines.find("-l");

    if (pos != std::string::npos) {
        SetSpawnLevel(lines.substr(pos + 3, lines.find(' ', pos + 3)));
    }
    else {
        SetSpawnLevel(config->getString("", "LevelName", ""));
    }
}