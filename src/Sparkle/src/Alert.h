#include "Clock.h"
#include "Sprite.h"

#pragma once

class Alert {
    private:
        Text *text;
        Sprite *back;
        Clock clock;
        bool active;
        float init;
        
    public:
        Alert(string text);
        ~Alert();
        void draw();
        void update();
        inline bool getStatus(){return active;}
};