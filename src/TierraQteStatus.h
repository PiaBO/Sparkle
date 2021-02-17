#pragma once

#include "Status.h"
#include <chrono> 
#include <thread> 
#include "Music.h"

using namespace std::this_thread;  
using namespace std::chrono;

class TierraQteStatus : public Status{
    public:
        static TierraQteStatus* Instance();
        void handle();
        void update(float);
        void render(float);
        void load();

    protected:
        TierraQteStatus();
        TierraQteStatus(const TierraQteStatus &);
        TierraQteStatus &operator= (const TierraQteStatus &);
        
    private:
        static TierraQteStatus* status;
        Text text;
        string texto;
        Clock tiempo;
        int pos;
        vector <int> teclas;
        vector<Sprite*> spritesTeclas;
        vector<int> direccion;
        int esencias;
        float newx;
        float newy;
        float x;
        float y;
        float lastx;
        float lasty;
        vector<float> posicionesX;
        vector<float> posicionesY; 
        int velocidad;
        bool pause;
        bool out;
        Sprite *bruja;
        float timeAcum;

        Music* batir;
};