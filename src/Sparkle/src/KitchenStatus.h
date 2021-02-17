#pragma once

#include "Status.h"
#include "AguaQteStatus.h"
#include "FuegoQteStatus.h"
#include "AireQteStatus.h"
#include "TierraQteStatus.h"

class KitchenStatus : public Status{

    public:
        static KitchenStatus* Instance();
        void handle();
        void update(float);
        void render(float);
        int setSprites();

    protected:
        KitchenStatus();
        KitchenStatus(const KitchenStatus &);
        KitchenStatus &operator= (const KitchenStatus &);
        
    private:
        static KitchenStatus* status;
        Sprite *back;
        Sprite *table;     
};