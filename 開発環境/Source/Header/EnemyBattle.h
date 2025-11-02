#pragma once
#include <iostream>
#include <string>

#include "DxLib.h"
#include "../Header/CharacterType_Enum.h"
#include "../Header/Data_Structs.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/Status_Struct.h"

class EnemyBattle : public Object_Base_Character
{
private:
    Object_Base_Character *mpPlayer;    // プレイヤー
    
    CHARACTER_TYPE meEnemyType; // エネミータイプ

    int mnAttackTime;  // 攻撃した時間

    int mnCloseAttackInterval;  // インターバルタイム(近距離)
    int mnMediumAttackInterval; // インターバルタイム(中距離)
    int mnFarAttackInterval;    // インターバルタイム(遠距離)

    float mfCloseDistance;  // 近距離
    float mfMediumDistance; // 中距離
    float mfFarDistance;    // 遠距離
    
public:
    EnemyBattle(Object_Base_Character *player, VECTOR position, float angle, STATUS status, CHARACTER_TYPE enemyType, std::string name, float closeDistance = 300.0f, float mediumDistance = 2000.0f, float farDistance = 10000.0f); // コンストラクタ
    ~EnemyBattle(); // デストラクタ

    void Initilize()    override;   // 初期化
    void Update()       override;   // 更新
    void Draw()         override;   // 描画
    void MyFinailize()  override;   // 終了処理

    void HpZeroMove() override; // HPが0以下時の処理

    int PlayerCheck();  // プレイヤーが度の距離にいるのか調べる

    VECTOR PlayerDistance();    // プレイヤーまでの距離
    VECTOR EnemyMove();         // このキャラクターの移動量

    void EndProcess();  // 終了処理
};