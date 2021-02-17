#include "EndMenuStatus.h"
#include "Shop.h"

EndMenuStatus* EndMenuStatus::status = 0;

//para iniciar el singleton
EndMenuStatus* EndMenuStatus::Instance()
{
    if(status == 0)
    {
        status = new EndMenuStatus;
    }

    return status;
}

//se crean los sprites necesarios, se almacena los eventos en un json, y calcula un dia random para que pase un evento
EndMenuStatus::EndMenuStatus():Status(){
    if (!status) {
        status = this;
    }

    back = new Sprite("resources/finBueno.png", 0, 0, 640, 360, 1280, 720);
    finBueno = true;

    string line,datos;

    ifstream myfile ("src/eventsData.json");

    if (myfile.is_open()){
      while ( getline (myfile,line) ){
          datos+= line;
      }

      myfile.close();

      char * aux = new char[datos.length()+1];
      strcpy(aux,datos.c_str());

      //PRESTIGE ES EL JSON QUE TIENEN LOS ESTADOS
      prestige.Parse(aux);

      delete aux;
      aux = NULL;
    }

    //iniciamos la variable de la ultima vez que hubo un evento como el primer dia del juego
    lastDayEvent = 1;

    //para que pase un evento tienen que pasar como minimo 3 dias
    srand(time(0));
    dayRand = (rand()%6)+3;

    menu = new Sprite("resources/botones/BotonMenu.png",{0,1},{0,0},200,550,200,50);
    continuar = new Sprite("resources/botones/BotonContinuar.png",{0,1},{0,0},200,550,200,50);

    buttonHold=new Music("resources/buttonhold.wav",false,5);
    buttonPress=new Music("resources/buttonpress.wav",false,5);
}

//se pinta el fondo dependiendo de si ha perdido o sigue jugando, asi como un resumen de con cuanto dinero ha terminado el dia, cual es el precio del alquiler y con cuanto dinero se queda
void EndMenuStatus::render(float percenTick){
    Shop* shop = Shop::Instance();
    
    back->draw();

    string resumeText;
    Text text = Text();

    if(shop->getMoney()<0){
        resumeText ="Has perdido";
        text.setString(resumeText);
        text.setSize(80);
        text.setPosition(400, 80);
        text.draw();
    } 

    resumeText ="Resumen del dia "+to_string(shop->getDay()-1);
    text.setString(resumeText);
    text.setSize(40);
    text.setPosition(105, 280);
    text.draw();

    int pos = 0;
    text.setSize(18);

    //si hay algun evento lo pinto en pantalla tambien
    if(eventText.size()>0){
      for(unsigned i=0; i<eventText.size(); i++){
        eventText[i]->draw();
      }
      pos = 80;
    }

    //dinero antes de pagar
    resumeText ="Dinero: "+ to_string(dineroAntes)+"$";
    text.setString(resumeText);
    
    text.setPosition(105, 350+pos);
    text.draw();

    //lo que se resta
    resumeText ="Alquiler: "+ to_string(alquiler)+"$";
    text.setString(resumeText);
    text.setPosition(105, 380+pos);
    text.draw();

    //lo que queda de dinero
    resumeText ="Dinero restante: "+ to_string(shop->getMoney())+"$";
    text.setString(resumeText);
    text.setPosition(105, 410+pos);
    text.draw();

    //guia para salir
    /*resumeText ="Pulsa k para continuar";
    text.setString(resumeText);
    text.setPosition(385, 275+pos);
    text.draw();*/

    //dependiendo de si has perdido o no te sale un boton para volver al menu o para pasar al siguiente dia
    if(!finBueno){
      menu->draw();
    } else {
      continuar->draw();
    }
    
}

//metodo para actualizar el menu
void EndMenuStatus::update(float t){
    Shop* shop = Shop::Instance();
    Motor2D *motor = Motor2D::Instance();
    sf::Vector2i posRaton = sf::Mouse::getPosition((*motor->getWindow()));

    if(shop->getHour()==22){ //solo lo hace la primera vez que entra al menu

        shop->setMenu(true);

        srand(time(0));
        dineroAntes= shop->getMoney();

        //que nos quite x dinero al final de cada dia segun el nivel de prestigio
        alquiler = 25 + shop->getLevelPrestige()*7;

        //si es el dia que tiene que haber un evento(en funcion del ultimo dia que hubo un evento y cuantos dias tenian que pasar para el siguiente), calcula cual sera y cuanto le va a dar/quitar
        if(lastDayEvent+dayRand == shop->getDay())
          randomEvent();

        //le resta el dinero del alquiler
        shop->addMoney(-alquiler);
        shop->restartTime();
        shop->setHour(10);

        //dependiendo de si ha ganado o perdido le ponemos una textura al boton
        if(shop->getMoney()<0 && finBueno){
          back->setTexture("resources/finMalo.png");
          finBueno = false;
        } else 
            if(shop->getMoney()>=0 && !finBueno){ //para que vuelva a colocar el bueno en caso de que no se actualice con la nueva partida
              back->setTexture("resources/finBueno.png");
              finBueno = true;
            }
    }

    //para hacer el hover de los botones
    if(!finBueno){
      if(menu->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){

        if(menu->getActualSprite()==0){ //sonido del boton
            buttonHold->Play();
        }
        menu->setActualSprite(1);
      }else{
        menu->setActualSprite(0);
      } 
    } else {
      if(continuar->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){

        if(continuar->getActualSprite()==0){ // sonido del boton
            buttonHold->Play();
        }
        continuar->setActualSprite(1);
      }else{
        continuar->setActualSprite(0);
      } 
    }
}

//metodo para controlar los eventos, asi como para llevarte a la tienda o al menu dependiendo de si has perdido o no
void EndMenuStatus::handle(){
    Shop *shop = Shop::Instance();
    sf::Event event;
    Motor2D *motor = Motor2D::Instance();
    
    while (motor->getWindow()->pollEvent(event)) {
      switch (event.type) {       
        case sf::Event::Closed:
          motor->getWindow()->close();
        break;

        case sf::Event::TextEntered: 

          //pueden pulsar la f para salir del menu
          if(event.text.unicode==70||event.text.unicode==102){ //LETRA F
            if(!finBueno){
              shop->setStatus(MenuStatus::Instance());
            }else{
              shop->setStatus(GameStatus::Instance());
              shop->setMenu(false);
            }

            //si ha habido algun evento se elimina
            if(eventText.size()>0){
              delete eventText[0];
              delete eventText[1];
              eventText[0]=NULL;
              eventText[1]=NULL;
              eventText.clear();
            }
          }
        break;

        case sf::Event::MouseButtonReleased:
            
            if(event.mouseButton.button == sf::Mouse::Left){
                sf::Vector2i posRaton = sf::Mouse::getPosition((*motor->getWindow()));
                if(!finBueno){
                  if(menu->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
                    buttonPress->Play();
                      shop->reset();
                      shop->setStatus(MenuStatus::Instance());
                  }
                } else {
                  if(continuar->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
                    buttonPress->Play();
                    shop->setStatus(GameStatus::Instance());
                    shop->setMenu(false);
                  }
                }

                //si ha habido algun evento se elimina
                if(eventText.size()>0){
                  delete eventText[0];
                  delete eventText[1];
                  eventText[0]=NULL;
                  eventText[1]=NULL;
                  eventText.clear();
                } 
            }
        break;

        default:break;
      }
    }

}

//metodo que se invoca para crear el evento aleatorio
//sus datos estan almacenados en el json llamado prestige y se coge un evento aleatorio con un random
void EndMenuStatus::randomEvent(){
    srand(time(0));
    int eventRand = rand()%20;

    //id para acceder al JSON
    string s = std::to_string(eventRand);
    char *idEvent = new char[s.size() + 1];
    strcpy ( idEvent, s.c_str() );

    eventText.push_back(new Text(prestige[idEvent]["event"].GetString()));
    eventText[0]->setPosition(105,350);

    int payment = prestige[idEvent]["money"].GetInt();

    //descontamos el dinero
    Shop::Instance()->addMoney(payment);

    string frase;

    if(payment>0){
      frase = "Ganas " + to_string(payment) + "$";
    } else {
      frase = "Pierdes " + to_string(payment) + "$";
    }

    eventText.push_back(new Text(frase));
    eventText[1]->setPosition(105,380);

    //actualizamos el rand y el lastDay
    lastDayEvent = Shop::Instance()->getDay();
    dayRand = (rand()%6)+3;

}
