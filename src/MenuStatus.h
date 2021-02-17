#pragma once

#include "Status.h"
#include "TutorialStatus.h"
#include "Music.h"


class MenuStatus : public Status{
    public:
        static MenuStatus* Instance();
        void handle();
        void update(float);
        void render(float);

    protected:
        MenuStatus();
        MenuStatus(const MenuStatus &);
        MenuStatus &operator= (const MenuStatus &);
        
    private:
        static MenuStatus* status;
        //Sprite *menu;
        Sprite *guardarBoton;
        Sprite *jugarBoton;
        Sprite *nuevaBoton;
        Sprite *salirBoton;
        Sprite *tutorialBoton;
        Sprite *title;
        Sprite *footer;
        Clock clock;
        float velScroll;
        Sprite *capa0;
        Sprite *capa1;
        Sprite *capa1_copia;
        float capa1_x;
        float capa1_newX;
        float capa1_lastX;
        float capa1_copia_x;
        float capa1_copia_newX;
        float capa1_copia_lastX;
        Sprite *capa2;
        Sprite *capa2_copia;
        float capa2_x;
        float capa2_newX;
        float capa2_lastX;
        float capa2_copia_x;
        float capa2_copia_newX;
        float capa2_copia_lastX;
        Sprite *capa3;
        Sprite *capa3_copia;
        float capa3_x;
        float capa3_newX;
        float capa3_lastX;
        float capa3_copia_x;
        float capa3_copia_newX;
        float capa3_copia_lastX;
        Sprite *capa4;
        Sprite *capa4_copia;
        float capa4_x;
        float capa4_newX;
        float capa4_lastX;
        float capa4_copia_x;
        float capa4_copia_newX;
        float capa4_copia_lastX;
        Sprite *witch;
        bool upW;
        float actualYw;
        float newYw;
        float lastYw;
        Music* buttonHold;
        Music* buttonPress;
        
};
