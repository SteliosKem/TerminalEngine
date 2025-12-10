#include "Input.h"
#include <Windows.h>

bool isKeyDown(char key) {
    return GetAsyncKeyState((unsigned short)key) & 0x8000;
}
