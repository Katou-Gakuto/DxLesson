#pragma once
#include <vector>
#include "DxLib.h"

class Object_Base_Character;

class Targets {
    
private:
    Object_Base_Character *mpTargetPlayer;                // プレイヤー

    std::vector<Object_Base_Character *>mpTargetEnemy;    // エネミー

public:
    Targets();  // コンストラクタ
    ~Targets(); // デストラクタ

    VECTOR GetPlayerPosition();             // プレイヤー座標取得
    void SetPlayer(Object_Base_Character * player);    // プレイヤーオブジェクト設定

    void AddTargetEnemy(Object_Base_Character *enemy);                                // エネミー追加
    std::vector<Object_Base_Character *>GetTargetEnemys() { return mpTargetEnemy; }   // エネミー取得
};