#pragma once
#include "DxLib.h"
#include "../Header/Player_Base.h"
#include "../Header/Status_Struct.h"

//class Camera;

class PlayerRobot : public Player_Base
{
private:
    void GenerationAttackObject() override; // 攻撃オブジェクト生成

    bool mbReflectionAttackFlag;    // 転がり攻撃反射フラグ

    int mnNextChengeTime;   // 次の変更出来るようになるまでの時間

public:

    PlayerRobot(Camera* camera, STATUS status, VECTOR position, float angle, std::string name, std::string dataFileName);   // コンストラクタ
    ~PlayerRobot();  // デストラクタ

    void MyInitilize()    override;   // 初期化
    void MyUpdate()       override;   // 更新
    void MyDraw()         override;   // 描画
    void MyFinailize()     override;   // 終了処理
};