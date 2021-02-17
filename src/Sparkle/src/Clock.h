#include <SFML/Graphics.hpp>
using namespace std;
#pragma once

class Clock{
    public:
        sf::Clock clock;
        Clock();
        ~Clock();
        void startTime();
        sf::Time restartTime();
        float getTimeAsSecond();
        int getTimeAsMilli();
        int getTimeAsMicro();
};