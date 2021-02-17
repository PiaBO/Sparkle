#include "TutorialStatus.h"
#include "Shop.h"
#include "GameStatus.h"


TutorialStatus* TutorialStatus::status = 0;
//para hacer el singleton
TutorialStatus* TutorialStatus::Instance(){
    if(status == 0){
        status = new TutorialStatus;
    }
    return status;
}

TutorialStatus::TutorialStatus():Status(){
    if (!status) {
        status = this;
    }
    spriteActual = 0;
    salir = false;
    //metemos todos los sprites
    //Menu de quitar tutorial
    menu = new Sprite("resources/fondoMenuInGame.png", 0, 0, 640, 360, 1280, 720);
    siBoton = new Sprite("resources/botones/BotonSi.png", {0,1}, {0,0}, 540, 360, 100, 50);
    noBoton = new Sprite("resources/botones/BotonNo.png", {0,1}, {0,0}, 690, 360, 100, 50);
    text = new Text("¿Deseas omitir el tutorial?");
    text->setPosition(450, 260);
    noBoton->setActualSprite(0);
    siBoton->setActualSprite(0);
    //Fotos del tutorial
    for(unsigned x = 1; x<25;x++){
        spritesTutorial.push_back(new Sprite("resources/FotosTutorial/Tutorial"+to_string(x)+".png", 0, 0, 640, 360, 1280, 720));
    }

    //sonido
    buttonHold=new Music("resources/buttonhold.wav",false,5);
    buttonPress=new Music("resources/buttonpress.wav",false,5);

}

//pintamos todos los sprites y texto
void TutorialStatus::render(float percenTick){
    //Pintamos el sprites actual que necesitemos hasta llegar al ultimo
    if(!salir){
        if(spritesTutorial.size()-1 >= (unsigned)spriteActual){
            spritesTutorial[spriteActual]->draw();
        }
    }else{
        if(spritesTutorial.size()-1 >= (unsigned)spriteActual){
            spritesTutorial[spriteActual]->draw();
        }
        menu->draw();
        siBoton->draw();
        noBoton->draw();
        text->draw();
    }


}

void TutorialStatus::update(float time){
 Motor2D *motor = Motor2D::Instance();
    sf::Vector2i posRaton = sf::Mouse::getPosition((*motor->getWindow()));

    if(siBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){

        if(siBoton->getActualSprite()==0 && salir){ //hover de los botones para omitir el tutorial
            buttonHold->Play();
        }
        siBoton->setActualSprite(1);
    }else{
        siBoton->setActualSprite(0);
    }

    if(noBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
        if(noBoton->getActualSprite()==0 && salir){
            buttonHold->Play();
        }
        noBoton->setActualSprite(1);
    }else{
        noBoton->setActualSprite(0);
    }
}
//controlador de los eventos 
void TutorialStatus::handle(){
    sf::Event event;
    Motor2D *motor = Motor2D::Instance();
    Shop *shop = Shop::Instance();
     while (motor->getWindow()->pollEvent(event)) {
        switch (event.type) {
            default:break;
            case sf::Event::Closed:
                motor->getWindow()->close();
            break;
            case sf::Event::KeyReleased: 
                switch (event.key.code){//saldra el submenu para omitir el tutorial
                    case sf::Keyboard::Escape:
                        if(salir)
                            salir = false; //para indicar si quiere irse del tutorial
                        else
                            salir = true;
                    break;
                    default:break;
                }
            break;

            case sf::Event::MouseButtonReleased:

                sf::Vector2i posRaton = sf::Mouse::getPosition((*motor->getWindow()));

                if(event.mouseButton.button == sf::Mouse::Left){
                //si clicas en cualquier lado de la pantalla avanzara a la siguiente imagen
                    if(!salir){ //si es el ultimo sprite al darle click acabara y empezara el juego
                        if(spritesTutorial[spriteActual]->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
                            if((unsigned)spriteActual == spritesTutorial.size()-1){
                                spriteActual = 0;
                                shop->setMenu(false);
                                shop->setStatus(GameStatus::Instance());
                            }else{
                                spriteActual++;  
                            }
                        }

                    }else{
                        if(siBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
                            //quitamos el tutorial
                            buttonPress->Play();
                            salir = false;
                            shop->setMenu(false);
                            shop->setStatus(GameStatus::Instance());
                        }else if(noBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
                            buttonPress->Play();
                            salir = false;

                        }
                    }
                }
        
            break;
        }
    }
}