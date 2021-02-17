#include "Sprite.h"

class Pot {
    public:
        Pot();
        ~Pot();
        void update(float);
        void render(float);
        void resetPosition();
        inline sf::FloatRect getGlobalBounds(){return collisioner;}
        inline void setSide(int num){side=num;}
        int getSide(){return side;}
    private:
        Sprite *sprite;
        int side;
        float x;
        float y;
        float newX;
        float newY;
        float lastX;
        float lastY;
        sf::FloatRect collisioner; //solo queremos que cuente como colision si le da al rectangulo de arriba de la olla
};