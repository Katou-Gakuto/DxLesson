#include "../Header/DataManager.h"
#include "../Header/Data_Structs.h"
#include "../Header/GameManager.h"
#include "../Header/ItemRecoveryMedicine.h"
#include "../Header/Item_Base.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/SoundManager.h"

/*
* @fn コンストラクタ
*/
ItemRecoveryMedicine::ItemRecoveryMedicine(ITEM_DATA item, int recoveryAmount)
: Item_Base(item)
, mnRecoveryAmount(recoveryAmount)
{
}

/*
* @fn デストラクタ
*/
ItemRecoveryMedicine::~ItemRecoveryMedicine()
{
}

/*
* @fn ItemEffect
* @drief アイテム効果
*/
void ItemRecoveryMedicine::ItemEffect(Object_Base_Character *character)
{
    if (character->GetStatus().maxHp != character->GetStatus().hp) {
        // HP回復
        character->Recovery(mnRecoveryAmount);
        Master::mpGameManager->GetSoundManager()->SetSound(SOUND::RECOVERY);

        mnItemNumber -= 1;
        if (mnItemNumber <= 0) {
            Master::mpGameManager->GetDataManager()->SetDeleteItem(mstrDisplayName);
        }
    }
}