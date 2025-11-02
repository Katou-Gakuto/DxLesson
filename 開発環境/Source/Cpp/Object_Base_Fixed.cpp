#include "DxLib.h"
#include "../Header/GameManager.h"
#include "../Header/Object_Base.h"
#include "../Header/Object_Base_Fixed.h"
#include "../Header/ObjectManager.h"

/*
* @fn コンストラクタ
*/
Object_Base_Fixed::Object_Base_Fixed(unsigned int mapColor)
: Object_Base()
, mpPrevFixedObject(nullptr)
, mpNextFixedObject(nullptr)
, mnMapColor(mapColor)
{
    Master::mpGameManager->GetObjectManager()->AddFixed(this);
}

/*
* @fn デストラクタ
*/
Object_Base_Fixed::~Object_Base_Fixed()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void Object_Base_Fixed::Initilize()
{
}

/*
* @fn Update
* @drief 更新
*/
void Object_Base_Fixed::Update()
{
}

/*
* @fn Draw
* @drief 描画
*/
void Object_Base_Fixed::Draw()
{
}

/*
* @fn Finalize
* @drief 固定オブジェクト共通終了処理
*/
void Object_Base_Fixed::Finalize()
{
    Master::mpGameManager->GetObjectManager()->FixedDelete(this);

    MyFinalize();
}

/*
* @fn CheckHit_ReturnAmountMoved
* @drief 当たり判定
*/
VECTOR Object_Base_Fixed::CheckHit_ReturnAmountMoved(VECTOR checkPosition, VECTOR nowPosition, VECTOR moveVec, float size)
{
    return VGet(0.0f, 0.0f, 0.0f);
}

/*
* @fn SetPlusMinusPosition
* @drief マインスとプラスポジションを設定する
*/
void Object_Base_Fixed::SetPlusMinusPosition(VECTOR plusPosition, VECTOR minusPosition)
{

    mvMinusPosition = VGet(0.0f, 0.0f, 0.0f);
    mvPlusPosition = VGet(0.0f, 0.0f, 0.0f);

    if (plusPosition.x > minusPosition.x) {
        mvPlusPosition.x = plusPosition.x;
        mvMinusPosition.x = minusPosition.x;
    }
    else {
        mvPlusPosition.x = minusPosition.x;
        mvMinusPosition.x = plusPosition.x;
    }

    if (plusPosition.y > minusPosition.y) {
        mvPlusPosition.y = plusPosition.y;
        mvMinusPosition.y = minusPosition.y;
    }
    else {
        mvPlusPosition.y = minusPosition.y;
        mvMinusPosition.y = plusPosition.y;
    }

    if (plusPosition.z > minusPosition.z) {
        mvPlusPosition.z = plusPosition.z;
        mvMinusPosition.z = minusPosition.z;
    }
    else {
        mvPlusPosition.z = minusPosition.z;
        mvMinusPosition.z = plusPosition.z;
    }
}