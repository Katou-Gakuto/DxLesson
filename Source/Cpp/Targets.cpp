#include "../Header/Object_Base_Character.h"
#include "../Header/Targets.h"

/*
* @fn コンストラクタ
*/
Targets::Targets()
: mpTargetPlayer(nullptr)
{
    mpTargetEnemy.clear();
}

/*
* @fn デストラクタ
*/
Targets::~Targets()
{
}

/*
* @fn GetPlayerPosition
* @drief プレイヤー座標取得
*/
VECTOR Targets::GetPlayerPosition()
{
    return mpTargetPlayer->GetObjectPosition();
}

/*
* @fn SetPlayer
* @drief プレイヤーオブジェクト設定
*/
void Targets::SetPlayer(Object_Base_Character *player)
{
    mpTargetPlayer = player;
}

/*
* @fn AddTargetEnemy
* @drief エネミー追加
*/
void Targets::AddTargetEnemy(Object_Base_Character *enemy)
{
    mpTargetEnemy.push_back(enemy);
}