#include "Music.h"

//La musica recibe lso 3 parametros básicos que necesitamos para crear música en SFML
Music::Music(string file,bool bo, int vol){
    //El archivo de donde saca la musica
    muse.openFromFile(file);
    //El volumen que tiene que poner la música
    muse.setVolume(vol);
    //Habilitar la opción de bucle de SFML que tiene implementasda de forma automatica
    muse.setLoop(bo);
}

Music::~Music() {

}

void Music::Play(){
//PAra que la musica suene hay que darle play
    muse.play();

}