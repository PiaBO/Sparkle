#include "GameStatus.h"
#include "Shop.h"
#include "libroStatus.h"
#include "MenuInGameStatus.h"

GameStatus* GameStatus::status = 0;

//crear el singleton
GameStatus* GameStatus::Instance()
{
    if(status == 0)
    {
        status = new GameStatus;
    }

    return status;
}

//se crea la instancia
GameStatus::GameStatus():Status(){
    if (!status) {
        status = this;
    }


    string line,datos;
    ifstream myfile ("src/PrestigeGame.json");
    if (myfile.is_open()){

        while ( getline (myfile,line) ){
            datos+= line;
        }

        myfile.close();

        char * aux = new char[datos.length()+1];
        strcpy(aux,datos.c_str());

        //se guarda los datos para los distintos prestigios en la variable prestige, que servira para cambiar los sprites del fondo y la mesa segun el prestigio
        prestige.Parse(aux);
        assert(prestige.IsObject());

        back = new Sprite(prestige["0"]["back"].GetString(), 0, 0, 640, 360, 1280, 720);
        table = new Sprite(prestige["0"]["table"].GetString(), 0, 0, 640, 360, 1280, 720);
       
        quest = false;

        //SPRITES INTERFAZ
        botonMenu = new Sprite("resources/botones/BotonesMenu.png", {0,1}, {0,0}, 1245,35,50,50);
        botonMenu->setActualSprite(0);
        interfazTop = new Sprite("resources/interfaz.png", 0, 0, 640,360,1280,720);
  //      interfazRight = new Sprite("resources/interfazLado.png", 0, 0, 1170,360,221,720);
        misionesSprite = new Sprite("resources/pergamino.png",{0,1},{0,0},1175,125,91,88);
        libroSprite = new Sprite("resources/libro.png",{0,1},{0,0},1175,600,150,150);
        //libroSprite->setScale(0.66,0.66);

        //SPRITES POCIONES
        vector<string> potionNames = {"resources/pociones/pocionAgua.png","resources/pociones/pocionFuego.png","resources/pociones/pocionAire.png","resources/pociones/pocionTierra.png"};
        vector<vector<int>> potionPos = {{350,550},{450,550},{550,550},{650,550}};
        vector<int> potionWidth = {94,82,99,68};
        vector<string> esenciaNames = {"resources/esenciaAgua.png","resources/esenciaFuego.png","resources/esenciaAire.png","resources/esenciaTierra.png"};
        vector<vector<int>> esenciaPos = {{1140,225},{1140,285},{1150,337},{1150,385}};
        
        for(unsigned i=0;i<potionNames.size();i++){
            potions.push_back(new Sprite(potionNames[i], {0,1,2,3,4,5,6}, {0,0,0,0,0,0,0}, potionPos[i][0], potionPos[i][1], potionWidth[i], 210));
        }

        //la pocion que se va rellenando
        potions.push_back(new Sprite("resources/pociones/pocionPrincipal.png", {0,1,2,3}, {0,0,0,0}, 800, 550, 58, 120));

        //esencias del HUD
        for(unsigned i=0;i<esenciaNames.size();i++){
            esencias.push_back(new Sprite(esenciaNames[i], {0,1,2,3,4,5,6,7,8,9}, {0,0,0,0,0,0,0,0,0,0}, esenciaPos[i][0],esenciaPos[i][1], 50, 50));
        }

        delete aux;
        aux = NULL;

        //sonidos de la tienda
        buttonHold=new Music("resources/buttonhold.wav",false,5);
        buttonPress=new Music("resources/buttonpress.wav",false,5);
        abrirLibro=new Music("resources/Musica/libro.wav",false,30);
        coin=new Music("resources/Musica/moneda.wav",false,30);
            
    } else {
        cout << "Unable to open file" << endl;
    }


    timeBetweenUpdate = 0;
    timeBetweenUpdate1 = 0;
    animacionPotis = 0;
    animacionGato = 0;

    //probamos a crear aqui un npc
    //npc = new Npc();
    npc = NULL;

    //calculamos cuantos dias tienen que pasar para que venga un npc troll (npc de mision)
    calculeDayTroll();

    missionsOpen = false;

    //gato
    gatoSprite = new Sprite("resources/gato.png", {0,1,2,3,4,5,6,7,8,9,10,11,12}, {0,0,0,0,0,0,0,0,0,0,0,0,0}, 110, 470, 256, 256);
}

//metodo para dibujar todo el texto de la interfaz
void GameStatus::drawTextHud(){
        Shop* shop = Shop::Instance();

        //texto de la interfaz para gastar solo 1 variable texto lo hacemos aqui
        string resumeText ="Día "+ to_string(shop->getDay());
        Text text= Text(resumeText);
        text.setPosition(55, 15);
        text.draw();  

        //money
        resumeText ="Dinero: "+ to_string(shop->getMoney())+"$";
        text.setString(resumeText);
        text.setPosition(450, 15);
        text.draw();

        //el reloj se tendra que poner en tienda para saber la hora supongo
        resumeText ="Hora: "+ to_string(shop->getHour())+":00";
        text.setString(resumeText);
        text.setPosition(850, 15);
        text.draw();
        
        //esencias
        resumeText ="x"+ to_string(shop->getEssence(0));
        text.setString(resumeText);
        text.setPosition(1200, 225);
        if(shop->getEssence(0)==0){
          text.setColorRed();
        } else {
          text.setColorWhite();
        }
        text.draw();


        resumeText ="x"+ to_string(shop->getEssence(1));
        text.setString(resumeText);
        text.setPosition(1200, 280);
        if(shop->getEssence(1)==0){
          text.setColorRed();
        } else {
          text.setColorWhite();
        }
        text.draw();


        resumeText ="x"+ to_string(shop->getEssence(2));
        text.setString(resumeText);
        text.setPosition(1200, 330);
        if(shop->getEssence(2)==0){
          text.setColorRed();
        } else {
          text.setColorWhite();
        }
        text.draw();


        resumeText ="x"+ to_string(shop->getEssence(3));
        text.setString(resumeText);
        text.setPosition(1200, 390);
        if(shop->getEssence(3)==0){
          text.setColorRed();
        } else {
          text.setColorWhite();
        }
        text.draw();

        //texto del libro
        /*resumeText ="Libro";
        text.setString(resumeText);
        text.setPosition(1000, 450);
        text.draw();*/
}

//pinta los sprites que se ven en la tienda
void GameStatus::render(float percenTick){
    Shop* shop = Shop::Instance();
    back->draw();
    if(npc!=NULL){
        npc->render(percenTick);
    }
    
    table->draw();
    interfazTop->draw();
 //   interfazRight->draw();
    botonMenu->draw();
    libroSprite->draw();
    gatoSprite->draw();

    misionesSprite->draw();

    if(missionsOpen){
      missions.render();
    }

    //el metodo de drawhud esta en shop y pintaria la interfaz cada vez que se hace el render de la tienda asi que tendra las variables actualziadas
    drawTextHud();
    
    if(quest){
      for(unsigned i=0;i<potions.size();i++){
          potions[i]->draw();
      }
    }

    for(unsigned i=0;i<esencias.size();i++){
      esencias[i]->draw();
    }  

    //alertas
    if(alert!=NULL){
      alert->draw();
    }
}

//metodo para actualizar la tienda
void GameStatus::update(float time){
    Motor2D *motor = Motor2D::Instance();
    Shop * shop = Shop::Instance();
    sf::Vector2i posRaton = sf::Mouse::getPosition((*motor->getWindow()));

    //para crear o eliminar un npc cuando termine, ademas de para crear un npc troll cuando llegue el dia Troll
    if(npc!= NULL){
      if(npc->getStatus()!=5){
        npc->update(time);
      }
      else
      {
          delete npc;
          npc = NULL;
      }
    } else {

      if(lastDayTroll+dayTroll == shop->getDay()){
        calculeDayTroll();

        if(missions.getSize()<5){ //PARA NO ALCANZAR EL MAX DE 5 MISIONES 
          npc = new Npc(true);
        } else {
          npc = new Npc(false);
        }
      } else {
        npc = new Npc(false);
      }

    }

    //para actualizar las alarmas y eliminarla cuando desaparezca
    if(alert!=NULL){
      if(alert->getStatus()){
        alert->update();
      }else{
        delete alert;
        alert = NULL;
      }
    }


    //para el hover del boton del menu
    if(botonMenu->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){

        if(botonMenu->getActualSprite()==0){ //sonido
            buttonHold->Play();
        }
        botonMenu->setActualSprite(1);
    }else{
        botonMenu->setActualSprite(0);
    }

    timeBetweenUpdate += time;

    //animacion parpadeo del libro
    if(timeBetweenUpdate>1){
      //para el libro cuando hay nueva receta
      if(LibroStatus::Instance()->getNew()){
        if(libroSprite->getActualSprite()==0){
          libroSprite->setActualSprite(1);
        } else{
          libroSprite->setActualSprite(0);
        }
      }

      timeBetweenUpdate = 0;

    } else {
      if(!LibroStatus::Instance()->getNew() && libroSprite->getActualSprite()==1){ //para que cuando deje de tener uno nuevo que se ponga en el 0
        libroSprite->setActualSprite(0);
      }
    }


  timeBetweenUpdate1 += time;

  //para desvanecer
  if(timeBetweenUpdate1>0.13){
    //para esencia agua cuando no quede
    if(shop->getEssence(0)==0){
      esencias[0]->fade();
    }

    //para esencia fuego cuando no quede
    if(shop->getEssence(1)==0){
      esencias[1]->fade();
    }

    //para esencia aire cuando no quede
    if(shop->getEssence(2)==0){
      esencias[2]->fade();
    }

    //para esencia tierra cuando no quede
    if(shop->getEssence(3)==0){
      esencias[3]->fade();
    }

    timeBetweenUpdate1 = 0;

  } else { //para ponerlo en el primer sprite cuando queden de nuevo
    if(shop->getEssence(0)>0 && esencias[0]->getActualSprite()!=0){
      esencias[0]->setActualSprite(0);
    }

    if(shop->getEssence(1)>0 && esencias[1]->getActualSprite()!=0){
      esencias[1]->setActualSprite(0);
    }

    if(shop->getEssence(2)>0 && esencias[2]->getActualSprite()!=0){
      esencias[2]->setActualSprite(0);
    }

    if(shop->getEssence(3)>0 && esencias[3]->getActualSprite()!=0){
      esencias[3]->setActualSprite(0);
    }
  }

  //para que cambie el sprite del pergamino
  if(missionsOpen){
    misionesSprite->setActualSprite(1);
  } else {
    misionesSprite->setActualSprite(0);
  }

  //animacion de las pociones
  animacionPotis += time;

  if(shop->getEssence(0)==0){
    potions[0]->setActualSprite(6);
  } else {
    if(animacionPotis > 0.3)
      potions[0]->cycle();
  }

  if(shop->getEssence(1)==0){
    potions[1]->setActualSprite(6);
  } else {
    if(animacionPotis > 0.3)
      potions[1]->cycle();
  }

  if(shop->getEssence(2)==0){
    potions[2]->setActualSprite(6);
  } else {
    if(animacionPotis > 0.3)
      potions[2]->cycle();
  }

  if(shop->getEssence(3)==0){
    potions[3]->setActualSprite(6);
  } else {
    if(animacionPotis > 0.3)
      potions[3]->cycle();
  }

  if(animacionPotis > 0.3)
    animacionPotis = 0;

  //animacion gato
  animacionGato += time; 
  
  if(animacionGato > 0.35){
    gatoSprite->cycle();
    animacionGato = 0;
  }

  //cuando hayas fabricado la pocion y pasen 0.35s entonces el npc se ira y te dara tu recompensa en funcion de la calidad de la pocion y de tu nivel de prestigio
  if(drops.size()==3 && wait.getTimeAsSecond()>=0.35){
    LibroStatus *libro = LibroStatus::Instance();
    int res = libro->comprobarPocion(drops,npc->getQuestType());

    //miramos si hay misiones de este tipo y actualizamos
    if(res==0){
      missions.update(npc->getTypeTroll());
    }
    int reward = npc->getReward();
    shop->setPrestige(res);
    shop->addMoney(res*reward+shop->getLevelPrestige()*10);

    //solo suena el sonido de la moneda cuando la recompensa es distinta de 0
    if(res*reward+shop->getLevelPrestige()*10!=0){
      coin->Play();
    }

    //reseteamos las gotas para volver a empezar con otro cliente
    drops.clear();
    potions[4]->setActualSprite(drops.size());
    npc->setStatus(3); //3 es que se vaya
    quest=false;
  }   
}

//metodo para manejar todos los eventos, tanto para jugar o cerrar el juego
void GameStatus::handle(){
  Shop *shop = Shop::Instance();
    sf::Event event;
    Motor2D *motor = Motor2D::Instance();
    LibroStatus *libro = LibroStatus::Instance();
    
    while (motor->getWindow()->pollEvent(event)) {
      switch (event.type) {       
        case sf::Event::Closed:
          motor->getWindow()->close();
        break;

        case sf::Event::KeyReleased: 
        
          switch (event.key.code) {
            case sf::Keyboard::Escape: //salga el menu
              shop->setMenu(true);
              shop->addStatus(MenuInGameStatus::Instance());
            break;

            case sf::Keyboard::Q: //DEBUG
              shop->addMoney(100);
            break;
            case sf::Keyboard::W: //DEBUG
              shop->addEssence(0,100);
              shop->addEssence(1,100);
              shop->addEssence(2,100);
              shop->addEssence(3,100);
            break; 
            case sf::Keyboard::P: //DEBUG
              shop->setPrestige(8);
              setSprites();
              int level = KitchenStatus::Instance()->setSprites();
              shop->setLevelPrestige(level);
            break; 

          }
        break;
        case sf::Event::TextEntered:
          if(event.text.unicode==76||event.text.unicode==108){ //LETRA L: que se abra el libro
            deleteAlert();
            abrirLibro->Play();
            shop->setStatus(LibroStatus::Instance());
            LibroStatus::Instance()->setNew();
          } else
              if(event.text.unicode==83||event.text.unicode==115){ //LETRA S //DEBUG
                shop->setHour(21);
                shop->restartTime();
              } else
                  if(event.text.unicode==77||event.text.unicode==109){ //LETRA M: que se habra las misiones
                    abrirLibro->Play();
                    if(missionsOpen){
                      missionsOpen = false;
                      abrirLibro->Play();
                    } else {
                      missionsOpen = true;
                      abrirLibro->Play();
                    }
                  }
        break;
        case sf::Event::MouseButtonReleased:
          
          if(event.mouseButton.button == sf::Mouse::Left){

            sf::Vector2i posRaton = sf::Mouse::getPosition((*motor->getWindow()));

            //para capturar el tipo de gota en la que esta pulsando
            if(quest && drops.size()<3){
              //Gota tipo : 1
              if(potions[0]->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)&&shop->getEssence(0)>0){
                shop->removeEssence(0,1);
                drops.push_back(1);
                potions[4]->setActualSprite(drops.size());
                wait.restartTime();
              //Gota tipo : 2
              }else if(potions[1]->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)&&shop->getEssence(1)>0){
              shop->removeEssence(1,1);
                drops.push_back(2);
                potions[4]->setActualSprite(drops.size());
                wait.restartTime();
              //Gota tipo : 3            
              }else if(potions[2]->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)&&shop->getEssence(2)>0){
                shop->removeEssence(2,1);
                drops.push_back(3);
                potions[4]->setActualSprite(drops.size());
                wait.restartTime();
              //Gota tipo : 4             
              }else if(potions[3]->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)&&shop->getEssence(3)>0){
                shop->removeEssence(3,1);
                drops.push_back(4);
                potions[4]->setActualSprite(drops.size());
                wait.restartTime();
              }
            } 
                

            //CREAR ESENCIAS: te lleva a su respectivo QTE
            if(esencias[0]->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
            //agua
              shop->setStatus(KitchenStatus::Instance());
              AguaQteStatus::Instance()->load();
              shop->addStatus(AguaQteStatus::Instance());
            }else if(esencias[1]->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
              shop->setStatus(KitchenStatus::Instance());
              FuegoQteStatus::Instance()->load();
              shop->addStatus(FuegoQteStatus::Instance());
            }else if(esencias[2]->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
              shop->setStatus(KitchenStatus::Instance());  
              AireQteStatus::Instance()->load();
              shop->addStatus(AireQteStatus::Instance());  
            }else if(esencias[3]->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
              shop->setStatus(KitchenStatus::Instance());
              TierraQteStatus::Instance()->load();
              shop->addStatus(TierraQteStatus::Instance());
            }else if(libroSprite->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){ //abrir libro
              deleteAlert();
              abrirLibro->Play();
              shop->setStatus(LibroStatus::Instance());
              LibroStatus::Instance()->setNew();
            }else if(botonMenu->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){ //abrir el menu in game
              buttonPress->Play();
              shop->setMenu(true);
              shop->addStatus(MenuInGameStatus::Instance());
            }else if(misionesSprite->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){ //abrir el libro de misiones
              if(missionsOpen){
                missionsOpen = false;
                abrirLibro->Play();
              } else {
                missionsOpen = true;
                abrirLibro->Play();
              }
            }

            //caso npc
            if(npc!=NULL){
              if(npc->getStatus()==0 && !quest){
                if(npc->getSprite()->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){ //para que hable y nos muestre la comanda
                  npc->setStatus(2);
                }
              }else 
                if(npc->getStatus()==2){
                  if(npc->getCancel()->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){ //para cancelar la comanda
                    npc->setStatus(3);
                  }
                  if(npc->getAccept()->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){ //para aceptar la comanda

                    if(npc->isTroll()){ //en el caso de que sea troll se agrega una nueva mision
                      missions.addMission(npc->getTypeTroll(), npc->getNumTroll(), npc->getReward());
                      npc->setStatus(3);
                    } else { //en caso contrario salen las pociones
                      npc->acceptQuest();
                      quest=true;
                    }
                  }
                }
            }
          }
        break;
        default:break;
      }
    }
}

//metodo para cambiar los sprites segun el nivel de prestigio de la tienda
int GameStatus::setSprites(){
    
    int nivelPrestige = 0; 
    
    int num = Shop::Instance()->getPrestige();

    //encontramos 5 niveles distintos, hace falta diferentes puntos de prestigio para alcanzar esos niveles.
    if(num>=0 && num<8){
        nivelPrestige=0;
    } else if(num<24){
        nivelPrestige=1;
    } else if(num<40){
        nivelPrestige=2;
    } else if(num<56){
        nivelPrestige=3;
    } else {
        nivelPrestige=4;
    }

    //busca en el json que hemos creado en el constructor si existe ese nivel (en el caso de que sea distinto al nivel actual)
    if(Shop::Instance()->getLevelPrestige()!=nivelPrestige){
    //para pasarlo a char* para poder usarlo en la función HasMember
        string s = std::to_string(nivelPrestige);
        //char const *pchar = s.c_str();
        char *pchar = new char[s.size() + 1];
        strcpy (pchar, s.c_str() );

        if(prestige.HasMember(pchar)){
            back->setTexture(prestige[pchar]["back"].GetString());
            table->setTexture(prestige[pchar]["table"].GetString());
            alert = new Alert("Subes de prestigio\nObtendrás más recompensas");
        }

        delete pchar;
        pchar=NULL;
    }

    return nivelPrestige;

}

//metodo para crear alertas en la esquina superior izquierda
void GameStatus::createAlert(string text){
  alert = new Alert(text);
}

//para eliminar el npc y borrar el puntero
void GameStatus::deleteNPC(){
  if(npc!=NULL){
    delete npc;
    npc = NULL;
  }
}

//para calcular el siguiente dia en el que tiene que salir un npc troll
void GameStatus::calculeDayTroll(){
  lastDayTroll = Shop::Instance()->getDay();
  dayTroll = (rand()%3)+2; //mirar balanceo
}

//para vaciar las gotas con las que se crean las esencias que se dan a los clientes
void GameStatus::clearDrops(){
  drops.clear();

  potions[4]->setActualSprite(drops.size());
}

//para agregaar una nueva mision
void GameStatus::addMission(int type, int num, int reward,int troleados){
  missions.addMission(type,num,reward,troleados);
}

//para eliminar las misiones 
void GameStatus::resetDatos(){
  missions.clearMissions();
}

