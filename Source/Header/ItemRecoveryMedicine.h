#pragma once
#include "../Header/Data_Structs.h"
#include "../Header/Item_Base.h"
#include "../Header/Object_Base_Character.h"

class ItemRecoveryMedicine : public Item_Base
{
private:
    int mnRecoveryAmount;   // ‰ñ•œ—Ê

public:
    ItemRecoveryMedicine(ITEM_DATA item, int recoveryAmount);
    ~ItemRecoveryMedicine();

    void ItemEffect(Object_Base_Character *character) override; // ƒAƒCƒeƒ€Œø‰Ê
};