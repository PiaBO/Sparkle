#include "Shop.h"

Shop* Shop::shop = 0;

//crear el singleton
Shop* Shop::Instance()
{
    if(shop == 0)
    {
        shop = new Shop;
    }

    return shop;
}

//para inicializar las variables de la tienda asi como el sonido
Shop::Shop(){
    money = 50;
    prestige = 0;
    levelPrestige = 0;
    numFire = 3;
    numEarth = 3;
    numAir = 3;
    numWater = 3;
    day = 1;
    hour = 10;
    menu = true;
    iniciado = false;
    status.push_back(MenuStatus::Instance());

    musica=new Music("resources/Base.wav",true,35);
    musica->Play();
}

//para cambiar de estado
void Shop::setStatus(Status* pStatus){
    status.pop_back();
    status.push_back(pStatus); 
}

//para agregar un nuevo estado a la pila
void Shop::addStatus(Status* pStatus){
    status.push_back(pStatus);
}

//quitar el ultimo estado de la pila
void Shop::removeStatus(){
    status.pop_back();
}

//renderizar los estados de la pila
void Shop::render(float percenTick){
    bool isGameStatus = false;

    Motor2D::Instance()->clearWindow();
    for(Status *stat : status ){
        stat->render(percenTick);

        if(dynamic_cast<GameStatus*>(stat)){
            isGameStatus = true;
        }
    }

    if(!isGameStatus && !menu){ //para que se siga actualizando el npc aunque no este en game status y vaya a su posicion
        Npc *npc = GameStatus::Instance()->getNpc();
        if(npc!=NULL){
            npc->actualizarNpc(percenTick);
        }
    }
    
}

void Shop::render(){ //PARA EL CASO DE LOS QTE QUE NO NECESITAN EL PERCENTICK PERO LLAMAN A SHOP
    float percen = 0;
    Motor2D::Instance()->clearWindow();
    for(Status *stat : status ){
        stat->render(percen);
    }

    /*Npc *npc = GameStatus::Instance()->getNpc();
    if(npc!=NULL){
        npc->actualizarNpc(0.5);
    }*/
}

//el manejador de eventos sera el del ultimo estado en la pila
void Shop::handle(){
    status[status.size()-1]->handle();
}

//actualizar la tienda
void Shop::update(float time){
    bool isGameStatus = false;
    bool isQte = false;

    //reiniciar la hora de la tienda
    if(hour == 10 && !iniciado){
        clock.restartTime();
        iniciado = true;
    }

    //actualizamos la hora
    if(!menu){ //para que no avance el tiempo cuando estás en el menu
        if(clock.getTimeAsSecond()>24.0f){
            hour+= clock.getTimeAsSecond()/24;
            clock.restartTime();
        }
        //comprobamos si ha acabado el dia
        if(hour>=22){

            //se mira si esta un qte activo, para no cortarlo antes de tiempo
            for(Status *stat : status){
                if(dynamic_cast<AguaQteStatus*>(stat)){
                    isQte = true;
                }else if(dynamic_cast<FuegoQteStatus*>(stat)){
                    isQte = true;
                }else if(dynamic_cast<TierraQteStatus*>(stat)){
                    isQte = true;
                }else if(dynamic_cast<AireQteStatus*>(stat)){
                    isQte = true;
                }
            }

            //en el caso de que no haya ningun qte se da por finalizado el dia
            if(!isQte){
                setMenu(true);
                setStatus(EndMenuStatus::Instance());
                GameStatus *game = GameStatus::Instance();
                game->clearDrops();
                game->setQuest(false);
                game->deleteNPC();
                game->setSprites();
                game->deleteAlert();
                levelPrestige = KitchenStatus::Instance()->setSprites();
                day++;
                iniciado = false;
            }

        }

        //hacemos el update del stat
        for(Status *stat : status ){
            stat->update(time);

            if(dynamic_cast<GameStatus*>(stat)){
                isGameStatus = true;
            }
        }

        if(!isGameStatus && !menu){ //NECESITAMOS QUE EL NPC SE ACTUALICE SIEMPRE PARA QUE NO SE VAYA DE SU POSICION NI HAGA COSAS RARAS
            Npc *npc = GameStatus::Instance()->getNpc();
            if(npc!=NULL){
                npc->update(time);
            }
        }
    }else{ //para no hacer trampas en el tiempo
        status.back()->update(time); 
        clock.restartTime();
    }
}

//para cambiar el prestigio de la tienda
void Shop::setPrestige(int num){
    prestige +=  num-1;
    if(prestige<0) prestige=0;
}

//para sumar una cantidad al numero de esencias del tipo que llega por parametro
void Shop::addEssence(int type,int quantity){
    
    switch (type)
    {
    case 0:
    numWater+=quantity;
        break;
    case 1:
    numFire+=quantity;
        break;
    case 2:
    numAir+=quantity;
        break;
    case 3:
    numEarth+=quantity;
        break;
    default:break;
    }

}

//para quitar una cantidad a la esencia del tipo del parametro
void Shop::removeEssence(int type,int quantity){
 switch (type)
    {
    case 0:
    numWater-=quantity;
        break;
    case 1:
    numFire-=quantity;
        break;
    case 2:
    numAir-=quantity;
        break;
    case 3:
    numEarth-=quantity;
        break;
    default:break;
    }
}

//para coger el valor del tipo de esencia que llega por parametro
int Shop::getEssence(int type){
    switch (type){
    case 0:
        return numWater;
        break;
    case 1:
       return numFire;
        break;
    case 2:
       return numAir;
        break;
    case 3:
        return numEarth;
        break;
    default:
        return 0;
    break;
    }
}

//para sustituir la cantidad de esencias del tipo que llega por parametro
void Shop::setEssence(int type,int quantity){
    switch (type){

    case 0:
        numWater=quantity;
    break;

    case 1:
       numFire=quantity;
    break;

    case 2:
       numAir=quantity;
    break;

    case 3:
        numEarth=quantity;
    break;
    default:break;
    }  
}

//para reiniciar las variables de la tienda
void Shop::reset(){
    money = 50;
    prestige = 0;
    levelPrestige = -1;
    GameStatus::Instance()->setSprites();
    KitchenStatus::Instance()->setSprites();
    numFire = 3;
    numEarth = 3;
    numAir = 3;
    numWater = 3;
    day=1;
    hour= 10;
    menu = true;
    iniciado = false;
    setStatus(MenuStatus::Instance());

}