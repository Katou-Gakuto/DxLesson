#pragma once
#include "DxLib.h"
#include "../Header/Object_Base_Fixed.h"

class FixedBoxWall : public Object_Base_Fixed
{
private:
    int mnWallHandle;   // 壁ハンドル

public:
    FixedBoxWall(VECTOR plusPosition, VECTOR minusPosition, char *filename);  // コンストラクタ
    ~FixedBoxWall();                                                // デストラクタ

    void Initilize()    override;   // 初期化
    void Update()       override;   // 更新
    void Draw()         override;   // 描画
    void MyFinalize()     override;   // 終了

    VECTOR CheckHit_ReturnAmountMoved(VECTOR checkPosition, VECTOR nowPosition, VECTOR moveVec, float size) override;   // 当たっていれば当たらない移動量を返す
};