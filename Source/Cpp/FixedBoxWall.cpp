#include "DxLib.h"
#include "../Header/FixedBoxWall.h"
#include "../Header/GameManager.h"
#include "../Header/ModelManager.h"
#include "../Header/ObjectTagMacro.h"
#include "../Header/Object_Base_Fixed.h"

/*
* @fn コンストラクタ
*/
FixedBoxWall::FixedBoxWall(VECTOR plusPosition, VECTOR minusPosition, char *filename)
: Object_Base_Fixed(GetColor(255, 255, 255))
{
    mnWallHandle = Master::mpGameManager->GetModelManager()->GetModelNumber(filename, true);

    SetPlusMinusPosition(plusPosition, minusPosition);
}

/*
* @fn デストラクタ
*/
FixedBoxWall::~FixedBoxWall()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void FixedBoxWall::Initilize()
{
    SetTag(WALL_TAG);
}

/*
* @fn Update
* @drief 更新
*/
void FixedBoxWall::Update()
{
}

/*
* @fn Draw
* @drief 描画
*/
void FixedBoxWall::Draw()
{
    if (mnWallHandle != -1) {
        for (int i = 0; i < (((mvPlusPosition.x / 3) * 0.01) + 2); i++) {
            for (int j = 0; j <= (((mvPlusPosition.z / 3) * 0.01) + 2); j++) {
                MV1SetPosition(mnWallHandle, VGet((i * 600.0f) + mvMinusPosition.x, 50.0f, (j * 600.0f) + mvMinusPosition.z));
                MV1DrawModel(mnWallHandle);
            }
        }
    }
}

/*
* @fn Finalize
* @drief 終了
*/
void FixedBoxWall::MyFinalize()
{
    MV1DeleteModel(mnWallHandle);
}

/*
* @fn CheckHit_ReturnAmountMoved
* @drief 当たっていれば当たらない移動量を返す
*/
VECTOR FixedBoxWall::CheckHit_ReturnAmountMoved(VECTOR checkPosition, VECTOR nowPosition, VECTOR moveVec, float size)
{
    VECTOR setMove = VGet(0.0f, 0.0f, 0.0f);

    if (mvPlusPosition.x < ((checkPosition.x + size) + setMove.x)) {
        setMove.x += (mvPlusPosition.x - ((checkPosition.x + size) + setMove.x));
    }
    if (mvPlusPosition.y < (checkPosition.y + setMove.y)) {
        setMove.y += (mvPlusPosition.y - (checkPosition.y + setMove.y));
    }
    if (mvPlusPosition.z < ((checkPosition.z + size) + setMove.z)) {
        setMove.z += (mvPlusPosition.z - ((checkPosition.z + size) + setMove.z));
    }

    if (mvMinusPosition.x > ((checkPosition.x - size) + setMove.x)) {
        setMove.x += (mvMinusPosition.x - ((checkPosition.x - size) + setMove.x));
    }
    if (mvMinusPosition.y > (checkPosition.y + setMove.y)) {
        setMove.y += (mvMinusPosition.y - (checkPosition.y + setMove.y));
    }
    if (mvMinusPosition.z > ((checkPosition.z - size) + setMove.z)) {
        setMove.z += (mvMinusPosition.z - ((checkPosition.z - size) + setMove.z));
    }


    return setMove;
}
