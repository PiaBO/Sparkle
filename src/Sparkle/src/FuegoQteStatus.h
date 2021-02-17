#pragma once

#include "Status.h"
#include "Music.h"


class FuegoQteStatus : public Status{
    public:
        static FuegoQteStatus* Instance();
        void handle();
        void update(float);
        void render(float);
        void load();

    protected:
        FuegoQteStatus();
        FuegoQteStatus(const FuegoQteStatus &);
        FuegoQteStatus &operator= (const FuegoQteStatus &);
        
    private:
        static FuegoQteStatus* status;
        Text text;
        string texto;
        Clock tiempo;
        Clock clock;
        Clock relojEspera;
        int tecla;
        int esencias;
        bool catched;
        float tiempoRand;
        Sprite *caldero;
        Sprite *calderoFondo;
        Sprite *rana;
        Sprite *libros;
        Sprite *completado;

        Music* croak;
};