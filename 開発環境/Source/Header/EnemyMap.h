#pragma once
#include "DxLib.h"
#include "../Header/CharacterType_Enum.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/Scene_Enum.h"
#include "../Header/Status_Struct.h"

class EnemyMap : public Object_Base_Character 
{
private:

    Object_Base_Character *mpPlayer;  // プレイヤー

    //float mfSearchRange;    // 索敵範囲

    //bool mbEncounterFlag;   // エンカウントフラグ

    SCENE meSetScene;   // 移動先シーン

    CHARACTER_TYPE meEnemyType; // キャラクタータイプ

    int mnSurvivalFlag;    // 生存フラグ

public:
    EnemyMap(Object_Base_Character * player, VECTOR position, float angle, STATUS status, SCENE setScene, std::string name, std::string dataFileName, CHARACTER_TYPE enemyType, bool survivalFlag);    // コンストラクタ
    ~EnemyMap();                                // デストラクタ

    void Initilize()    override;   // 初期化
    void Update()       override;   // 更新
    void Draw()         override;   // 描画
    void MyFinailize()     override;   // 終了処理

    void HpZeroMove() override; // HPが0以下時の処理

    bool PlayerCheck(); // プレイヤーが近くに居るか

    void SetEnemyDataSurvivalFlag();    // このエネミーのデータの生存フラグをfalseにする

    void SetDeleteData();   // このデータを削除する
};