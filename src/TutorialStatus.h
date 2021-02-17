#include "Status.h"
#include "Music.h"

using namespace std;
#pragma once

class TutorialStatus : public Status{
 public:
        static TutorialStatus* Instance();
        void handle();
        void update(float);
        void render(float);


    protected:
        TutorialStatus();
        TutorialStatus(const TutorialStatus &);
        TutorialStatus &operator= (const TutorialStatus &);
        
    private:
        static TutorialStatus* status;
        vector<Sprite*> spritesTutorial;
        Text* text;
        Sprite* siBoton;
        Sprite* noBoton;
        Sprite* menu;
        int spriteActual;  
        bool salir;

        Music* buttonHold;
        Music* buttonPress;
};