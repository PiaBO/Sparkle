#include "pocion.h"

#include <iostream>

//Constructor
Pocion::Pocion(string pNombre, int pAtaque, int pDefensa, int pMagia, int pMedicina, vector<int> pReceta) { 

    nombre = pNombre;
    ataque.efecto = pAtaque;
    ataque.desbloqueado = false;
    defensa.efecto = pDefensa;
    defensa.desbloqueado = false;
    magia.efecto = pMagia;
    magia.desbloqueado = false;
    medicina.efecto = pMedicina;
    medicina.desbloqueado = false;

    receta = pReceta;
    desbloqueado = false;
}
Pocion::~Pocion(){}

void Pocion::desbloquear(){
        desbloqueado = true;
}

//Método para obtener la receta escrita, se usa en el render de libro
string Pocion::recetaToString(){
    string cad;

    if(receta[0]>0){
        cad += "Agua: "+to_string(receta[0])+" ";
    }
    if(receta[1]>0){
        cad += "Fuego: "+to_string(receta[1])+" ";
    }
    if(receta[2]>0){
        cad += "Aire: "+to_string(receta[2])+" ";
    }
    if(receta[3]>0){
        cad += "Tierra: "+to_string(receta[3])+" ";
    }

return cad;
}

//Método para obtener el efecto de la poción
string Pocion::efectoToString(int n){
    string cad;

        switch(n){
            case 0: cad +="Mal";
                break;
            case 1: cad +="Mediocre";
                break;   
            case 2: cad +="Bueno";
                break;       
            case 3: cad +="Excelente";
                break;    
            default:break;                                  
        }
    return cad;
}