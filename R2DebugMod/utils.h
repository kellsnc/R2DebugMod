#pragma once

template<typename T>
T* GetDataPointerPath(uint32_t address, std::initializer_list<uint32_t> offsets) {
    int* result = (int*)address;

    for (auto offset : offsets)
    {
        result = (int*)(*result + offset);
    }

    return (T*)result;
}

Vector3* GetPlayerPosition();

void SetPlayerPosition(Vector3* pos);