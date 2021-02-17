#include "Alert.h"

//se crea el sprite para el fondo de la alerta y se situa arriba a la izquierda, ademas de crearse el texto que usaremos para escribir nuestro mensaje
Alert::Alert(string pText){
    text = new Text(pText);
    text->setColorWhite();
    text->setPosition(25,90);

    back = new Sprite("resources/alert.png", 0, 0, 150, 115, 450, 150);

    active = true;
    init = clock.getTimeAsSecond();
}

//se elimina la alerta, eliminando los punteros
Alert::~Alert(){
    delete text;
    delete back;

    text = NULL;
    back = NULL;
}

//se pinta en pantalla
void Alert::draw(){
    back->draw();
    text->draw();
}

//se calcula el tiempo transcurrido desde que se creo para eliminar la alerta
void Alert::update(){
    if(clock.getTimeAsSecond()-init>4){
        active=false;
    }
}