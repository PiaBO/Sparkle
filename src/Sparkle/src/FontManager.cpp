#include "FontManager.h"

FontManager* FontManager::fontManager = 0;

//para crear el singleton
FontManager* FontManager::Instance(){
    if(fontManager == 0)
    {
        fontManager = new FontManager;
    }

    return fontManager;
}

//para cargar la fuente que utilizamos durante todo el juego
//de esta forma solo se carga una vez en todo el juego
FontManager::FontManager(){
    if (!fontManager) {
        fontManager = this;
    }

    fuente = new sf::Font();

    if (!fuente->loadFromFile("resources/Letra.ttf")) {
      cout << "Error cargando Letra.ttf";
      exit(0);
    }
}
