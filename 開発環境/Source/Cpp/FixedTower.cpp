#include "DxLib.h"
#include "../Header/FixedTower.h"
#include "../Header/GameManager.h"
#include "../Header/ModelManager.h"
#include "../Header/ObjectTagMacro.h"
#include "../Header/Object_Base_Fixed.h"

/*
* @fn コンストラクタ
*/
FixedTower::FixedTower(VECTOR plusPosition, int modelNumber, const char *filename, int xTowerNumber, int zTowerNumber)
: Object_Base_Fixed(GetColor(0, 0, 0))
, mnModelNumber(modelNumber)
, mnXTowerNumber(xTowerNumber)
, mnZTowerNumber(zTowerNumber)
{
    mfErrorHitSize = 1.5;

    mnTowerHandle = Master::mpGameManager->GetModelManager()->GetModelNumber(filename, true);

    mfXTowerSize = -600.0f * xTowerNumber;
    mfZTowerSize = -600.0f * zTowerNumber;

    SetPlusMinusPosition(plusPosition, VGet(plusPosition.x + mfXTowerSize, 0.0f, plusPosition.z + mfZTowerSize));
}

/*
* @fn デストラクタ
*/
FixedTower::~FixedTower()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void FixedTower::Initilize()
{
    SetTag(WALL_TAG);
}

/*
* @fn Update
* @drief 更新
*/
void FixedTower::Update()
{
}

/*
* @fn Draw
* @drief 描画
*/
void FixedTower::Draw()
{
    if (mnTowerHandle != -1) {
        for (int x = 0; x < mnXTowerNumber; x++) {
            for (int z = 0; z < mnZTowerNumber; z++) {
                for (int i = 0; i < 3; i++) {
                    MV1SetRotationXYZ(mnTowerHandle, VGet(0.0f, 0.0f, 0.0f));
                    MV1SetPosition(mnTowerHandle, VGet(mvPlusPosition.x + ((mfXTowerSize / mnXTowerNumber) * x), i * 1000.0f, mvPlusPosition.z + ((mfZTowerSize / mnZTowerNumber) * z)));
                    MV1DrawModel(mnTowerHandle);

                    MV1SetRotationXYZ(mnTowerHandle, VGet(0.0f, DX_PI_F, 0.0f));
                    MV1SetPosition(mnTowerHandle, VGet(mvMinusPosition.x - ((mfXTowerSize / mnXTowerNumber) * ((mnXTowerNumber - 1) - x)), i * 1000.0f, mvMinusPosition.z - ((mfZTowerSize / mnZTowerNumber) * ((mnZTowerNumber - 1) - z))));
                    MV1DrawModel(mnTowerHandle);

                    if (mnModelNumber > 2) {//?
                        MV1SetRotationXYZ(mnTowerHandle, VGet(0.0f, DX_PI_F * 0.5f, 0.0f));
                        MV1SetPosition(mnTowerHandle, VGet(mvPlusPosition.x + (x * mfXTowerSize), i * 1000.0f, mvMinusPosition.z + (z * mfZTowerSize)));
                        MV1DrawModel(mnTowerHandle);
                        MV1SetRotationXYZ(mnTowerHandle, VGet(0.0f, DX_PI_F * (-0.5f), 0.0f));
                        MV1SetPosition(mnTowerHandle, VGet(mvMinusPosition.x + (x * mfXTowerSize), i * 1000.0f, mvPlusPosition.z + (z * mfZTowerSize)));
                        MV1DrawModel(mnTowerHandle);
                    }
                }
            }
        }
    }
    else {
        DrawTriangle3D(mvPlusPosition, VGet(mvPlusPosition.x, 0.0f, mvMinusPosition.z), VGet(mvMinusPosition.x, 0.0f, mvPlusPosition.z), GetColor(0, 255, 0), TRUE);
        DrawTriangle3D(mvMinusPosition, VGet(mvPlusPosition.x, 0.0f, mvMinusPosition.z), VGet(mvMinusPosition.x, 0.0f, mvPlusPosition.z), GetColor(0, 255, 0), TRUE);
    }
}

/*
* @fn MyFinalize
* @drief 終了
*/
void FixedTower::MyFinalize()
{
    MV1DeleteModel(mnTowerHandle);
}

/*
* @fn CheckHit_ReturnAmountMoved
* @drief 当たっていれば当たらない移動量を返す
*/
VECTOR FixedTower::CheckHit_ReturnAmountMoved(VECTOR checkPosition, VECTOR nowPosition, VECTOR moveVec, float size)
{
    VECTOR setVec = VGet(0.0f, 0.0f, 0.0f);
    size = (size * 1.3);

    if (((mvPlusPosition.x >= (checkPosition.x - size)) && ((checkPosition.x + size) >= (mvMinusPosition.x))) &&
        ((mvPlusPosition.z >= (checkPosition.z - size)) && ((checkPosition.z + size) >= (mvMinusPosition.z)))) {
        if (mvPlusPosition.x <= (nowPosition.x - size)) {
            setVec.x += (mvPlusPosition.x - (checkPosition.x - size - 1.0f));
        }
        if (mvPlusPosition.z <= (nowPosition.z - size)) {
            setVec.z += (mvPlusPosition.z - (checkPosition.z - size - 1.0f));
        }
        if ((nowPosition.x + size) <= (mvMinusPosition.x)) {
            setVec.x += ((mvMinusPosition.x) - (checkPosition.x + size + 1.0f));
        }
        if ((nowPosition.z + size) <= (mvMinusPosition.z)) {
            setVec.z += ((mvMinusPosition.z) - (checkPosition.z + size + 1.0f));
        }

        /*if ((setVec.x != 0.0f) && (setVec.z != 0.0f)) {
            if (moveVec.x == moveVec.z) {
            }
            else if (moveVec.x > moveVec.z) {
                setVec.x = 0.0f;
            }
            else if (moveVec.x < moveVec.z) {
                setVec.z = 0.0f;
            }
        }*/
    }

    return setVec;
}