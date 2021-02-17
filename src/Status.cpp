#include "Status.h"
#include "Shop.h"

//Mensajes de alerta del juego
Alert* Status::alert = NULL;


Status::Status(){
}

void Status::guardar(){
  //Se crea un JSON en el que se guardan los datos de la partida actual
  Shop *shop = Shop::Instance();

  Document d;
  d.Parse("{}");

  //añadimos los datos que queremos guardar
  d.AddMember("money",shop->getMoney(),d.GetAllocator());
  d.AddMember("prestige",shop->getPrestige(),d.GetAllocator());
  d.AddMember("day",shop->getDay(),d.GetAllocator());
  d.AddMember("hour",shop->getHour(),d.GetAllocator());

  //Guardamos los diferentes datos de la partida

  //Esencias
  Value esen(rapidjson::kArrayType);
  for(unsigned int i=0;i<4;i++)
      esen.PushBack(shop->getEssence(i),d.GetAllocator());
      
  d.AddMember("essences",esen,d.GetAllocator());

  //Libro de recetas
  Value poc(rapidjson::kArrayType);
  Document::AllocatorType& allocator = d.GetAllocator();
  Document p,ata,def,mag,med;
  LibroStatus *libro = LibroStatus::Instance();

  for(int i=0;i<20;i++){
    Value nombre(rapidjson::kStringType);
    nombre.SetString(libro->getRecetas()[i]->nombre.c_str(),allocator);

    p.SetObject();
    p.AddMember("nombre",nombre,p.GetAllocator());
      
    ata.SetObject();
    ata.AddMember("efecto",libro->getRecetas()[i]->ataque.efecto,ata.GetAllocator());
    ata.AddMember("desbloqueado",libro->getRecetas()[i]->ataque.desbloqueado,ata.GetAllocator());
    p.AddMember("ataque",ata,p.GetAllocator());

    def.SetObject();
    def.AddMember("efecto",libro->getRecetas()[i]->defensa.efecto,def.GetAllocator());
    def.AddMember("desbloqueado",libro->getRecetas()[i]->defensa.desbloqueado,def.GetAllocator());
    p.AddMember("defensa",def,p.GetAllocator());

    mag.SetObject();
    mag.AddMember("efecto",libro->getRecetas()[i]->magia.efecto,mag.GetAllocator());
    mag.AddMember("desbloqueado",libro->getRecetas()[i]->magia.desbloqueado,mag.GetAllocator());
    p.AddMember("magia",mag,p.GetAllocator());
    
    med.SetObject();
    med.AddMember("efecto",libro->getRecetas()[i]->medicina.efecto,med.GetAllocator());
    med.AddMember("desbloqueado",libro->getRecetas()[i]->medicina.desbloqueado,med.GetAllocator());
    p.AddMember("medicina",med,p.GetAllocator());

    Value receta(rapidjson::kArrayType);
    for(unsigned int j=0;j<libro->getRecetas()[i]->receta.size();j++)
        receta.PushBack(libro->getRecetas()[i]->receta[j],d.GetAllocator());
    p.AddMember("receta",receta,p.GetAllocator());  

    p.AddMember("desbloqueado",libro->getRecetas()[i]->desbloqueado,p.GetAllocator());  

    poc.PushBack(p,allocator);
    
  }
  
  d.AddMember("potions",poc,d.GetAllocator());

  // Misiones
  vector<Mission*> misiones = GameStatus::Instance()->getMissions().getMissions();
  Value missions(rapidjson::kArrayType);
  
  Document m;
  for(int i=0;(unsigned)i<misiones.size();i++){
   
    m.SetObject();
    m.AddMember("typeTroll",misiones[i]->getTypeTroll(),m.GetAllocator());
    m.AddMember("numTroll",misiones[i]->getNumTroll(),m.GetAllocator());
    m.AddMember("troleados",misiones[i]->getTroleados(),m.GetAllocator());
    m.AddMember("reward",misiones[i]->getReward(),m.GetAllocator());
    missions.PushBack(m,allocator);
  }
  
  d.AddMember("misiones",missions,d.GetAllocator());

  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);
  d.Accept(writer);
  ofstream myfile ("partida.save");
  if (myfile.is_open()){
    myfile << buffer.GetString();
    myfile.close();
  }

}

void Status::cargar(){
  //Se leen los datos de un JSON con la partida guardada y se cargan
  Document d;
  Shop *shop = Shop::Instance();
  string line,datos;
  ifstream myfile ("partida.save"); //leemos fichero

  if(myfile.is_open()){
    while (getline (myfile,line) ){
        datos+= line;
  }
  myfile.close();

  char * punterodatos = new char[datos.length()+1]; 
  strcpy(punterodatos,datos.c_str());  //pasamos de string a char *
  d.Parse(punterodatos);       //crearmos el objeto JSON a partir del texto leido
  delete punterodatos;
  punterodatos = NULL;

  //DINERO
  const Value& a = d["money"];  //accedemos a money
  if(a.IsInt())    //comprobarmos su valor
      shop->setMoney(a.GetInt()); //lo obtenemos

  //PRESTIGIO
  const Value& b  = d["prestige"];
  if(b.IsInt())
      shop->setPrestigio(b.GetInt());

  //ESENCIAS
  const Value& c  = d["essences"];
  if(c.IsArray()){
    for(int i=0;i<4;i++)
      shop->setEssence(i,c.GetArray()[i].GetInt());
  }

  //DÍA
  const Value& di  = d["day"];
  if(di.IsInt())
    shop->setDay(di.GetInt());

  //HORA
  const Value& ho  = d["hour"];
  if(ho.IsInt())
    shop->setHour(ho.GetInt());

  //LIBRO DE RECETAS
  vector<Pocion*> potions = LibroStatus::Instance()->getRecetas();
  for(int i=0;i<20;i++){
    potions[i]->nombre = d["potions"][i]["nombre"].GetString(); 
    potions[i]->ataque.efecto = d["potions"][i]["ataque"]["efecto"].GetInt();
    potions[i]->defensa.efecto = d["potions"][i]["defensa"]["efecto"].GetInt();
    potions[i]->medicina.efecto = d["potions"][i]["medicina"]["efecto"].GetInt();
    potions[i]->magia.efecto = d["potions"][i]["magia"]["efecto"].GetInt();
    potions[i]->ataque.desbloqueado = d["potions"][i]["ataque"]["desbloqueado"].GetBool();
    potions[i]->defensa.desbloqueado = d["potions"][i]["defensa"]["desbloqueado"].GetBool();
    potions[i]->medicina.desbloqueado = d["potions"][i]["medicina"]["desbloqueado"].GetBool();
    potions[i]->magia.desbloqueado = d["potions"][i]["magia"]["desbloqueado"].GetBool();
    potions[i]->desbloqueado = d["potions"][i]["desbloqueado"].GetBool();

    for(int j=0;j<4;j++){
        potions[i]->receta[j] = d["potions"][i]["receta"][j].GetInt();
    }

  }

  //MISIONES
  GameStatus *game = GameStatus::Instance();
  game->setSprites();
  for(int i=0;(unsigned)i<d["misiones"].Size();i++){
    game->addMission(d["misiones"][i]["typeTroll"].GetInt(),d["misiones"][i]["numTroll"].GetInt(),d["misiones"][i]["reward"].GetInt(),d["misiones"][i]["troleados"].GetInt());

  }
  }else
  cout << "No hay ninguna partida guardada" << endl; 

}

//Borrar el json con la partida guardada
void Status::borrarPartida(){
  remove("partida.save");
}

void Status::deleteAlert(){
  if(alert!=NULL){
    delete alert;
    alert = NULL;
  }
}