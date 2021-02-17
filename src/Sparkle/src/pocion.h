#include <vector>
#include <string>

#pragma once

using namespace std;
class Pocion{
    struct strPocion{
        int efecto;
        bool desbloqueado;
        void desbloquear(){
            desbloqueado = true;
        }
    };  
    
    public:             
        string nombre;
        strPocion ataque;
        strPocion defensa;
        strPocion magia;
        strPocion medicina;
        bool desbloqueado;
        vector<int> receta;
        Pocion(string, int, int, int, int,vector<int>);
        ~Pocion();
        void desbloquear();
        string recetaToString();
        string efectoToString(int);

};
