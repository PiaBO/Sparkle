#include <SFML/Graphics.hpp>
#include <codecvt>
#include <locale>
#include "FontManager.h"

using namespace std;

#pragma once

class Text {
    private:
        sf::Text texto;
    public:
        Text(string text);
        Text();
        ~Text();
        void draw();
        void setColorBlack();
        void setColorWhite();
        void setColorRed();
        void setSize(int size);
        void setUnderline();
        void setPosition(int x, int y);
        void setString(string newText);
        inline sf::Text getText(){return texto;}

};