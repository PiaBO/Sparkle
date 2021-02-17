#include "KitchenStatus.h"
#include "Shop.h"

KitchenStatus* KitchenStatus::status = 0;

//crear singleton
KitchenStatus* KitchenStatus::Instance()
{
    if(status == 0)
    {
        status = new KitchenStatus;
    }

    return status;
}

//crear la instancia, esta sera el fondo que se vera en todos los QTE
KitchenStatus::KitchenStatus():Status(){
    if (!status) {
        status = this;
    }

    //los datos que se van a utilizar para cambiar el fondo y la mesa segun el prestigio de la tienda se almacena en el json llamado prestige
    string line,datos;
    ifstream myfile ("src/PrestigeKitchen.json");
    if (myfile.is_open()){
        
        while ( getline (myfile,line) ){
            datos+= line;
        }

        myfile.close();

        char * aux = new char[datos.length()+1];
        strcpy(aux,datos.c_str());

        prestige.Parse(aux);
        assert(prestige.IsObject());

        back = new Sprite(prestige["0"]["back"].GetString(), 0, 0, 640, 360, 1280, 720);

        table = new Sprite(prestige["0"]["table"].GetString(), 0, 0, 640, 405, 1280, 720);

        delete aux;
        aux = NULL;

    } else {
        cout << "Unable to open file" << endl;
    }
}

//pintas los sprites que se ven en la cocina
void KitchenStatus::render(float percenTick){
    back->draw();
    table->draw();
}

//para eliminar la alerta al entrar en la cocina
void KitchenStatus::update(float time){  
    deleteAlert(); 
}

//el manejador que se usa en este caso es el de cada uno de los qte
void KitchenStatus::handle(){
}


//metodo para cambiar los sprites segun el nivel de prestigio de la tienda
int KitchenStatus::setSprites(){
    
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
        }

        delete pchar;
        pchar = NULL;
    }

    return nivelPrestige;

}
