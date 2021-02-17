#include "Mission.h"

#pragma once

class Missions{
    public:
        Missions();
        ~Missions();
        void update(int);
        void render();
        void addMission(int,int,int);
        void addMission(int,int,int,int);
        inline int getSize(){return missions.size();}
        inline  vector<Mission*>  getMissions(){return missions;}
        inline void clearMissions(){missions.clear();}

    private:
        vector<Mission*> missions;
        Sprite *fondo;
};