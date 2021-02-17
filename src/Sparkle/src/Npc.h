#include <SFML/Graphics.hpp>
#include <fstream>
#include "Music.h"
#include "../include/rapidjson/document.h" 
#include "../include/rapidjson/writer.h" 
#include "../include/rapidjson/stringbuffer.h"

#include "Sprite.h"
#include "Clock.h"

#pragma once

#define TAM_X 330
#define TAM_Y 380
#define POS_INI_X -150
#define POS_INI_Y 400

using namespace std;
using namespace rapidjson;

class Npc {
  private:
    Sprite* sprite;
    Sprite* dialogBox;
    Sprite* accept;
    Sprite* cancel;
    int typeQuest;
    int reward;
    int estado;// 0 parado 1 entrando 2 hablando 3 saliendo 5 acabado
    Text quest;
    bool accepted;
    int lastX;
    int newX;
    int actualX;
    int lastY;
    int newY;
    int actualY;
    bool up;
    bool troleando;
    int tipoTroll;
    int numTroll;
    static int lastNpcType;
    Music* ring;
    Clock reloj;
  public:
    Npc(bool);//contructor que inicializa todo
    ~Npc();//destructor
    void update(float);
    void render(float);
    void actualizarNpc(float);
    inline int getReward(){return reward;}
    inline int getQuestType(){return typeQuest;}
    inline int getStatus(){return estado;}
    inline Sprite* getSprite(){return sprite;}
    inline Sprite* getAccept(){return accept;}
    inline Sprite* getCancel(){return cancel;}
    inline void acceptQuest(){accepted=true;}
    inline void setStatus(int stat){estado = stat;}
    inline bool isTroll(){return troleando;}
    inline int getTypeTroll(){return tipoTroll;}
    inline int getNumTroll(){return numTroll;}
};
