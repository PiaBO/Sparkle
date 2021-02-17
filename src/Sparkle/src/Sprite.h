#include "TextureManager.h"
#include "motor2D.h"

using namespace std;

#pragma once

class Sprite{
    public:
        Sprite(string file, vector<int> column, vector<int> fila, int x, int y, int tile_size_x, int tile_size_y);
        Sprite(string file, int column, int fila, int x, int y, int tile_size_x, int tile_size_y);
        ~Sprite();
        void draw();
        void setTexture(string file);
        void setTextureRect(int numX, int numY, int tamX, int tamY);
        void setTextureRect(sf::IntRect rec);
        void setOriginCero();
        void setPosition(int x,int y);
        void moveSprites(int x,int y);
        void setScale(float x,float y);
        void fade();
        void disapear();
        void cycle();
        int speak();
        inline void setActualSprite(int num){actualSprite = num;}
        inline sf::Sprite getSprite(){return sprites[actualSprite];}
        inline int getActualSprite(){return actualSprite;}
        inline sf::Sprite getSprite(int n){
            if((unsigned)n<sprites.size())
                return sprites[n];
            else
                return sprites[0];
        }
        
    private:
        vector<sf::Sprite> sprites;
        int actualSprite;
        sf::Texture* textura;
        int up;
};