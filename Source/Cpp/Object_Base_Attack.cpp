#include <vector>
#include "../Header/GameManager.h"
#include "../Header/ObjectManager.h"
#include "../Header/ObjectTagMacro.h"
#include "../Header/Object_Base.h"
#include "../Header/Object_Base_Attack.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
Object_Base_Attack::Object_Base_Attack(Object_Base_Character *attackCharacter, int damage, int survivalGameTime)
: Object_Base()
, mpPrevAttackObject(nullptr)
, mpNextAttackObject(nullptr)
, mpAttackCharacter(attackCharacter)
, mbAttackDeleteFlag(false)
, mnDamage(damage)
{
    Master::mpGameManager->GetObjectManager()->AddAttack(this);

    mnSurvivalGameTime = survivalGameTime + Master::mpGameManager->GetTimeManager()->GetGameTime();
    
    mpHitCharacter.clear();
    
    SetTag(ATTACK_TAG);
}

/*
* @fn デストラクタ
*/
Object_Base_Attack::~Object_Base_Attack()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void Object_Base_Attack::Initilize()
{
}

/*
* @fn Update
* @drief 更新
*/
void Object_Base_Attack::Update()
{
    // 時間停止フラグが有効なら更新しない
    if (Master::mpGameManager->GetTimeManager()->GetStopFlag()) {
        return;
    }

    MyUpdate();

    if (mnSurvivalGameTime <= Master::mpGameManager->GetTimeManager()->GetGameTime()) {
        mbAttackDeleteFlag = true;
    }

    if (mbAttackDeleteFlag) {
        SetDeleteFlag(true);
    }
}

/*
* @fn Draw
* @drief 描画
*/
void Object_Base_Attack::Draw()
{
}

/*
* @fn Finalize
* @drief 終了処理
*/
void Object_Base_Attack::Finalize() 
{
    Master::mpGameManager->GetObjectManager()->AttackDelete(this);

    mpHitCharacter.clear();
    MyFinailize();
}

/*
* @fn CheckCharacter
* @drief キャラクターに攻撃が当たっていればダメージ処理をして記録する
*/
bool Object_Base_Attack::CheckCharacter(Object_Base_Character *character)
{
    if (character == mpAttackCharacter) {
        return false;
    }

    for (int i = 0; i < mpHitCharacter.size(); i++) {
        if (character == mpHitCharacter[i]) {
            return false;
        }
    }
    if (AttackHitCheck(character)) {
        if (mpAttackCharacter->GetStatus().level >= (character->GetStatus().level + 100)) {
            character->Damage(mnDamage, true);
        }
        else {
            character->Damage(mnDamage);
        }
        mpHitCharacter.push_back(character);
        return true;
    }

    return false;
}