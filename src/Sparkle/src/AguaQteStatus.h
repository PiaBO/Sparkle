#pragma once

#include "Status.h"
#include <chrono> 
#include <thread> 
#include "Music.h"

using namespace std::this_thread;  
using namespace std::chrono;

class AguaQteStatus : public Status{
    public:
        static AguaQteStatus* Instance();
        void handle();
        void update(float);
        void render(float);
        void load();

    protected:
        AguaQteStatus();
        AguaQteStatus(const AguaQteStatus &);
        AguaQteStatus &operator= (const AguaQteStatus &);
        
    private:
        static AguaQteStatus* status;
        Sprite *back;
        Sprite *table;   
        Sprite* gota;
        Sprite* pot;
        Text text;
        Text titulo;
        string texto;
        Clock tiempo;
        Clock reloj;
        Clock relojGota;
        bool con;
        bool actualizar;
        bool fin;
        bool start;
        int pulsos;
        int tecla;
        int esencias;
        int posSprite;
        int pulsaciones;
        float y;
        float lasty;
        float newy;
        float tiempoPulso;
        float tiempoTecla;
        float tiempoMedia;
        float timeAcumulado;
        Music* sonidogota;
};