#include "AguaQteStatus.h"
#include "Shop.h"

AguaQteStatus* AguaQteStatus::status = 0;

//metodo para iniciar el singleton
AguaQteStatus* AguaQteStatus::Instance()
{
    if(status == 0)
    {
        status = new AguaQteStatus;
    }

    return status;
}

//contructor para crear el QTE, se crean los sprites que no van a cambiar nunca y el sonido de la gota que cae al agua
AguaQteStatus::AguaQteStatus():Status(){
    if (!status) {
        status = this;
    }

    vector <int> col={0,1,2,3};
    vector<int> fil={0,0,0,0};
    gota = new Sprite("resources/gota.png",col,fil,600,250,64,64);
    col={0,1,2,3,4};
    fil={0,0,0,0,0};
    pot = new Sprite("resources/calderoAzul.png",col,fil,600,550,315,270);
    sonidogota=new Music("resources/waterpoof.wav",false,3);

}

//metodo para controlar los eventos, tanto para jugar como para salir del QTE
void AguaQteStatus::handle(){
    Motor2D *motor = Motor2D::Instance();
    Shop *shop = Shop::Instance();
    sf::Event event;

    while (motor->getWindow()->pollEvent(event)) {

      if(event.type == sf::Event::KeyReleased){
        if(event.key.code==sf::Keyboard::Escape){
          shop->removeStatus();
          shop->setStatus(GameStatus::Instance());
        }
      }

      if(event.type == sf::Event::TextEntered){
        //cout << event.text.unicode << endl;

        //no se utiliza el keyReleased porque no funciona con mayusculas
        if(event.text.unicode==(unsigned)tecla+65||event.text.unicode==(unsigned)tecla+97){
          tiempoTecla = tiempo.getTimeAsMilli();
        }
      }

      if(event.type == sf::Event::Closed){
        motor->getWindow()->close();
      }    
    }
}

//renderizamos los sprites y el texto que aparece en pantalla
//para la gota se calcula interpolacion
void AguaQteStatus::render(float percenTick){
    Motor2D * motor = Motor2D::Instance();
    titulo.draw();
    text.draw();
    y = lasty*(1-percenTick) + newy*percenTick;
    gota->setPosition(600,y);
    pot->draw();
    if(start && !fin){
        if(posSprite>-1)
        motor->drawSprites(gota->getSprite(posSprite));
    }
}

//metodo de actualizar el QTE
void AguaQteStatus::update(float time){
    pot->fade();

    //esta parte se utiliza para realizar una cuenta atras
    if(!start){
        if(reloj.getTimeAsSecond()>4){
                
            start = true;
            tiempo.restartTime();
            relojGota.restartTime();
            text.setString(" ");

        } else 
            if(reloj.getTimeAsSecond()>3){

                text.setString("1");
                text.setSize(80);

            } else 
                if(reloj.getTimeAsSecond()>2){

                    text.setString("2");
                    text.setSize(70);

                } else 
                    if(reloj.getTimeAsSecond()>1){

                        text.setSize(60);
                        text.setString("3");

                    }
    }
    
    //mientras no se ha acabado el QTE, van cayendo las gotas y se calcula los tiempos que se tarda en reaccionar para calcular luego el numero de esencias que va a ganar
    if(start && !fin){

        lasty=newy;
        float porcentaje = relojGota.getTimeAsMilli()/(float)pulsos;
        newy = 200+porcentaje*300;

        //se mira en que posicion se encuentra la gota para crear la animacion
        if(newy > 450)
            newy=450;
        if(newy<250)
            posSprite=0;
        else if(newy<440)
            posSprite=1;
        else if(porcentaje<0.9)
            posSprite=2;
        else if(porcentaje>=0.9 && porcentaje<=1){

            sonidogota->Play();
            posSprite=3;
        }
        else
            posSprite=-1;

        if(pulsaciones>6 && tiempo.getTimeAsMilli()>pulsos/2){
            posSprite = -1;
        }

        if(relojGota.getTimeAsMilli()-tiempo.getTimeAsMilli()<pulsos/2 && relojGota.getTimeAsMilli()-tiempo.getTimeAsMilli()>=0)
            tiempo.restartTime();

        if(tiempo.getTimeAsMilli()<pulsos/2){
            con=true;
            actualizar=true;
          
        }else{
            if(tiempoTecla>0 && relojGota.getTimeAsMilli()>=1000){
                relojGota.restartTime();
                lasty=200;
                newy=200;
                
            }
            if(con){
                if(tiempoTecla>0 && tiempoTecla>pulsos/2-70)
                    tiempoTecla+= (pulsos/2-tiempoTecla)*0.5;
                tiempoPulso = tiempo.getTimeAsMilli();
                con=false;
                //cout << "Pulso" << endl;
            }
            
            if(actualizar && tiempo.getTimeAsMilli()>pulsos*3/4 && tiempoTecla>0){
                float dif = tiempoPulso - tiempoTecla;

                if(dif<0)
                    dif = dif *-1;

                tiempoMedia+=dif;
                actualizar=false;
                pulsaciones++;
                tiempoTecla=-1;
                tiempo.restartTime();
            }
       
        }

        if(pulsaciones>7){
            posSprite = -1;
            fin=true;
            reloj.restartTime();
        }

        //cout << "Reloj:" << tiempo.getTimeAsMilli() << "  Gota:" <<relojGota.getTimeAsMilli() << endl;
    }

    //cuando a acabado se calcula el tiempo medio que ha tardado para decir asi que recompensa se ha ganado y lo devolvemos a la tienda
    if(fin){
        posSprite = -1;
        tiempoMedia = tiempoMedia/6;
        if(tiempoMedia<140+pulsos/300)
            esencias = 4;
        else if(tiempoMedia < 240+pulsos/300)
            esencias=3;
        else
            esencias=2;

        Shop *shop = Shop::Instance();
        if(reloj.getTimeAsSecond()>1){
            shop->addEssence(0, esencias);
            shop->removeStatus();
            cin.clear();
            shop->setStatus(GameStatus::Instance());
                if(esencias>0){
                    string reward = "Has conseguido " + to_string(esencias) + " esencias de\nAgua.";
                    GameStatus::Instance()->createAlert(reward);
                }
        }


    }
}


//para volver a poner el QTE en su estado inicial antes de empezar
void AguaQteStatus::load(){
    con = true;
    actualizar = true;
    fin = false;
    start = false;
    esencias = 2;
    posSprite = 0;
    pulsaciones = 0;
    tiempoPulso = 0;
    tiempoTecla = 0;
    tiempoMedia = 0;

    text.setPosition(580,280);

    pulsos = 800 + rand()%25*50;
    tecla = rand()%17;

    texto = "Sigue el ritmo pulsando la letra ";
    texto+= char(tecla+65);
    
    titulo.setString(texto);
    titulo.setPosition(320,70);
    titulo.setSize(35);

    reloj.restartTime();
    tiempo.restartTime();
}