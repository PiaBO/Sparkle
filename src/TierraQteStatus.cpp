#include "TierraQteStatus.h"
#include "Shop.h"
#include <chrono> 
#include <thread> 

using namespace std::this_thread;  
using namespace std::chrono;
TierraQteStatus* TierraQteStatus::status = 0;
//para que sea singleton
TierraQteStatus* TierraQteStatus::Instance()
{
    if(status == 0)
    {
        status = new TierraQteStatus;
    }

    return status;
}
//Inicializamos las posiciones de las flechas del qte y creamos sprites
TierraQteStatus::TierraQteStatus():Status(){
    if (!status) {
        status = this;
    }
    posicionesX.push_back(1450);
    posicionesY.push_back(360);
    posicionesX.push_back(-170);
    posicionesY.push_back(360);
    posicionesX.push_back(620);
    posicionesY.push_back(-170);
    posicionesX.push_back(620);
    posicionesY.push_back(890);

    vector<int> rows;
    vector<int> columns;
    rows.push_back(0);
    rows.push_back(0);
    columns.push_back(0);
    columns.push_back(1);

    bruja = new Sprite("resources/brujaCaldero.png", columns, rows, 700, 360, 386, 582);

    batir=new Music("resources/sonidocaer.wav",false,10);
  
}
//controlador de los eventos que suceden en el qte
void TierraQteStatus::handle(){
    Motor2D *motor = Motor2D::Instance();
    Shop *shop = Shop::Instance();
    sf::Event event;

    while (motor->getWindow()->pollEvent(event)) {

      switch (event.type) {

        case sf::Event::Closed:
          motor->getWindow()->close();
        break;

        case sf::Event::KeyReleased:
          switch (event.key.code){

          case sf::Keyboard::Escape://para salir del qte sin completarlo
            shop->removeStatus();
            shop->setStatus(GameStatus::Instance());
          break;//comprobamos que las flechas que pulsan son las correctas si lo son la bruja bate
          case sf::Keyboard::Right:
            if(teclas[pos]==0){
              batir->Play();
              out=true;
              pause=false;
              velocidad=1800;
            }
          break;
          case sf::Keyboard::Left:
           if(teclas[pos]==1){
              batir->Play();
              out=true;
              pause=false;
              velocidad=1800;
            }
          break;
          case sf::Keyboard::Up:
           if(teclas[pos]==2){
              batir->Play();
              out=true;
              pause=false;
              velocidad=1800;
            }
          break;
          case sf::Keyboard::Down:
           if(teclas[pos]==3){
              batir->Play();
              out=true;
              pause=false;
              velocidad=1800;
            }
          break;
          default:break;
        }
        break;
        default:break;
      }
    }
}
//pintar los sprites del qte
void TierraQteStatus::render(float percenTick){

  if(tiempo.getTimeAsSecond()<2)
    text.draw();

  bruja->draw();

  x = lastx*(1-percenTick) + newx*percenTick;
  y = lasty*(1-percenTick) + newy*percenTick;
  spritesTeclas[pos]->setPosition(x,y);
  spritesTeclas[pos]->draw();

}

void TierraQteStatus::update(float time){
  if(tiempo.getTimeAsSecond()>2){//interpolamos las flechas para que se vean correctamente
  
    if(direccion[pos]==0 && !pause){//las flechas aparecen interpolandose y en sus respectivas direcciones
      lastx=newx;
      newx -= velocidad*time;
      if(x<=620 && !out){
        pause=true;
        lastx=x;
        newx=x;
      }else if(out && x<=-170){
        pos++;
        velocidad=700;
        out=false;
        if(pos<4){
          newx= posicionesX[direccion[pos]];
          newy= posicionesY[direccion[pos]];
          lastx = newx;
          lasty = newy;
          x= newx;
          y=newy;
        }
      }
    }else if(direccion[pos]==1 && !pause){
      lastx=newx;
      newx += velocidad*time;
      if(x>=620 && !out){
        pause=true;
        lastx=x;
        newx=x;
      }else if(out && x>=1450){
        pos++;
        velocidad=700;
        out=false;
        if(pos<4){
          newx= posicionesX[direccion[pos]];
          newy= posicionesY[direccion[pos]];
          lastx = newx;
          lasty = newy;
          x= newx;
          y=newy;
        }
      }
    }else if(direccion[pos]==2 && !pause){
      lasty=newy;
      newy += velocidad*time;

      if(y>=360 && !out){
        pause=true;
        lasty=y;
        newy=y;
      }else if(out && y>=890){
        pos++;
        velocidad=700;
        out=false;
        if(pos<4){
          newx= posicionesX[direccion[pos]];
          newy= posicionesY[direccion[pos]];
          lastx = newx;
          lasty = newy;
          x= newx;
          y=newy;
        }
      }
    }else if(direccion[pos]==3 && !pause){
      lasty=newy;
      newy -= velocidad*time;
      if(y<=360 && !out){
        pause=true;
        lasty=y;
        newy=y;
      }else if(out && y<=-170){
        pos++;
        velocidad=700;
        out=false;
        if(pos<4){
          newx= posicionesX[direccion[pos]];
          newy= posicionesY[direccion[pos]];
          lastx = newx;
          lasty = newy;
          x= newx;
          y=newy;
        }
      }
    }

    timeAcum += time;
    if(out){

      if(timeAcum>=0.18){
        bruja->fade();
        timeAcum=0;
      }
    }

  }

  if(pos>3){ //miramos el tiempo que ha tardado y damos las recompensas en cuanto a el
    if(tiempo.getTimeAsSecond()<8.2)
        esencias = 3; 

    if(tiempo.getTimeAsSecond()<7.4)
        esencias = 4; 
    Shop *shop = Shop::Instance();
    sleep_until(system_clock::now() + seconds(2));
    shop->addEssence(3, esencias);
    shop->removeStatus();
    cin.clear();
    shop->setStatus(GameStatus::Instance());
    string reward = "Has conseguido " + to_string(esencias) + " esencias de\nTierra.";
    GameStatus::Instance()->createAlert(reward);
  }


}

//metodo para cargar el qte cuando se inicia
void TierraQteStatus::load(){
    //limpiamos antes de jugar
    teclas.clear();
    direccion.clear();
    for(unsigned int i=0;i<spritesTeclas.size();i++)
      delete spritesTeclas[i];
    spritesTeclas.clear();

    pos = 0;
    teclas.push_back(rand()%4); 
    teclas.push_back(rand()%4); 
    teclas.push_back(rand()%4); 
    teclas.push_back(rand()%4);

    velocidad = 700;
    pause = false;
    out=false;
    for(unsigned int i=0;i<4;i++){//volvemos a crear las teclas aleatoriamente
      int random = rand()%4;
      spritesTeclas.push_back(new Sprite("resources/teclas.png",teclas[i],0,posicionesX[random],posicionesY[random],128,128));
      direccion.push_back(random); // 0 right 1 left 2 up 3 down
    }
    x = posicionesX[direccion[0]];
    lastx = posicionesX[direccion[0]];
    newx = posicionesX[direccion[0]];
    y = posicionesY[direccion[0]];
    lasty = posicionesY[direccion[0]];
    newy = posicionesY[direccion[0]];

    esencias = 2;
    text.setSize(22);
    text.setPosition(100,80);
    texto = "Pulsa las teclas que aparecen en la pantalla";
    text.setString(texto);
    tiempo.restartTime();
    timeAcum=0;
}
