#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class InputManager {
    private:
      static u32 kdown;
      
    public:
        static const int BUTTON_A = KEY_A;
        static const int BUTTON_B = KEY_B;
        static const int BUTTON_X = KEY_X;
        static const int BUTTON_Y = KEY_Y;
        static const int BUTTON_LEFT = KEY_LEFT;
        static const int BUTTON_RIGHT = KEY_RIGHT;
        static const int BUTTON_UP = KEY_UP;
        static const int BUTTON_DOWN = KEY_DOWN;
        static const int BUTTON_R = KEY_R;
        static const int BUTTON_L = KEY_L;
        static const int BUTTON_START = KEY_START;
        
        static void scanInput();
        static bool isPressed(const int button);
};

#endif /* INPUTMANAGER_H */

