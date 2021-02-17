#pragma once

#include "Status.h"

#include "Music.h"

class MenuInGameStatus : public Status{
    public:
        static MenuInGameStatus* Instance();
        void handle();
        void update(float);
        void render(float);
        void saveExit();
        void createAlert(string);

    protected:
        MenuInGameStatus();
        MenuInGameStatus(const MenuInGameStatus &);
        MenuInGameStatus &operator= (const MenuInGameStatus &);
        
    private:
        static MenuInGameStatus* status;
        Sprite *menu;
        Sprite *guardarBoton;
        Sprite *continuarBoton;
        Sprite *tutorialBoton;
        Sprite *salirBoton;
        Sprite *siBoton;
        Sprite *noBoton; 
        Text   *text;
        bool salir;

        Music* buttonHold;
        Music* buttonPress;
};
