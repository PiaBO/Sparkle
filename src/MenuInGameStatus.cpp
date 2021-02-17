#include "MenuInGameStatus.h"
#include "Shop.h"

MenuInGameStatus* MenuInGameStatus::status = 0;

//crear singleton
MenuInGameStatus* MenuInGameStatus::Instance()
{
    if(status == 0)
    {
        status = new MenuInGameStatus;
    }

    return status;
}

//creamos los sprites necesarios para el menu
MenuInGameStatus::MenuInGameStatus():Status(){
    if (!status) {
        status = this;
    }

    //fondo del menu
    menu = new Sprite("resources/fondoMenuInGame.png", 0, 0, 640, 360, 1280, 720);

    //Botones
    continuarBoton = new Sprite("resources/botones/BotonContinuar.png", {0,1}, {0,0}, 640, 300, 200, 50);
    guardarBoton = new Sprite("resources/botones/BotonGuardar.png", {0,1}, {0,0}, 640, 370, 200, 50);
    tutorialBoton = new Sprite("resources/botones/BotonTutorial.png", {0,1}, {0,0}, 640, 440, 200, 50);
    salirBoton = new Sprite("resources/botones/BotonSalir.png", {0,1}, {0,0}, 640, 510, 200, 50);

    //Cargamos submenu
    siBoton = new Sprite("resources/botones/BotonSi.png", {0,1}, {0,0}, 540, 360, 100, 50);
    noBoton = new Sprite("resources/botones/BotonNo.png", {0,1}, {0,0}, 690, 360, 100, 50);
    text = new Text("¿Deseas guardar antes de salir?");
    text->setPosition(450, 260);

    noBoton->setActualSprite(0);
    siBoton->setActualSprite(0);
    continuarBoton->setActualSprite(0);
    guardarBoton->setActualSprite(0);
    salirBoton->setActualSprite(0);
    salir = false;

    buttonHold=new Music("resources/buttonhold.wav",false,5);
    buttonPress=new Music("resources/buttonpress.wav",false,5);
}

//se pintan los sprites en la pantalla
void MenuInGameStatus::render(float percenTick){

    menu->draw();
    if(salir){
        siBoton->draw();
        noBoton->draw();
        text->draw();
    }else{
        guardarBoton->draw();
        continuarBoton->draw();
        tutorialBoton->draw();
        salirBoton->draw();
    }

    if(alert!=NULL){
      alert->draw();
    }

}

//el update controla el hover de los botones, con su sonido y actualizar la alarma
void MenuInGameStatus::update(float time){
    Motor2D *motor = Motor2D::Instance();
    sf::Vector2i posRaton = sf::Mouse::getPosition((*motor->getWindow()));

    if(continuarBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
        if(!salir && continuarBoton->getActualSprite()==0){
            buttonHold->Play();
        }
        continuarBoton->setActualSprite(1);
    }else{
        continuarBoton->setActualSprite(0);
    }

    if(guardarBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
        if(!salir && guardarBoton->getActualSprite()==0){
            buttonHold->Play();
        }
        guardarBoton->setActualSprite(1);
    }else{
        
        guardarBoton->setActualSprite(0);
    }

    if(tutorialBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
        if(!salir && tutorialBoton->getActualSprite()==0){
            buttonHold->Play();
        }
        tutorialBoton->setActualSprite(1); 
    }else{
        tutorialBoton->setActualSprite(0); 
    }

    if(salirBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
        if(!salir && salirBoton->getActualSprite()==0){
            buttonHold->Play();
        }
        salirBoton->setActualSprite(1); 
    }else{
        salirBoton->setActualSprite(0); 
    }

    if(siBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
        if(salir && siBoton->getActualSprite()==0){
            buttonHold->Play();
        }
        siBoton->setActualSprite(1); 
    }else{
        siBoton->setActualSprite(0); 
    }
    
    if(noBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
        if(salir && noBoton->getActualSprite()==0){
            buttonHold->Play();
        }
        noBoton->setActualSprite(1); 
    }else{
        noBoton->setActualSprite(0); 
    }
    
    if(alert!=NULL){
      if(alert->getStatus()){
        alert->update();
      }else{
        delete alert;
        alert = NULL;
      }
    }
}

//para controlar los eventos
void MenuInGameStatus::handle(){
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
                switch (event.key.code){
                    case sf::Keyboard::Escape: // salir del menu
                        salir = false;
                        shop->setMenu(false);
                        shop->removeStatus();
                    break;
                    default:break;
                }
            break;

            case sf::Event::MouseButtonReleased:

                sf::Vector2i posRaton = sf::Mouse::getPosition((*motor->getWindow()));

                if(event.mouseButton.button == sf::Mouse::Left){
                
                    if(!salir){
                        if(salirBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){ //salir al menu principal
                            buttonPress->Play();
                            saveExit();
                        }else if(continuarBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){ //quitar el menu in game
                            buttonPress->Play();
                            shop->setMenu(false);
                            shop->removeStatus();
                        }else if(guardarBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){ //guardar partida
                            buttonPress->Play();
                            //Guardar
                            guardar();
                            createAlert("Se ha guardado correctamente");
                        } else if(tutorialBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){ //ir al tutorial
                            buttonPress->Play();
                            shop->removeStatus();
                            shop->setStatus(TutorialStatus::Instance());
                        }
                    }else{
                        if(siBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){ //para confirmar el submenu
                            buttonPress->Play();
                            //Guardar
                            salir = false;
                            guardar();
                            shop->removeStatus();
                            shop->setMenu(false);
                            shop->setStatus(MenuStatus::Instance());
                        }else if(noBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){ //para denegar en el submenu
                            buttonPress->Play();
                            salir = false;
                            shop->removeStatus();
                            shop->setMenu(false);
                            shop->setStatus(MenuStatus::Instance());
                        }
                    }
                }
        
            break;
        }
    }
}

void MenuInGameStatus::saveExit(){
    salir = true;
}

//crear alarma
void MenuInGameStatus::createAlert(string text){
    alert = new Alert(text);
}