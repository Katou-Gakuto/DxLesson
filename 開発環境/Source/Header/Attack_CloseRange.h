#pragma once
#include "DxLib.h"
#include "../Header/Object_Base_Attack.h"

class Attack_CloseRange : public Object_Base_Attack
{
private:
    VECTOR mvAttackPosition;    // 攻撃場所
    float mfAttackSize; // 攻撃サイズ

public:
    Attack_CloseRange(Object_Base_Character *attackCharacter, int damage, int survivalGameTime, VECTOR attackPosition, float attackSize); // コンストラクタ
    ~Attack_CloseRange(); //デストラクタ

    void Initilize() override;      // 初期化
    void MyUpdate() override;       // 更新
    void Draw() override;           // 描画
    void MyFinailize() override;    // 終了処理


    bool AttackHitCheck(Object_Base_Character *character) override;  // キャラクターに攻撃が当たって居るか判定する
};