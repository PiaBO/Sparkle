#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

#pragma once

class TextureManager{
    public:
        static TextureManager* Instance();
        sf::Texture* Load(string);
    protected:
        TextureManager();
        TextureManager(const TextureManager &);
        TextureManager &operator= (const TextureManager &);
    private:
        static TextureManager* textManager;
};
