#include "Text.h"
#include "motor2D.h"

using convert_t = std::codecvt_utf8<wchar_t>;
std::wstring_convert<convert_t, wchar_t> strconverter;

//Creacion de la clase texto a partir de un string
Text::Text(string text){

    wstring aux = strconverter.from_bytes(text);

    texto.setString(aux);
    texto.setFont(*FontManager::Instance()->getFont());
    texto.setColor(sf::Color::White);
    texto.setCharacterSize(18);
    
}
//crear un texto base sin nada
Text::Text(){

    texto.setFont(*FontManager::Instance()->getFont());
    texto.setColor(sf::Color::White);
    texto.setCharacterSize(18);
}

Text::~Text(){}

//Conectar con el motor2D para hacer el draw
void Text::draw(){
    Motor2D* motor = Motor2D::Instance();
    motor->drawText(texto);
}

//Selector de colores para texto
void Text::setColorBlack(){
    texto.setColor(sf::Color::Black);
}

void Text::setColorWhite(){
    texto.setColor(sf::Color::White);
}

void Text::setColorRed(){
    texto.setColor(sf::Color::Red);
}
//Fin del selector de colores
//Selector de tamanyo
void Text::setSize(int size){
    texto.setCharacterSize(size);
}
//Subrayado
void Text::setUnderline(){
    texto.setStyle(sf::Text::Style::Underlined);
}
//Recolocar el texto que vamos a utilizar
void Text::setPosition(int x, int y){ 
    texto.setPosition(x,y);
}

void::Text::setString(string newText){
    //Conversor para que funcione
    wstring aux = strconverter.from_bytes(newText);
    //lo pasamos a wstring
    texto.setString(aux);
}