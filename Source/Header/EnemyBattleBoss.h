#pragma once
#include <iostream>
#include <string>

#include "DxLib.h"
#include "../Header/CharacterType_Enum.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/Status_Struct.h"

class EnemyBattleBoss : public Object_Base_Character
{
private:
    Object_Base_Character *mpPlayer;    // プレイヤー

    CHARACTER_TYPE meEnemyType; // エネミータイプ

    VECTOR mvSetActionVec;  // アクション時使用する方向ベクトル

    int mnActionType;   // アクションタイプ
    int mnNextActionTime;   // 次のアクションまでの時間

    int mnAttackIntervalTime;   // 攻撃インターバル

    void NewActionSet();    // 新しいアクション設定

public:
    EnemyBattleBoss(Object_Base_Character *player, VECTOR position, float angle, STATUS status, CHARACTER_TYPE enemyType, std::string name);
    ~EnemyBattleBoss();

    void Initilize()    override;   // 初期化
    void Update()       override;   // 更新
    void Draw()         override;   // 描画
    void MyFinailize()  override;   // 終了処理

    void HpZeroMove() override; // HPが0以下時の処理

    void EndProcess();  // 終了処理
};