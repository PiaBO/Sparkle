#include "MenuStatus.h"
#include "Shop.h"

MenuStatus* MenuStatus::status = 0;

//crear el singleton
MenuStatus* MenuStatus::Instance()
{
    if(status == 0)
    {
        status = new MenuStatus;
    }

    return status;
}

//creamos los sprites
MenuStatus::MenuStatus():Status(){
    if (!status) {
        status = this;
    }

    //SCROLLING
    velScroll = 70;

    //fondo CAPA 0
    capa0 = new Sprite("resources/scroll/fondo.png", 0, 0, 640, 360, 1280, 720);


    //fondo CAPA 1
    capa1 = new Sprite("resources/scroll/nubes.png", 0, 0, 0, 0, 2560, 720);
    capa1->setOriginCero();
    capa1_copia = new Sprite("resources/scroll/nubes.png", 0, 0, 2560, 0, 2560, 720);
    capa1_copia->setOriginCero();
    capa1_x = 0;
    capa1_lastX = 0;
    capa1_newX = 0;
    capa1_copia_x = 2560;
    capa1_copia_newX = 2560;
    capa1_copia_lastX = 2560;


    //fondo CAPA 2
    capa2 = new Sprite("resources/scroll/mountains.png", 0, 0, 0, 0, 2560, 720);
    capa2->setOriginCero();
    capa2_copia = new Sprite("resources/scroll/mountains.png", 0, 0, 2560, 0, 2560, 720);
    capa2_copia->setOriginCero();
    capa2_x = 0;
    capa2_lastX = 0;
    capa2_newX = 0;
    capa2_copia_x = 2560;
    capa2_copia_newX = 2560;
    capa2_copia_lastX = 2560;

    //fondo CAPA 3
    capa3 = new Sprite("resources/scroll/forest.png", 0, 0, 0, 0, 2560, 720);
    capa3->setOriginCero();
    capa3_copia = new Sprite("resources/scroll/forest.png", 0, 0, 2560, 0, 2560, 720);
    capa3_copia->setOriginCero();
    capa3_x = 0;
    capa3_lastX = 0;
    capa3_newX = 0;
    capa3_copia_x = 2560;
    capa3_copia_newX = 2560;
    capa3_copia_lastX = 2560;

    //fondo CAPA 4
    capa4 = new Sprite("resources/scroll/trees.png", 0, 0, 0, 0, 2560, 720);
    capa4->setOriginCero();
    capa4_copia = new Sprite("resources/scroll/trees.png", 0, 0, 2560, 0, 2560, 720);
    capa4_copia->setOriginCero();
    capa4_x = 0;
    capa4_lastX = 0;
    capa4_newX = 0;
    capa4_copia_x = 2560;
    capa4_copia_newX = 2560;
    capa4_copia_lastX = 2560;

    //brujita
    witch = new Sprite("resources/scroll/brujita.png", 0,0,300,320,543,255);
    lastYw = 320;
    newYw = 320;

    //menu = new Sprite("resources/fondoSparkle.png", 0, 0, 640, 360, 1280, 720);
    
    //Botones del interfaz
    nuevaBoton = new Sprite("resources/botones/BotonNuevaPartida.png", {0,1}, {0,0}, 640, 300, 200, 50);
    jugarBoton = new Sprite("resources/botones/BotonJugar.png", {0,1}, {0,0}, 640, 370, 200, 50);
    tutorialBoton = new Sprite("resources/botones/BotonTutorial.png", {0,1}, {0,0}, 640, 440, 200, 50);
    salirBoton = new Sprite("resources/botones/BotonSalir.png", {0,1}, {0,0}, 640, 510, 200, 50);

    title = new Sprite("resources/scroll/tituloSparkle.png", 0, 0, 640, 150, 400, 103);
    footer = new Sprite("resources/scroll/footer.png", 0, 0, 640, 680, 1280, 100);

    //sonidos
    buttonHold=new Music("resources/buttonhold.wav",false,5);
    buttonPress=new Music("resources/buttonpress.wav",false,5);
}

//se pintan los sprites con sus interpolados
void MenuStatus::render(float percenTick){
    //SCROLLING

    //capa 0
    capa0->draw();

    //interpolando
    //capa 2
    capa2_x = capa2_lastX*(1-percenTick) + capa2_newX*percenTick;
    capa2->setPosition(capa2_x,0);

    if(capa2_x>=-2560 && capa2_x<=1280){ //si esta dentro de la pantalla dibujar
        capa2->draw();
    }

    capa2_copia_x = capa2_copia_lastX*(1-percenTick) + capa2_copia_newX*percenTick;
    capa2_copia->setPosition(capa2_copia_x,0);

    if(capa2_copia_x>=-2560 && capa2_copia_x<=1280){ //si esta dentro de la pantalla dibujar
        capa2_copia->draw();
    }

    //capa 3
    capa3_x = capa3_lastX*(1-percenTick) + capa3_newX*percenTick;
    capa3->setPosition(capa3_x,0);

    if(capa3_x>=-2560 && capa3_x<=1280){ //si esta dentro de la pantalla dibujar
        capa3->draw();
    }

    capa3_copia_x = capa3_copia_lastX*(1-percenTick) + capa3_copia_newX*percenTick;
    capa3_copia->setPosition(capa3_copia_x,0);

    if(capa3_copia_x>=-2560 && capa3_copia_x<=1280){ //si esta dentro de la pantalla dibujar
        capa3_copia->draw();
    }

    //capa 4
    capa4_x = capa4_lastX*(1-percenTick) + capa4_newX*percenTick;
    capa4->setPosition(capa4_x,0);

    if(capa4_x>=-2560 && capa4_x<=1280){ //si esta dentro de la pantalla dibujar
        capa4->draw();
    }

    capa4_copia_x = capa4_copia_lastX*(1-percenTick) + capa4_copia_newX*percenTick;
    capa4_copia->setPosition(capa4_copia_x,0);

    if(capa4_copia_x>=-2560 && capa4_copia_x<=1280){ //si esta dentro de la pantalla dibujar
        capa4_copia->draw();
    }



     //capa 1
    capa1_x = capa1_lastX*(1-percenTick) + capa1_newX*percenTick;
    capa1->setPosition(capa1_x,0);

    if(capa1_x>=-2560 && capa1_x<=1280){ //si esta dentro de la pantalla dibujar
        capa1->draw();
    }

    capa1_copia_x = capa1_copia_lastX*(1-percenTick) + capa1_copia_newX*percenTick;
    capa1_copia->setPosition(capa1_copia_x,0);

    if(capa1_copia_x>=-2560 && capa1_copia_x<=1280){ //si esta dentro de la pantalla dibujar
        capa1_copia->draw();
    }


    //brujita
    //interpolacion y
    actualYw = lastYw*(1-percenTick) + newYw*percenTick;
    witch->setPosition(300, actualYw);
    witch->draw();

        //menu->draw();

    //INTERFAZ
    jugarBoton->draw();
    nuevaBoton->draw();
    salirBoton->draw();
    tutorialBoton->draw();
    title->draw();
    footer->draw();
}

//para actualizar el menu
void MenuStatus::update(float time){
    Motor2D *motor = Motor2D::Instance();
    sf::Vector2i posRaton = sf::Mouse::getPosition((*motor->getWindow()));

    //HOVER DE LOS BOTONES

    if(nuevaBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
        if(nuevaBoton->getActualSprite()==0){
            buttonHold->Play();
        }
        nuevaBoton->setActualSprite(1);
    }else{
        nuevaBoton->setActualSprite(0);
    }
    if(jugarBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
        if(jugarBoton->getActualSprite()==0){
            buttonHold->Play();
        }
        jugarBoton->setActualSprite(1);
    }else{
        jugarBoton->setActualSprite(0);
    }
    
    if(salirBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
        if(salirBoton->getActualSprite()==0){
            buttonHold->Play();
        }
        salirBoton->setActualSprite(1); 
    }else{
        salirBoton->setActualSprite(0); 
    }

    if(tutorialBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
        if(tutorialBoton->getActualSprite()==0){
            buttonHold->Play();
        }
        tutorialBoton->setActualSprite(1); 
    }else{
        tutorialBoton->setActualSprite(0); 
    }

    //INTERPOLACIONES

    //SCROLLING

    //capa1
    capa1_lastX = capa1_newX;
    capa1_newX += -velScroll*time;

    capa1_copia_lastX = capa1_copia_newX;
    capa1_copia_newX += -velScroll*time;

    if(capa1_x < -2560){ //cuando se acabe el sprite moverlo
        capa1_newX = capa1_copia_newX+2560;
        capa1_lastX = capa1_copia_newX+2560;
    }

    if(capa1_copia_x < -2560){ //cuando se acabe el sprite moverlo
        capa1_copia_newX = capa1_newX+2560;
        capa1_copia_lastX = capa1_newX+2560;
    }

    //capa2
    capa2_lastX = capa2_newX;
    capa2_newX += -velScroll*1.5*time;

    capa2_copia_lastX = capa2_copia_newX;
    capa2_copia_newX += -velScroll*1.5*time;

    if(capa2_x < -2560){ //cuando se acabe el sprite moverlo
        capa2_newX = capa2_copia_newX+2560;
        capa2_lastX = capa2_copia_newX+2560;
    }

    if(capa2_copia_x < -2560){ //cuando se acabe el sprite moverlo
        capa2_copia_newX = capa2_newX+2560;
        capa2_copia_lastX = capa2_newX+2560;
    }

    //capa 3
    capa3_lastX = capa3_newX;
    capa3_newX += -velScroll*4*time;

    capa3_copia_lastX = capa3_copia_newX;
    capa3_copia_newX += -velScroll*4*time;

    if(capa3_x < -2560){ //cuando se acabe el sprite moverlo
        capa3_newX = capa3_copia_newX+2560;
        capa3_lastX = capa3_copia_newX+2560;
    }

    if(capa3_copia_x < -2560){ //cuando se acabe el sprite moverlo
        capa3_copia_newX = capa3_newX+2560;
        capa3_copia_lastX = capa3_newX+2560;
    }

    //capa 4
    capa4_lastX = capa4_newX;
    capa4_newX += -velScroll*8*time;

    capa4_copia_lastX = capa4_copia_newX;
    capa4_copia_newX += -velScroll*8*time;

    if(capa4_x < -2560){ //cuando se acabe el sprite moverlo
        capa4_newX = capa4_copia_newX+2560;
        capa4_lastX = capa4_copia_newX+2560;
    }

    if(capa4_copia_x < -2560){ //cuando se acabe el sprite moverlo
        capa4_copia_newX = capa4_newX+2560;
        capa4_copia_lastX = capa4_newX+2560;
    }

    //brujita

    int altura = 20;
    float taller = altura*time;

    //interpolacion y
    if(upW && actualYw>=330){
        upW = false;
    } else 
        if(!upW && actualYw<=320){
            upW=true;
        }

    if(!upW && actualYw>=320){
        taller = -taller;
    }

    lastYw=newYw;
    newYw = lastYw + taller;
}

//controlar los eventos
void MenuStatus::handle(){
sf::Event event;
    Motor2D *motor = Motor2D::Instance();
    Shop *shop = Shop::Instance();
     while (motor->getWindow()->pollEvent(event)) {
        switch (event.type) {
            default:break;
            case sf::Event::Closed:
                motor->getWindow()->close();
            break;

            case sf::Event::MouseButtonReleased:

                sf::Vector2i posRaton = sf::Mouse::getPosition((*motor->getWindow()));

                if(event.mouseButton.button == sf::Mouse::Left){
            
                    if(salirBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){ //cerrar el juego
                        buttonPress->Play();
                        motor->closeWindow();
                    }

                    if(nuevaBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){ //boton de nueva partida, lleva al tutorial
                        //Buscamos save y si hay archivo se borra
                        buttonPress->Play();
                        borrarPartida();
                        shop->reset();
                        shop->setStatus(TutorialStatus::Instance());
                    }

                    if(jugarBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){ //boton para jugar
                        buttonPress->Play();
                        GameStatus::Instance()->resetDatos();
                        cargar();
                        shop->setMenu(false);
                        shop->setStatus(GameStatus::Instance());
                    }

                    if(tutorialBoton->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){ //tutorial
                        buttonPress->Play();
                        shop->setStatus(TutorialStatus::Instance());
                    }
                }
        
            break;
        }
    }
}
