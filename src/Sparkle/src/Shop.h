#include "GameStatus.h"
#include "KitchenStatus.h"
#include "MenuStatus.h"
#include "MenuInGameStatus.h"
#include "EndMenuStatus.h"
#include "libroStatus.h"
#include "Clock.h"
#include "Music.h"
#pragma once

class Shop{
    public:
        static Shop* Instance();
        void setStatus(Status*);
        void addStatus(Status*);
        void removeStatus();
        void render();
        void render(float);
        void update(float);
        void handle();
        void reset();
        void addEssence(int,int);
        void removeEssence(int,int);
        inline void addMoney(int num){money += num;}
        inline void restartTime(){clock.restartTime();}
        inline int getPrestige(){return prestige;}
        inline int getLevelPrestige(){return levelPrestige;}
 	    inline int getMoney(){return money;}
        inline int getDay(){return day;}
        inline int getHour(){return hour;}
        inline bool getMenu(){return menu;}
        int getEssence(int);
        inline void setDay(int quantity){day = quantity;}
        inline void setMoney(int num){money = num;}
        inline void setMenu(bool state){ menu = state; };
        inline void setLevelPrestige(int num){levelPrestige = num;}
        inline void setHour(int quantity){hour = quantity;}
        inline void setPrestigio(int p){prestige=p;}
        void setPrestige(int);
        void setEssence(int,int);

    protected:
        Shop();
        Shop(const Shop &);
        Shop &operator= (const Shop &);

    private:
        static Shop* shop;
        int money;
        int prestige;
        int levelPrestige;
        vector<Status*> status;
        int numFire;
        int numAir;
        int numWater;
        int numEarth;
        Clock clock;
        int day;
        int hour;
        bool menu;
        bool iniciado;
        Music* musica;
};