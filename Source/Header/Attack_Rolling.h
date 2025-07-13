#pragma once
#include "../Header/Object_Base_Attack.h"
#include "../Header/Object_Base_Character.h"

class Attack_Rolling : public Object_Base_Attack
{
private:
    VECTOR *mpAttackPosition;   // 攻撃場所
    float mfAttackSize; // 攻撃サイズ

public:
    Attack_Rolling(Object_Base_Character *attackCharacter, int damage, int survivalGameTime, float attackSize, VECTOR *attackPosition); // コンストラクタ
    ~Attack_Rolling(); //デストラクタ

    void Initilize() override;      // 初期化
    void MyUpdate() override;       // 更新
    void Draw() override;           // 描画
    void MyFinailize() override;    // 終了処理


    bool AttackHitCheck(Object_Base_Character *character) override;  // キャラクターに攻撃が当たって居るか判定する
};