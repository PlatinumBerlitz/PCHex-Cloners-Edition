#include <3ds.h>

#include "inputmanager.h"

u32 InputManager::kdown;

void InputManager::scanInput() {
    hidScanInput();
    kdown = hidKeysDown();
}

bool InputManager::isPressed(const int button) {
    return (kdown & button);
}

touchPosition InputManager::scanTouch() {
    touchPosition touch;
    hidTouchRead(&touch);
    
    return touch;
}