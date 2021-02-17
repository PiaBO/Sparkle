#include "Pot.h"

//Constructor
Pot::Pot(){
    x = 640;
    y = 500;
    newX = 640;
    newY = 500;
    lastX = 640;
    lastY = 500;
    side = 0;

    //animaciones
    vector<int> columns;
    vector<int> rows;
    rows.push_back(0);
    rows.push_back(0);
    rows.push_back(0);
    rows.push_back(0);
    rows.push_back(0);
    columns.push_back(0);
    columns.push_back(1);
    columns.push_back(2);
    columns.push_back(3);
    columns.push_back(4);

    sprite = new Sprite("resources/calderoLila.png", columns, rows, x, y, 315, 270);

    //Bounding box para controlar las colisiones
    collisioner.left=557.5; //640-315/2+75
    collisioner.top=395; //500-270/2+30
    collisioner.height=15;
    collisioner.width=180;
}

Pot::~Pot(){
    delete sprite;
    sprite = NULL;
}

//Update con interpolación
void Pot::update(float time){
    
    float velocidad = 500;
    lastX = newX;
    //std::cout << side << endl;
    if(side!= 0){
        newX += velocidad*time*side;

        if(newX>1150){
            newX=1150;
        }else 
            if(newX<130){
                newX=130;
            }
    }

    sprite->fade();
}

void Pot::render(float percenTick){
    x = lastX*(1-percenTick) + newX*percenTick;

    //actualizamos collisioner para que la posicion sea la de la olla
    collisioner.left = x-90; //-90 para que este centrado

    sprite->setPosition(x, 500);
    sprite->draw();
}
//Resetear todos los atributos al terminar el minijuego
void Pot::resetPosition(){
    x = 640;
    y = 500;
    newX = 640;
    newY = 500;
    lastX = 640;
    lastY = 500;
    side = 0;
}
