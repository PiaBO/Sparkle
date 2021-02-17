#include "libroStatus.h"
#include "Shop.h"

LibroStatus* LibroStatus::status = 0;

//crear el singleton
LibroStatus* LibroStatus::Instance(){
    if(status == 0){
        status = new LibroStatus();
    }
    return status;
}

//se crea la instancia
LibroStatus::LibroStatus():Status(){
    if(!status) status = this;
    // Vector con todas las combinaciones de las esencias básicas
    // 1: Agua | 2: Fuego | 3: Aire | 4: Tierra  
    vector<vector<int> > recetasBase{{3,0,0,0},{2,1,0,0},{2,0,1,0},{2,0,0,1},{1,2,0,0},{1,1,1,0},{1,1,0,1},{1,0,2,0},{1,0,1,1},{1,0,0,2},{0,3,0,0},{0,2,1,0},{0,2,0,1},{0,1,2,0},{0,1,1,1},{0,1,0,2},{0,0,3,0},{0,0,2,1},{0,0,1,2},{0,0,0,3}}; 

    // Vector que contendrá las recetas para esta partida
    // Inicializado a 0
    vector<vector<int> > recetas(20,vector<int>(4,0));
    srand(time(0));

    //boton para poder salir del libro
    atrasSprite = new Sprite("resources/flecha.png",0,0,30,30,400,270);
    atrasSprite->setScale(0.15,0.18);

    //fondo del libro
    fondo = new Sprite("resources/fondolibro.png", 0, 0, 640, 360, 1280, 720);

    // Primero desordenamos las recetas de manera aleatoria
    for (unsigned f = 0; f < recetasBase.size(); f++)
    {
        int posAleatoria = rand()%20;
            
        if(recetas[posAleatoria][0] == 0 && recetas[posAleatoria][1] == 0 && recetas[posAleatoria][2] == 0 && recetas[posAleatoria][3] == 0){ 
            //Está vacío
            recetas[posAleatoria] = recetasBase[f];
        }else{
            //Se vuelve a calcular las posición
            f--;
        }
    }

   //Intanciamos las pociones con las recetas aleatorias

    string line,datos;
    ifstream myfile ("src/potionsData.json");
    if (myfile.is_open()){
        while ( getline (myfile,line) ){
             datos+= line;
        }   
   
        myfile.close();

        char * aux = new char[datos.length()+1];
        strcpy(aux,datos.c_str());

        prestige.Parse(aux);

        int j = 0;

        for (SizeType i = 0; i < prestige.Size(); i++) {
            string nombre = prestige[i]["Nombre"].GetString();
            int ataque = prestige[i]["Attack"].GetInt();
            int defensa = prestige[i]["Defense"].GetInt();
            int magia = prestige[i]["Magic"].GetInt();
            int medicina = prestige[i]["Medicine"].GetInt();

            this->recetas.push_back(new Pocion(nombre,ataque,defensa,magia,medicina,recetas[j])); 
            
            j++;
        }

        delete aux;
        aux = NULL;

        abrirLibro=new Music("resources/Musica/libro.wav",false,30);

    }else{
        cout << "Unable to open file" << endl;
    }

    //pocion nueva al principio es false
    nueva = false;
    
}

int LibroStatus::comprobarPocion(vector<int> pReceta, int pTipo){
    int result = -1;
    //Recorremos las recetas buscando cual se ha creado
    for(unsigned i; i < recetas.size() && result == -1; i++){
        Pocion *p = recetas[i];
        vector<int> rec = contarReceta(pReceta);
        //Encontramos la poción que ha creado
        if(rec[0] == p->receta[0] && rec[1] == p->receta[1] && rec[2] == p->receta[2] && rec[3] == p->receta[3]){
            //Si esta bloqueada (nunca la habia hecho) se desbloquea
            if(!p->desbloqueado){
                p->desbloquear();
                //hasta que entre en el libro le saldrá que hay una poti nueva
                nueva = true;
                //Mostramos un mensaje al usuario
                string alert = "Poción desbloqueada: \n" + p->nombre;
                GameStatus::Instance()->createAlert(alert);
            }
            //Buscamos la efectividad
            switch(pTipo){
                case 1: result = p->ataque.efecto;
                        if(!p->ataque.desbloqueado)
                         p->ataque.desbloquear();
                        
                    break;
                case 2: result = p->defensa.efecto;
                        if(!p->defensa.desbloqueado) 
                         p->defensa.desbloquear();                
                    break;
                case 3: result = p->magia.efecto;
                        if(!p->magia.desbloqueado) 
                         p->magia.desbloquear();                
                    break;
                case 4: result = p->medicina.efecto;
                        if(!p->medicina.desbloqueado) 
                         p->medicina.desbloquear();                
                    break;
                    default:break;
            }
        }
    }
    return result;

}

//pintamos el texto del libro, calculando la poscion de cada uno
void LibroStatus::render(float percenTick){

    Text textoNombre,textoReceta, textoAtaque, textoDefensa, textoMagia, textoMedicina;
    vector<Text> textos{textoNombre,textoReceta, textoAtaque, textoDefensa, textoMagia, textoMedicina};
    vector<string> cadenas{"Nombre","Receta","Ataque","Defensa","Magia","Medicina"};
    vector<string> esencias{"Agua","Fuego","Aire","Tierra"};
    vector<string> efectividad{"Malo","Mediocre","Bueno","Excelente"};
    // vector<vector<int>>posTexto{{27,10},{354,10},{680,10},{813,10},{960,10},{1110,10}}; antiguas posiciones
    vector<vector<int>>posTexto{{67,10},{394,10},{720,10},{843,10},{1000,10},{1150,10}};
    
    //sprite fondo
    fondo->draw();

    int cont = 0;
    for(Text texto : textos){
        texto.setColorBlack();
        texto.setSize(24);
        texto.setUnderline();
        texto.setPosition(posTexto[cont][0],posTexto[cont][1]);
        texto.setString(cadenas[cont]);
        cont++;
        texto.draw();
    }

    Text textoPocion;
    textoPocion.setColorBlack();
    int fila = 48;
    for(Pocion *p : recetas){
        //Si está desbloqueada se muestra toda la información
        if(p->desbloqueado){
            //Nombre
            textoPocion.setString(p->nombre);
            textoPocion.setPosition(posTexto[0][0],fila);
            textoPocion.draw();

            //Receta
            textoPocion.setString(p->recetaToString());
            textoPocion.setPosition(posTexto[1][0],fila);
            textoPocion.draw();

            //Ataque
            if(p->ataque.desbloqueado){
                textoPocion.setString(p->efectoToString(p->ataque.efecto));
            }else{
                textoPocion.setString("???");        
            }

            textoPocion.setPosition(posTexto[2][0],fila);
            textoPocion.draw();

            //Defensa
            if(p->defensa.desbloqueado){
                textoPocion.setString(p->efectoToString(p->defensa.efecto));
            }else{
                textoPocion.setString("???");        
            }

            textoPocion.setPosition(posTexto[3][0],fila);
            textoPocion.draw();

            //Magia
            if(p->magia.desbloqueado){
                textoPocion.setString(p->efectoToString(p->magia.efecto));
            }else{
                textoPocion.setString("???");        
            }

            textoPocion.setPosition(posTexto[4][0],fila);
            textoPocion.draw();

            //Medicina
            if(p->medicina.desbloqueado){
                textoPocion.setString(p->efectoToString(p->medicina.efecto));       
            }else{
                textoPocion.setString("???");        
            }

            textoPocion.setPosition(posTexto[5][0],fila);
            textoPocion.draw();

        }else{
            //Si no está desbloqueada saldŕan interrogantes
            //Nombre
            textoPocion.setString("???");
            textoPocion.setPosition(posTexto[0][0],fila);
            textoPocion.draw();

            //Receta
            textoPocion.setPosition(posTexto[1][0],fila);
            textoPocion.draw();

            //Ataque
            textoPocion.setPosition(posTexto[2][0],fila);
            textoPocion.draw();

            //Defensa
            textoPocion.setPosition(posTexto[3][0],fila);
            textoPocion.draw();

            //Magia
            textoPocion.setPosition(posTexto[4][0],fila);
            textoPocion.draw();

            //Medicina
            textoPocion.setPosition(posTexto[5][0],fila);
            textoPocion.draw();      
        }
        fila += 32;
    }

    atrasSprite->draw(); 
       
}

//para calcular cuantas gotas de cada tipo hay en la receta
vector<int> LibroStatus::contarReceta(vector<int> pReceta){
    int cont1, cont2, cont3, cont4;
    cont1 = cont2 = cont3 = cont4 = 0;
    for(int n : pReceta){
        switch(n){
            case 1: cont1++;
                break;
            case 2: cont2++;
                break;
            case 3: cont3++;
                break;
            case 4: cont4++;
                break;
                default:break;
        }
    }

    vector<int> vec = {cont1,cont2,cont3,cont4};

    return vec;
}

//para controlar los eventos
void LibroStatus::handle(){

    Shop *shop = Shop::Instance();
    sf::Event event;
    Motor2D *motor = Motor2D::Instance();
    while (motor->getWindow()->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                motor->getWindow()->close();
            break;
            case sf::Event::TextEntered:
                //no se usa keyReleased porque no pilla mayusculas
                if(event.text.unicode==76||event.text.unicode==108){ //LETRA L: salir del libro
                    abrirLibro->Play();
                    shop->setStatus(GameStatus::Instance());
                }
            break;
            case sf::Event::MouseButtonReleased:
            
                if(event.mouseButton.button == sf::Mouse::Left){
                    //para salir de libro con el boton de atras

                    sf::Vector2i posRaton = sf::Mouse::getPosition((*motor->getWindow()));
                    if(atrasSprite->getSprite().getGlobalBounds().contains(posRaton.x, posRaton.y)){
                        abrirLibro->Play();     
                        shop->setStatus(GameStatus::Instance());
                    }
                }
            break;
            case sf::Event::KeyReleased: 
                switch (event.key.code) {
                    case sf::Keyboard::Escape: // salir del libro

                        abrirLibro->Play();
                        shop->setStatus(GameStatus::Instance());
                    break;
                }
            break;

            default:break;
        }
    }
}

//se sigue llamando al update del gameStatus para que los npc se sigan actualizando
void LibroStatus::update(float time){
    GameStatus::Instance()->update(time);
}

//para obtener la receta
vector<Pocion*> LibroStatus::getRecetas(){
    return recetas;
}


void LibroStatus::setNew(){
    if(nueva)
        nueva = false;
}