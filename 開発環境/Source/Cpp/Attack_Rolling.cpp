#include "../Header/Attack_Rolling.h"
#include "../Header/Calculation.h"
#include "../Header/Object_Base_Attack.h"
#include "../Header/Object_Base_Character.h"

/*
* @fn コンストラクタ
*/
Attack_Rolling::Attack_Rolling(Object_Base_Character *attackCharacter, int damage, int survivalGameTime, float attackSize, VECTOR *attackPosition)
: Object_Base_Attack(attackCharacter, damage, survivalGameTime)
, mpAttackPosition(attackPosition)
, mfAttackSize(attackSize)
{
}

/*
* @fn デストラクタ
*/
Attack_Rolling::~Attack_Rolling()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void Attack_Rolling::Initilize()
{
}

/*
* @fn MyUpdate
* @drief 更新
*/
void Attack_Rolling::MyUpdate()
{
}

/*
* @fn Draw
* @drief 描画
*/
void Attack_Rolling::Draw()
{
//    DrawSphere3D(VAdd(*mpAttackPosition, VGet(0.0f, mfAttackSize, 0.0f)), mfAttackSize, 32, GetColor(0, 255, 0), GetColor(0, 255, 0), TRUE);
}

/*
* @fn MyFinailize
* @drief 終了処理
*/
void Attack_Rolling::MyFinailize()
{
}

/*
* @fn AttackHitCheck
* @drief キャラクターに攻撃が当たって居るか判定する
*/
bool Attack_Rolling::AttackHitCheck(Object_Base_Character *character)
{
    return Calculation::Check_Circle_And_Pos(VAdd(*mpAttackPosition, VGet(0.0f, mfAttackSize, 0.0f)), mfAttackSize + character->GetStatus().size, character->GetObjectPosition());
}