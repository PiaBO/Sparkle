#include "motor2D.h"

Motor2D* Motor2D::motor = 0; // declaramos instancia 

Motor2D::Motor2D(){

}

//para crear el singleton
Motor2D* Motor2D::Instance(){ 
    if(motor == 0){
        motor = new Motor2D;
        sf::RenderWindow *ventanaJuego = new sf::RenderWindow(sf::VideoMode(1280, 720), "Sparkle");
        motor->window = ventanaJuego;
    }
    return motor;
}

//para recuperar la ventana
void::Motor2D::setWindow(sf::RenderWindow *ventana){
    this->window = ventana;
}

//para pintar la ventana
void::Motor2D::drawWindow(){
    window->display();
}

//para pintar los sprites
void::Motor2D::drawSprites(sf::Sprite sprite){
    window->draw(sprite);
}

//para pintar el texto
void::Motor2D::drawText(sf::Text text){
    window->draw(text);
}

//para limpiar la ventana
void::Motor2D::clearWindow(){
    window->clear();
}

//para cerrar la ventana
void::Motor2D::closeWindow(){
    window->close();
}

//para recuperar la ventana
sf::RenderWindow* Motor2D::getWindow(){
    return window;
}