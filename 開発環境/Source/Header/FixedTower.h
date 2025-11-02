#pragma once
#include "DxLib.h"
#include "../Header/Object_Base_Fixed.h"

class FixedTower : public Object_Base_Fixed
{
private:
    int mnModelNumber;  // モデル数
    int mnTowerHandle;  // モデルハンドル

    int mnXTowerNumber; // X軸にタワーの個数
    int mnZTowerNumber; // Z軸にタワーの個数

    float mfXTowerSize; // X方向の大きさ
    float mfZTowerSize; // Z方向の大きさ

    float mfErrorHitSize;   // ヒット時の誤差

public:
    FixedTower(VECTOR plusPosition, int modelNumber, const char *filename, int xTowerNumber = 1, int zTowerNumber = 1);  // コンストラクタ
    ~FixedTower();                                                // デストラクタ

    void Initilize()    override;   // 初期化
    void Update()       override;   // 更新
    void Draw()         override;   // 描画
    void MyFinalize()     override;   // 終了

    VECTOR CheckHit_ReturnAmountMoved(VECTOR checkPosition, VECTOR nowPosition, VECTOR moveVec, float size) override;   // 当たっていれば当たらない移動量を返す
};