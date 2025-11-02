#include "Dxlib.h"
#include "../Header/Object_Base.h"
#include "../Header/ObjectManager.h"
#include "../Header/SceneManager.h"
#include "../Header/GameManager.h"


Object_Base::Object_Base() : mpNextObject(nullptr), mpPrevObject(nullptr), mbIsDeleteFlag(false), mnTag(0)
{
    meObjectScene = Master::mpGameManager->GetSceneManager()->GetNowScene();

    Master::mpGameManager->GetObjectManager()->Add(this);
}

Object_Base::~Object_Base()
{

}




/*
* @fn DeleteSetTag
* @drief オブジェクトの削除フラグを有効化(numberで指定)
*/
void Object_Base::DeleteSetTag(int number, bool flag)
{
    std::vector<Object_Base*> result = Master::mpGameManager->GetObjectManager()->FindsByTag(number);
    if (!result.empty())
    {
        for (int i = 0; i < result.size(); i++) {
            result[i]->SetDeleteFlag(flag);
        }
    }
}

/*
* @fn ObjectHitTag
* @drief オブジェクトに当たっているか
*/
bool Object_Base::ObjectHitTag(VECTOR* position, VECTOR moveVec, VECTOR old_Position, float radius, bool flag, VECTOR size)
{
    if (flag == true)
    {
        return true;
    }

    return flag;
}

/*
* @fn ObjectHitsTag
* @drief オブジェクトに当たっているか(複数当たっている場合使う)
*/
bool Object_Base::ObjectHitsTag(VECTOR *position, VECTOR moveVec, VECTOR old_Position, float radius, bool flag, VECTOR size)
{
    if (flag == true)
    {
        return true;
    }

    return flag;
}
