#include "Missions.h"

//se crea el fondo donde se van a pintar las misiones individuales
Missions::Missions(){
    fondo = new Sprite("resources/misionesHud.png", 0, 0, 890,170,341,230);
}

Missions::~Missions(){}

//actualizar las misiones para que compruebe una a una la lista de misiones individuales si son del tipo que le pasan pos parametro
void Missions::update(int typeTroll){
    for(int i=0;(unsigned) i<missions.size(); i++){
        if(missions[i]->getTypeTroll() == typeTroll){ //si la mision es del tipo que le pasan por parametro agrega uno al numero de engañados
            missions[i]->addTroleado();
        }

        if(missions[i]->isFinished()){ //si la mision esta finalizada crea una alerta y elimina esa mision
            missions[i]->createAlert();
            delete missions[i];
            missions[i]=NULL;
            missions.erase(missions.begin()+i); //TENER CUIDADO POR SI PETA
            i--;
        }
    }
}

//pinta el fondo con el texto de las misiones individuales
void Missions::render(){

    fondo->draw();

    for(int i=0;(unsigned) i<missions.size(); i++){
        missions[i]->toString(723,60+34*i);
        missions[i]->getText().draw();
    }
}

//agrega una nueva mision a la lista
void Missions::addMission(int type, int num, int reward){
    missions.push_back(new Mission(type,num,reward));
}

//para cargar las misiones desde el fichero de partida guardada
void Missions::addMission(int type, int num, int reward,int troleados){
    missions.push_back(new Mission(type,num,reward));
    missions[missions.size()-1]->setTroleados(troleados);
}