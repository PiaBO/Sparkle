#include "Sprite.h"
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/stringbuffer.h"
#include "Alert.h"
#include <fstream>


using namespace std;
using namespace rapidjson;

#pragma once

class Status{
    protected:
        Document prestige;
        static Alert* alert;
    public:
        Status();
        virtual void handle() = 0;
        virtual void update(float) = 0;
        virtual void render(float) = 0;
        void guardar();
        void cargar();
        void borrarPartida();
        void deleteAlert();
};