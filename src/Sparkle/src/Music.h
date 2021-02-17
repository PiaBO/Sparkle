
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
#pragma once
class Music{
    public:
        Music(string str,bool bo,int vol);
        ~Music();
        Music &operator= (const Music &);
        void Play();
    private:
        sf::Music muse;


};