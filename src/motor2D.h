#include <SFML/Graphics.hpp>
#include <iostream>
#include "Text.h"

using namespace std;
#pragma once

class Motor2D{
    private:
        sf::RenderWindow *window;
        static Motor2D *motor;
        Motor2D();
        Motor2D(const Motor2D &); //constructor de copia

    public:
        static Motor2D *Instance();
        void setWindow(sf::RenderWindow *ventana);
        void drawWindow();
        void drawSprites(sf::Sprite sprite);
        void drawText(sf::Text text);
        void clearWindow();
        void closeWindow();
        sf::RenderWindow* getWindow();
};