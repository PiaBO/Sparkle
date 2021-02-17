#include "TextureManager.h"


TextureManager* TextureManager::textManager = 0;
//crear singleton
TextureManager* TextureManager::Instance(){
    if(textManager == 0)
    {
        textManager = new TextureManager;
    }

    return textManager;
}

TextureManager::TextureManager(){
    if (!textManager) {
        textManager = this;
    }
}

//Esto sirve para que no se sobrecargue y salgan los cuadrados en blanco
sf::Texture* TextureManager::Load(string file){
    sf::Texture* texture = new sf::Texture();

    if (!texture->loadFromFile(file)) {
      cout << "Error cargando la imagen";
      exit(0);
    }

    return texture;
}
