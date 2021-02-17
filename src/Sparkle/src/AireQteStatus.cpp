#include "AireQteStatus.h"
#include "Shop.h"

AireQteStatus* AireQteStatus::status = 0;

//metodo para iniciar el singleton
AireQteStatus* AireQteStatus::Instance()
{
    if(status == 0)
    {
        status = new AireQteStatus;
    }

    return status;
}

//contructor para crear el QTE, se crea el objeto caldero y el sonido de cuando se coge un objeto
AireQteStatus::AireQteStatus():Status(){
    if (!status) {
        status = this;
    }

    srand(time(0));

    pot = new Pot();
    sonidoCoger=new Music("resources/sonidocaer.wav",false,5);

}

//metodo para controlar los eventos, tanto para jugar como para salir del QTE
void AireQteStatus::handle(){
    Motor2D *motor = Motor2D::Instance();
    Shop *shop = Shop::Instance();
    sf::Event event;

    while (motor->getWindow()->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyReleased:
                switch (event.key.code){
                    case sf::Keyboard::Escape:
                        shop->removeStatus();
                        shop->setStatus(GameStatus::Instance());
                    break;
                    case sf::Keyboard::Left:
                        if(pot->getSide()!=1)
                            pot->setSide(0);
                        
                    break;
                    case sf::Keyboard::Right:
                        if(pot->getSide()!=-1)
                            pot->setSide(0);
            
                            
                    break;
                    default:break;
                }
            break;
            case sf::Event::KeyPressed:
                switch (event.key.code){
                    case sf::Keyboard::Left:
                        pot->setSide(-1);
                    break;
                    case sf::Keyboard::Right:
                        pot->setSide(1);
                    break;
                    default:break;
                }
            break;
            

            case sf::Event::Closed:
                motor->getWindow()->close();
            break;

            default:break;
        }
    }
}


//renderizamos los sprites y el texto que aparece en pantalla, en el caso de catched el string va cambiando junto con la variable cogidos
//todos los objetos que cae se hace por medio de interpolación
void AireQteStatus::render(float percenTick){

    pot->render(percenTick);

    for(int i=0;(unsigned) i<objects.size(); i++){
        objects[i].y = objects[i].lastY*(1-percenTick) + objects[i].newY*percenTick;
        objects[i].sprite->setPosition(objects[i].x, objects[i].y);
        objects[i].sprite->draw();
    }

    //texto con la explicacion inicial
    if(timeAcum<2){
        text.draw();
    }

    catched.setString(texto + to_string(cogidos));
    catched.draw();

}

//metodo para actualizar el QTE
void AireQteStatus::update(float time){

    timeAcum += time;
    float velocidad = 150;
    
    //actualizamos la posicion de todos los objetos que caen, que solo se mueven en vertical
    if(clock.getTimeAsSecond()>(unsigned)1.5){
        for(int i=0; i<objects.size(); i++){
            objects[i].lastY = objects[i].newY;

            if(!objects[i].catched)
                objects[i].newY += velocidad*time;
            else
                objects[i].newY -= velocidad*time/4;

            if(objects[i].sprite->getSprite().getGlobalBounds().intersects(pot->getGlobalBounds()) && !objects[i].catched){
                sonidoCoger->Play();
                cogidos ++;
                objects[i].catched=true;              
                quedan --;
            } else {
                if(!objects[i].catched && objects[i].y>550+rand()%100){
                    quedan --;//esto sera cuando colisione con la mesa
                    objects[i].catched=true;
                }
            }

            //en el caso de ser capturado o de llegar al limite inferior de la mesa, se hace la animacion de desaparecer el objeto
            if(objects[i].catched){
              objects[i].sprite->disapear();
            }

        }
    }

    //se llama a la funcion de actualizar del caldero para que se mueva
    pot->update(time);

    //tiempo de espera antes de volver a la tienda
    if(quedan<=0 && endClock.getTimeAsSecond()>2){
        endClock.restartTime();
    }

    //se calcula cuantas esencias debe ganar en funcion de cuantos objetos haya cogido del final
    if(quedan<=0 && endClock.getTimeAsSecond()>1.5){
        Shop *shop = Shop::Instance();

        if(cogidos/(float) numObjects >=0.8){
            esencias = 4;
        } else 
            if(cogidos/(float) numObjects >=0.5){
                esencias = 3;
            }

        shop->addEssence(2, esencias);

        shop->removeStatus();
        cin.clear();
        shop->setStatus(GameStatus::Instance());

        string reward = "Has conseguido " + to_string(esencias) + " esencias de\nAire.";
        GameStatus::Instance()->createAlert(reward);

    }    
    
}

//para volver a poner el QTE en su estado inicial antes de empezar
void AireQteStatus::load(){


    for(int i=0; (unsigned)i<objects.size(); i++){ //eliminamos los punteros a sprite
        delete objects[i].sprite;
    }
    timeAcum = 0;

    //reseteamos objects
    objects.clear();
    
    esencias = 2;
    text.setPosition(100,70);
    text.setSize(22);
    text.setString("Intenta meter todos los objetos posibles en la olla");

    //contador
    cogidos = 0;
    texto = "Puntuación: ";
    catched.setSize(30);
    catched.setString(texto + to_string(cogidos));
    catched.setPosition(970,50);

    //CALDERO
    pot->resetPosition();

    //el numero de objetos sera variable entre 7 y 16
    srand(time(0));
    numObjects = 7 + rand()%10;
    quedan = numObjects;

    //vector con los objetos + animacion de desaparecer
    vector<int> row;
    vector<int> column;
    row.push_back(0);
    column.push_back(0);
    row.push_back(8);
    column.push_back(0);
    row.push_back(8);
    column.push_back(1);
    row.push_back(8);
    column.push_back(2);
    row.push_back(8);
    column.push_back(3);
    row.push_back(8);
    column.push_back(4);
    row.push_back(8);
    column.push_back(5);
    row.push_back(8);
    column.push_back(6);
    row.push_back(8);
    column.push_back(7);
    row.push_back(9);
    column.push_back(0);
    row.push_back(9);
    column.push_back(1);
    row.push_back(9);
    column.push_back(2);
    row.push_back(9);
    column.push_back(3);
    row.push_back(9);
    column.push_back(4);

    //para cada objeto creamos el sprite y calculamos una posicion inicial variable tanto de x como de y, para que haya aleatoriedad en la posicion de los objetos
    for(int i=0; i<numObjects; i++){
        int rowRand = rand()%8;
        int columnRand = rand()%8;
        int xRand = 128 + rand()%1024; //los objetos miden 64, pero para que no se vayan muy a los bordes
        int yRand = 100 + rand()%30;
        row[0]=rowRand;
        column[0]=columnRand;
        Object aux;
        aux.sprite = new Sprite("resources/food.png", column, row, xRand, -100-yRand*i, 64, 64);
        aux.x = xRand;
        aux.lastY = -100-yRand*i;
        aux.newY = -100-yRand*i;
        aux.y = -100-yRand*i;
        aux.catched = false;
        objects.push_back(aux);
    }
}