#include "Sprite.h"

//Contructor para una spritesheet
Sprite::Sprite(string file, vector<int> column, vector<int> fila, int x, int y, int tile_size_x, int tile_size_y){

    TextureManager *texturaM = TextureManager::Instance();

    textura = texturaM->Load(file);

//Para cada sprite
    for(unsigned int i=0; i<fila.size(); i++){

        sf::Sprite nuevo;
        //Y creo el spritesheet a partir de la imagen anterior
        nuevo.setTexture(*textura);

        //Le pongo el centroide en el centro
        nuevo.setOrigin(tile_size_x / 2, tile_size_y / 2);
        //Cojo el sprite que me interesa por defecto del sheet

       nuevo.setTextureRect(sf::IntRect(column[i] * tile_size_x, fila[i] * tile_size_y, tile_size_x, tile_size_y));

        sprites.push_back(nuevo); // metemos el nuevo sprite
    }

    actualSprite=0;
     
    setPosition(x,y);

    //para el fade (animación esencias)
    up=1;

}

//constructor para un único sprite
Sprite::Sprite(string file, int column, int fila, int x, int y, int tile_size_x, int tile_size_y){

    TextureManager *texturaM = TextureManager::Instance();

    textura = texturaM->Load(file);

    sf::Sprite nuevo;
    //Y creo el spritesheet a partir de la imagen anterior
    nuevo.setTexture(*textura);

    //Le pongo el centroide en el centro
    nuevo.setOrigin(tile_size_x / 2, tile_size_y / 2);

    nuevo.setTextureRect(sf::IntRect(column * tile_size_x, fila * tile_size_y, tile_size_x, tile_size_y));

    sprites.push_back(nuevo); // metemos el nuevo sprite
    
    actualSprite = 0;

    setPosition(x,y);

    //Para el fade (animación esencias)
    up=1;

}


Sprite::~Sprite(){
    delete textura;
    textura = NULL;
}

//Método para pintar el sprite actual
void Sprite::draw(){
    Motor2D* motor2D= Motor2D::Instance();
    motor2D->drawSprites(sprites[actualSprite]);
}
//Método façade de sfml
void Sprite::setTexture(string file){
    TextureManager *texturaM = TextureManager::Instance();

    textura = texturaM->Load(file);

    sprites[0].setTexture(*textura);

}
//Método façade de sfml
void Sprite::setTextureRect(int numX, int numY, int tamX, int tamY){
    sprites[0].setTextureRect(sf::IntRect(numX*tamX, numY*tamY, tamX, tamY));
}
//Método façade de sfml
void Sprite::setTextureRect(sf::IntRect rec){
    sprites[0].setTextureRect(rec);
}
//Colocar el centroide en el 0,0
void Sprite::setOriginCero(){
    for(unsigned int i = 0;i<sprites.size();i++){
        sprites[i].setOrigin(0,0);
    }
}
//Método façade de sfml
void Sprite::setPosition(int x,int y){
    for(unsigned int i = 0;i<sprites.size();i++)
        sprites[i].setPosition(x,y);

}
//Método façade de sfml
void Sprite::moveSprites(int x,int y){
    for(unsigned int i = 0;i<sprites.size();i++)
        sprites[i].move(x,y);
}

//Método façade de sfml
void Sprite::setScale(float x,float y){
    for(unsigned int i = 0;i<sprites.size();i++)
        sprites[i].setScale(x,y);
}
//Animación de hablar para los npc
int Sprite::speak(){
    int estado = 2;

    switch(actualSprite){
        case 3: actualSprite = 4;
        break;
        case 4:  actualSprite = 3;
        break;
        default:
            actualSprite = 3;
        break;
    }

    return estado;
}
//Animación de las esencias
void Sprite::fade(){

    if((unsigned)actualSprite == sprites.size()-1){
        up=-1;
    }

    if(actualSprite == 0){
        up=1;
    }
    actualSprite += up;
}
//Animación fade out
void Sprite::disapear(){
    actualSprite++;
    if((unsigned)actualSprite > sprites.size()-1)
        actualSprite = sprites.size()-1;
    
}
// Para la animación de las pociones y del gato
// Que vaya pasando todos los sprites y cuando llegue al penultimo vuelva al primero, 
// en el caso de estar en el ultimo poque no quedaban vuelve a iniciar en 0 tambien
void Sprite::cycle(){
    actualSprite++;

    if((unsigned) actualSprite >= sprites.size()-2){
        actualSprite = 0;
    }
}