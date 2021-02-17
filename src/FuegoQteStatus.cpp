#include "FuegoQteStatus.h"
#include "Shop.h"

FuegoQteStatus* FuegoQteStatus::status = 0;

//creacion del singleton
FuegoQteStatus* FuegoQteStatus::Instance()
{
    if(status == 0)
    {
        status = new FuegoQteStatus;
    }

    return status;
}

//creacion de los sprites que no cambian y el sonido de la rana 
FuegoQteStatus::FuegoQteStatus():Status(){
    if (!status) {
        status = this;
    }

    caldero = new Sprite("resources/calderoRojo.png", {0,1,2,3,4}, {0,0,0,0,0}, 400, 500, 315, 270);
    calderoFondo = new Sprite("resources/calderoRojoFondo.png", 0, 0, 400, 500, 315, 270);
    rana = new Sprite("resources/rana.png", {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},{0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8},830,392.5,920,175);
    //calculo posicion rana
      //x = 920/2+170=630
      //y = 175/2+305=392.5
    libros = new Sprite("resources/libros.png",0,0,912,530,156,164);
    completado = new Sprite("resources/completed.png",0,0,640,360,1280,720);

    croak=new Music("resources/Musica/rana.wav",false,30);
  
  
}


//metodo para controlar los eventos, tanto para jugar como para salir del QTE
void FuegoQteStatus::handle(){
    sf::Event event;
    Shop * shop = Shop::Instance();
    Motor2D *motor = Motor2D::Instance();

    while (motor->getWindow()->pollEvent(event)) {

      switch (event.type) {

        case sf::Event::Closed:
          motor->getWindow()->close();
        break;

        case sf::Event::KeyReleased:
          if(event.key.code==sf::Keyboard::Escape){
              shop->removeStatus();
              shop->setStatus(GameStatus::Instance());
          }

          if(event.key.code==sf::Keyboard::Space && rana->getActualSprite()>=4 && !catched){
            esencias = 2; 
            catched=true;
            croak->Play();
            relojEspera.restartTime();

            //calcula tambien cuantas esencias deben de darte segun el tiempo que tarde en reaccionar
            if(tiempo.getTimeAsSecond()<0.6)
              esencias = 3; 

            if(tiempo.getTimeAsSecond()<0.2)
              esencias = 4; 
             
          }

        break;

      default:break;
      }

   
    }
}

//pinta los sprites que salen en este QTE
void FuegoQteStatus::render(float percenTick){
    text.draw();
    calderoFondo->draw();
    libros->draw();
    rana->draw();
    caldero->draw();

    if(catched){
      completado->draw();
    }
}

//actualiza el QTE, pasando los sprites de la animacion de la rana y del caldero
void FuegoQteStatus::update(float time){
    caldero->fade();
    Shop * shop = Shop::Instance();
    if(clock.getTimeAsMilli()>tiempoRand && (!catched || (catched && relojEspera.getTimeAsSecond()>0.5))){
      rana->disapear(); 

      //se reinicia el tiempo para calcular el num de esencias
      if(rana->getActualSprite()==4){
        tiempo.restartTime();
      }
    }

    //tiempo de espera antes de volver a la tienda
    if(relojEspera.getTimeAsSecond()>1.5&&catched){
      shop->addEssence(1,esencias);
      shop->removeStatus();
      shop->setStatus(GameStatus::Instance());
      cin.clear();
      string reward = "Has conseguido " + to_string(esencias) + " esencias de\nFuego.";
      GameStatus::Instance()->createAlert(reward);
    }
}

//ponemos el QTE a su estado inicial antes de empezarlo
void FuegoQteStatus::load(){
    tecla = 0;
    esencias = 2;
    catched=false;
    texto = "¡La rana se quiere escapar!\nAyúdanos a atraparla pulsando la barra espaciadora en cuanto la veas.";
    text.setString(texto);
    text.setPosition(100,70);
    text.setColorWhite();
    text.setSize(22);
    
    //el tiempo que tarde la rana en salir sera aleatorio
    tiempoRand = random()%1000+2000;
    rana->setPosition(830,392.5);
    rana->setActualSprite(0);
    tiempo.restartTime(); //para calcular cuanto tardas en darle
    clock.restartTime(); //de espera de la rana para salir
}