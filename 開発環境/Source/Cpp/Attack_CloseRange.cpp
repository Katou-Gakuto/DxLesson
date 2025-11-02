#include "DxLib.h"
#include "../Header/Calculation.h"
#include "../Header/Attack_CloseRange.h"
#include "../Header/Object_Base_Attack.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/Status_Struct.h"

/*
* @fn コンストラクタ
*/
Attack_CloseRange::Attack_CloseRange(Object_Base_Character *attackCharacter, int damage, int survivalGameTime, VECTOR attackPosition, float attackSize)
: Object_Base_Attack(attackCharacter, damage, survivalGameTime)
, mvAttackPosition(attackPosition)
, mfAttackSize(attackSize)
{
}

/*
* @fn デストラクタ
*/
Attack_CloseRange::~Attack_CloseRange()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void Attack_CloseRange::Initilize()
{
}

/*
* @fn MyUpdate
* @drief 更新
*/
void Attack_CloseRange::MyUpdate()
{
}

/*
* @fn Draw
* @drief 描画
*/
void Attack_CloseRange::Draw()
{
 //   DrawSphere3D(mvAttackPosition, mfAttackSize, 32, GetColor(0, 255, 0), GetColor(0, 255, 0), TRUE);
}

/*
* @fn MyFinailize
* @dreif 終了処理
*/
void Attack_CloseRange::MyFinailize()
{
}

/*
* @fn AttackHitCheck
* @drief キャラクターに攻撃が当たって居るか判定する
*/
bool Attack_CloseRange::AttackHitCheck(Object_Base_Character *character)
{
    return Calculation::Check_Circle_And_Pos(mvAttackPosition, mfAttackSize + character->GetStatus().size, character->GetObjectPosition());
}