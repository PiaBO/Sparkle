#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "pocion.h"
#include "Status.h"
#include "Music.h"

#pragma once

using namespace std;
class LibroStatus : public Status{
   
    public:
        static LibroStatus* Instance();
        int comprobarPocion(vector<int>, int);
        vector<int> contarReceta(vector<int> receta);
        vector<Pocion*> getRecetas();
        void handle();
        void render(float);
        void update(float);
        inline bool getNew(){return nueva;}
        void setNew();

    protected:
        LibroStatus();
        LibroStatus(const LibroStatus &);
        LibroStatus &operator=(const LibroStatus &);
    
    private:
        static LibroStatus* status;
        vector<Pocion*> recetas; 
        Music* abrirLibro;
        Sprite *atrasSprite;
        Sprite *fondo;
        bool nueva;

};

