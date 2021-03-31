#include "pch.h"

Vector3* GetPlayerPosition() {
    return GetDataPointerPath<Vector3>(0x500560, { 0x224, 0x310, 0x34, 0, 0x1AC });
}

void SetPlayerPosition(Vector3* pos) {
    *GetPlayerPosition() = *pos;
}