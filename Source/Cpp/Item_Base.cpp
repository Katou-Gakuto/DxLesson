#include "../Header/GameManager.h"
#include "../Header/GraphManager.h"
#include "../Header/Data_Structs.h"
#include "../Header/Item_Base.h"

/*
* @fn コンストラクタ
*/
Item_Base::Item_Base(ITEM_DATA item)
: mnItemNumber(item.possessionCount)
, mstrDisplayName(item.templateData.name)
{
    mnItemHandle = Master::mpGameManager->GerGraphManager()->GetGraphNumber(item.itemPhotoFileName.c_str(), true);

    mnItemType = -1;
    if (item.templateData.typeName == "RecoveryMedicine(Small)") {
        mnItemType = 0;
    }
    if (item.templateData.typeName == "RecoveryMedicine(Medium)") {
        mnItemType = 0;
    }
    if (item.templateData.typeName == "RecoveryMedicine(Large)") {
        mnItemType = 0;
    }
}

/*
* @fn デストラクタ
*/
Item_Base::~Item_Base()
{
}

/*
* @fn Draw
* @drief アイテム画像描画
*/
void Item_Base::Draw(int x, int y, int sizeX, int sizeY)
{
    DrawExtendGraph(x, y, x + sizeX, y + sizeY, mnItemHandle, TRUE);
}