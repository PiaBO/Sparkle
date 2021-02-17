#include "Mission.h"
#include "GameStatus.h"

//se inician los datos de la mision
Mission::Mission(int type, int num, int r){
    typeTroll = type;
    numTroll = num;
    reward = r;
    troleados = 0;
    finish = false;

}

Mission::~Mission(){}

//se pasa a string la mision, diciendo a que tipo de npc tiene que enganyar y cuantos lleva del total
void Mission::toString(int x, int y){
    text = "Engañados " + to_string(troleados) + "/" + to_string(numTroll) + " ";  

    switch(typeTroll){
        case 0: text +="campesinos.";
            break;
        case 1: text +="caballeros.";
            break;   
        case 2: text +="cazadores.";
            break;       
        case 3: text +="bardos.";
            break;    
        case 4: text +="magos.";
            break;  
            default:break;                                 
    }

    quest.setString(text);

    quest.setPosition(x,y);
}

//para aumentar en uno el numero de npc del tipo de la mision que lleva troleados
void Mission::addTroleado(){
    troleados ++;

    if(troleados == numTroll){
        finish = true;
    }
}

//cuando completa una mision se le muestra una alerta para indicarle que la ha completado y cuanto ha ganado/perdido
void Mission::createAlert(){
    string s;

    s = "Has completado una misión.\n";
    
    if(reward<=0){
        s += "Lamentablemente ha sido un engaño.\nPierdes: ";
    } else {
        s += "Ganas: ";
    }

    s += to_string(reward) + "$";

    GameStatus::Instance()->createAlert(s);

}