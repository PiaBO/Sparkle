#include "Clock.h"

//PARA HACER FAÇADE DEL RELOJ, CONTIENE LOS MISMOS METODOS QUE LA CLASE SF:CLOCK

Clock::Clock(){

}

Clock::~Clock(){
    clock.getElapsedTime().Zero;
}

sf::Time Clock::restartTime(){
    return clock.restart();
}

float Clock::getTimeAsSecond(){
    return clock.getElapsedTime().asSeconds();
}

int Clock::getTimeAsMilli(){
    return clock.getElapsedTime().asMilliseconds();
}

int Clock::getTimeAsMicro(){
    return clock.getElapsedTime().asMicroseconds();
}
