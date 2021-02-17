#pragma once
#include "Status.h"
#include "Npc.h"
#include "Missions.h"
#include "Music.h"

class GameStatus : public Status{

    public:
        static GameStatus* Instance();
        void handle();
        void update(float);
        void render(float);
        int setSprites();
        void createAlert(string);
        void deleteNPC();
        void drawTextHud();
        void calculeDayTroll();
        void addMission(int,int,int,int);
        void resetDatos();
        inline Npc* getNpc(){return npc;}
        inline void setQuest(bool value){quest=value;}
        inline Missions getMissions(){return missions;}
        void clearDrops();

    protected:
        GameStatus();
        GameStatus(const GameStatus &);
        GameStatus &operator= (const GameStatus &);
        
    private:
        static GameStatus* status;
        Sprite *back;
        Sprite *table;
        vector<Sprite*> potions;
        vector<Sprite*> esencias;
        vector<int> drops;
        Sprite *interfazTop;
        Sprite *interfazRight;
        Sprite *libroSprite;
        Sprite *botonMenu;
        Sprite *misionesSprite;
        Sprite *gatoSprite;
        Npc *npc;
        bool quest;
        float timeBetweenUpdate;
        float timeBetweenUpdate1;
        float animacionPotis;
        float animacionGato;
        int lastDayTroll;
        int dayTroll;
        Missions missions;
        bool missionsOpen;
        Music* buttonHold;
        Music* buttonPress;
        Music* abrirLibro;
        Music* coin;
        Clock wait;
};