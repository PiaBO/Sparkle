#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

#pragma once

class FontManager{
    public:
        static FontManager* Instance();
        inline sf::Font* getFont(){return fuente;}

    protected:
        FontManager();
        FontManager(const FontManager &);
        FontManager &operator= (const FontManager &);
        
    private:
        static FontManager* fontManager;
        sf::Font* fuente;
};
