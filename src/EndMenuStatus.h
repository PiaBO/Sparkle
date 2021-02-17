#pragma once

#include "Status.h"
#include "Music.h"

class EndMenuStatus : public Status{
    public:
        static EndMenuStatus* Instance();
        void handle();
        void update(float);
        void render(float);
        void randomEvent();

    protected:
        EndMenuStatus();
        EndMenuStatus(const EndMenuStatus &);
        EndMenuStatus &operator= (const EndMenuStatus &);
        
    private:
        static EndMenuStatus* status;
        Sprite *back;
        Sprite *menu;
        Sprite *continuar;
        int alquiler;
        int dineroAntes;
        vector<Text*> eventText;
        int lastDayEvent;
        int dayRand;
        bool finBueno;
        Music* buttonHold;
        Music* buttonPress;
};
