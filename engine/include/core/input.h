#ifndef INPUT_H
#define INPUT_H

class Input {
    public:
        static void Init();
        static bool isKeyDown(unsigned char KEYCODE);
        static void KeyCallback();

    private:
        Input() = delete;
        ~Input() = delete;
};

#endif