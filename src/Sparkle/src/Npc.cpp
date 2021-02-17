#include "Npc.h"
#include "Shop.h"

int Npc::lastNpcType = -1;

Npc::Npc(bool troll){

    //Leemos el JSON para crear los npc de manera aleatoria
    string line,datos,file;

    if(troll){
        file = "src/trollData.json";
    } else {
        file = "src/npcData.json";
    }
        
    ifstream myfile (file);

    if (myfile.is_open()){
        while ( getline (myfile,line) ){
            datos+= line;
        }

        myfile.close();

        Document npcData;

        char * aux = new char[datos.length()+1];
        strcpy(aux,datos.c_str());

        npcData.Parse(aux);

        //se generan dos numeros aleatorios
        srand(time(0));

        int npcRand;

        do { //PARA QUE NO SALGAN MUCHOS NPCs DEL MISMO SEGUIDOS
            npcRand = rand()%5;
        } while(npcRand == lastNpcType);

        tipoTroll = npcRand;
        //lastNPC es una variable para que no salgan NPC del mismo tipo todo el rato
        lastNpcType = npcRand;

        int questRand;
        
        //elegimos cual es de la lista
        if(troll){
            questRand = (rand()%1)+1;
        } else {
            questRand = (rand()%8)+1;
        } 

        //id para acceder al JSON
        string s = std::to_string(npcRand);
        char *idNpc = new char[s.size() + 1];
        strcpy ( idNpc, s.c_str() );
        //char const *idNpc = s.c_str();
        
        //Nos guardamos las filas y columnas de todas los npc para animarlo más tarde
        //filas
        vector<int> vRows;

        for (SizeType i = 0; i < npcData[idNpc]["row"].Size(); i++){
            vRows.push_back(npcData[idNpc]["row"][i].GetInt());    
        }

        //columnas
        vector<int> vCols;

        for (SizeType i = 0; i < npcData[idNpc]["col"].Size(); i++){
            vCols.push_back(npcData[idNpc]["col"][i].GetInt());    
        }

        //Sprite aleatorio

        int ranSprite = rand()%4+1;

        //creamos el sprite 
        sprite = new Sprite(npcData[idNpc]["sprite"].GetString()+to_string(ranSprite)+".png",vCols,vRows,POS_INI_X,POS_INI_Y,TAM_X,TAM_Y);


        //cogemos la mision
        string q = std::to_string(questRand);
        char *idQuest = new char[q.size() + 1];
        strcpy ( idQuest, q.c_str() );
        //char const *idQuest = q.c_str();

        quest = Text(npcData[idNpc]["quest"][idQuest].GetString());
        quest.setPosition(575,190); //posicion de la mision
        quest.setColorWhite();

        //Este formato nos permite incluir cualquier cantidad de misiones mientras sigan el orden
        questRand=questRand%4;
        if(questRand==0)
            questRand = 4; //el tipo 4 %4 siempre será el 0

        typeQuest = questRand; 
 

        //se obtiene la recompensa de manera aleatoria
        int rewardMax = npcData[idNpc]["moneyMax"].GetInt(); 
        reward = rand()%(rewardMax - (rewardMax/2) + 1)+ (rewardMax/2);

        //si es troll se hace prob para ver si te engaña o te paga
        float prob = (1+rand()%100)/100;
        if(prob > 0.7){
            reward = reward*(-1);
        }

        delete aux;
        delete idNpc;
        delete idQuest;
        aux = NULL;
        idNpc   = NULL;
        idQuest = NULL;

        estado = 1;

        dialogBox = new Sprite("resources/dialog.png",0,0,775,250,500,350);

        accept = new Sprite("resources/accept.png",{0,1},{0,0},675,320,100,50);
        cancel = new Sprite("resources/cancel.png",{0,1},{0,0},875,320,100,50);  

        accepted = false;

        //num de NPC a los que engañar
        if(troll) {
            numTroll = 2+rand()%5;
        } else {
            numTroll = -1;
        }

    } else{
        cout << "Unable to open file" << endl;
    }
    //Cargamos las posiciones iniciales
    actualX = POS_INI_X;
    lastX = POS_INI_X;
    newX = lastX;

    actualY = POS_INI_Y;
    lastY = POS_INI_Y;
    newY = lastY;

    up = true;
    troleando = troll;
    
    //cargar musica
    ring=new Music("resources/ding.wav",false,10);
}

Npc::~Npc(){
    delete sprite;
    delete dialogBox;
    delete accept;
    delete cancel;
    delete ring;
    

    sprite = NULL;
    dialogBox = NULL;
    accept = NULL;
    cancel = NULL;
    ring= NULL;
   
}

void  Npc::update(float time){
    int velocidad = 100;
    int altura = 20;
    float add = velocidad*time;
    float taller = altura*time;

    //segun el estado del NPC se comporta de formas distintas
    switch (estado)
    {
        case 0: //El npc está quieto
            estado = 0;
            sprite->setActualSprite(2);
            break;
        case 1: //El npc se esta desplazando hacia el mostrador
            if(actualX<400){ //Movimiento para la interpolacion
                if(reloj.getTimeAsSecond()>0.75f){
                    sprite->setActualSprite(5);
                    reloj.restartTime();
                }else{
                    if(reloj.getTimeAsSecond()>0.35f)
                    sprite->setActualSprite(0);
                }
                //interpolacion x
                lastX = newX;
                newX = lastX + add;
                //interpolacion y
                if(up && actualY>=405){
                    up = false;
                } else 
                    if(!up && actualY<=400){
                        up=true;
                    }
                if(!up && actualY>=400){
                    taller = -taller;
                }
                lastY=newY;
                newY = lastY + taller;
            }else{
                //llama cuando llega
                ring->Play();
                estado = 0;
            }
            
            break;
        case 2: //Cuando te esta hablando de la mision
            if(!accepted){
                if(reloj.getTimeAsSecond()>0.25){
                    estado = sprite->speak();
                    reloj.restartTime();
                }
                    newX=actualX;
                    newY=actualY;
                    lastX=actualX;
                    lastY=actualY;                
            } else {
                sprite->setActualSprite(2);
            }
            break;
        case 3://El npc se esta desplazando hacia fuera de la tienda
            if(actualX>POS_INI_X){
                if(reloj.getTimeAsSecond()>0.75f){
                    sprite->setActualSprite(6);
                    reloj.restartTime();
                }else{
                    if(reloj.getTimeAsSecond()>0.35f)
                    sprite->setActualSprite(1);
                }
                //interpolacion x
                lastX = newX;
                newX = lastX - add;

                //interpolacion y

                if(up && actualY>=405){
                    up = false;
                } else 
                    if(!up && actualY<=400){
                        up=true;
                    }

                if(!up && actualY>=400){
                    taller = -taller;
                }

                lastY=newY;
                newY = lastY + taller;

            }else{
                estado = 5;
            }

            break;
            default:break;
    }

    Motor2D *motor = Motor2D::Instance();
    sf::Vector2i posRaton = sf::Mouse::getPosition((*motor->getWindow()));
    
    //hacemos el update por si pone el raton encima de los botones (HOVER)
    if(accept->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
      
        accept->setActualSprite(1); 
    }else{
       
        accept->setActualSprite(0); 
    }

    if(cancel->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
        
        cancel->setActualSprite(1); 
    }else{
      
        cancel->setActualSprite(0); 
    }
}


//Interpolacion del NPC si se encuentra moviendose
void Npc::actualizarNpc(float percenTick){
    if(!Shop::Instance()->getMenu() && ((estado == 1 && actualX<400) || (estado == 3 && actualX>POS_INI_X))){
        //interpolacion x
        actualX = lastX*(1-percenTick) + newX*percenTick;
        //interpolacion y
        actualY = lastY*(1-percenTick) + newY*percenTick;

        sprite->setPosition(actualX, actualY);
            
    }
}

void  Npc::render(float percenTick){

    actualizarNpc(percenTick);

    sprite->draw();
    //comprueba si tiene que tener el dialogo o no
    if(estado == 2){
        dialogBox->draw();
        quest.draw(); 

        if(!accepted){
            accept->draw();
            cancel->draw();
        }
    }
}