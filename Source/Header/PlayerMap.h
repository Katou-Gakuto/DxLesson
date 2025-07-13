#pragma once
#include <iostream>
#include <string>

#include "DxLib.h"
#include "../Header/Camera.h"
#include "../Header/Player_Base.h"
#include "../Header/Status_Struct.h"

class PlayerMap : public Player_Base
{
private:

    void GenerationAttackObject() override; // 攻撃オブジェクト生成

public:
    PlayerMap(Camera *camera, STATUS status, VECTOR position, float angle, std::string name, std::string dataFileName);
    ~PlayerMap();

    void MyInitilize()    override;   // 初期化
    void MyUpdate()       override;   // 更新
    void MyDraw()         override;   // 描画
    void MyFinailize()     override;   // 終了処理
};