#include "Sprite.h"

#pragma once

class Mission {
    public:
        Mission(int,int,int);
        ~Mission();
        void toString(int,int);
        void addTroleado();
        void createAlert();
        inline bool isFinished(){return finish;}
        inline int getReward(){return reward;}
        inline Text getText(){return quest;}
        inline int getNumTroll(){return numTroll;}
        inline int getTroleados(){return troleados;}
        inline int getTypeTroll(){return typeTroll;}
        inline void setReward(int r){reward = r;}
        inline void setNumTroll(int t){numTroll = t;}
        inline void setTypeTroll(int t){typeTroll = t;}
        inline void setTroleados(int t){troleados = t;}
        inline void setText(string t){text = t;}

    private:
        int typeTroll;
        int numTroll;
        int troleados;
        Text quest;
        string text;
        int reward;
        bool finish;
};
