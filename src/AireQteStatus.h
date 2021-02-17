#pragma once

#include "Status.h"
#include "Pot.h"
#include "Music.h"

struct Object{
    bool catched;
    Sprite *sprite;
    float x;
    float y;
    float newY;
    float lastY;
};

class AireQteStatus : public Status{
    public:
        static AireQteStatus* Instance();
        void handle();
        void update(float);
        void render(float);
        void load();

    protected:
        AireQteStatus();
        AireQteStatus(const AireQteStatus &);
        AireQteStatus &operator= (const AireQteStatus &);
        
    private:
        static AireQteStatus* status;
        Text text;
        string texto;
        Text catched;
        Clock clock;
        Clock endClock;
        float timeAcum;
        int numObjects;
        int quedan;
        int cogidos;
        vector<Object> objects;
        Pot *pot;
        int esencias;
        Music* sonidoCoger;
};