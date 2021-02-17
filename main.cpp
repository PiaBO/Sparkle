#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "include/config.h"
#include "src/Shop.h"

const float kUpdateTimePS=1000/15;

int main() {

  Motor2D* motor = Motor2D::Instance();
  Shop *shop = Shop::Instance();
  
  shop->render();

  Clock clock;
  Clock updateClock;
  sf::Time timeElapsed;

  //Bucle del juego

  while (motor->getWindow()->isOpen()) {
    
    shop->handle();

    if(updateClock.getTimeAsMilli() > kUpdateTimePS){
      timeElapsed  = updateClock.restartTime();
      shop->update(timeElapsed.asSeconds());
    }

    float percenTick = fmin(1.0f, updateClock.getTimeAsMilli()/kUpdateTimePS);
    
    shop->render(percenTick);

    motor->drawWindow();
  }

  return 0;
}