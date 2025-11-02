#include <cmath>
#include "DxLib.h"
#include "../Header/Calculation.h"
#include "../Header/CoordinateXY.h"

/*
* @fn Check_Circle_And_Pos
* @drief 円とポジションの当たり判定を取得
*/
bool Calculation::Check_Circle_And_Pos(VECTOR CirclePos, float range, VECTOR Pos)
{
    VECTOR targetPos = VGet((Pos.x - CirclePos.x), 0.0f, (Pos.z - CirclePos.z));

    float targetAngle = std::atan2(targetPos.x, targetPos.z);
    VECTOR setPos = targetPos;
    targetPos.x = (std::cos(targetAngle) * setPos.x) - (std::sin(targetAngle) * setPos.z);
    targetPos.z = (std::sin(targetAngle) * setPos.x) + (std::cos(targetAngle) * setPos.z);

    float targetDistance = std::abs(targetPos.x) + std::abs(targetPos.z);

    return (targetDistance <= range);
}

/*
* @fn GetMovePos
* @drief ターゲットに対しての移動量割合を取得
*/
VECTOR Calculation::GetMovePos(VECTOR myPos, VECTOR targetPos)
{
    VECTOR move = VGet(targetPos.x -myPos.x, 0.0f, targetPos.z - myPos.z);


    float denominator = std::abs(move.x) + std::abs(move.z);

    move = VGet((std::abs(move.x) / denominator) * (std::signbit(move.x) ? -1 : 1), 0.0f, (std::abs(move.z) / denominator) * (std::signbit(move.z) ? -1 : 1));

    return move;
}

/*
* @fn GetNotExceedAngle
* @drief 方向を2から-2になるように調整する
*/
float Calculation::GetNotExceedAngle(float angle)
{
    if (angle > DX_PI_F) {
        angle -= DX_TWO_PI_F;
    }
    else if (angle < -DX_PI_F) {
        angle += DX_TWO_PI_F;
    }

    return angle;
}

/*
* @fn GetCirclePosAngle
* @drief 円の中心を軸に方向を得る関数
*/
float Calculation::GetCirclePosAngle(COORDINATE_X_Y centerOfTheCircle, COORDINATE_X_Y target)
{
    return std::atan2((target.x - centerOfTheCircle.x), (target.y - centerOfTheCircle.y));
}

/*
* @fn GetNotAnglePos_Circle
* @drief 円の中心を軸に方向を初期化したポジション
*/
COORDINATE_X_Y Calculation::GetNotAnglePos_Circle(COORDINATE_X_Y centerOfTheCircle, COORDINATE_X_Y target)
{
    COORDINATE_X_Y targetPos = XYGet(0.0f, 0.0f);

    float angle = GetCirclePosAngle(centerOfTheCircle, target);

    targetPos.x = (target.x * cosf(angle)) - (target.y * sinf(angle));
    targetPos.y = ((target.x * sinf(angle)) + (target.y * cosf(angle)));

    return targetPos;
}

/*
* @fn GetAnglePos_Circle
* @drief 円の中心を軸に指定の地点を指定量回した座標
*/
COORDINATE_X_Y Calculation::GetAnglePos_Circle(COORDINATE_X_Y centerOfTheCircle, COORDINATE_X_Y target, float angle)
{
    COORDINATE_X_Y targetPos = GetNotAnglePos_Circle(centerOfTheCircle, target);

    COORDINATE_X_Y setPos = targetPos;

    targetPos.x = setPos.y * sinf(angle);
    targetPos.y = setPos.y * cosf(angle);

    return targetPos;
}

/*
* @fn GetSphericalMove
* @drief 球面移動した場所を返す
*/
VECTOR Calculation::GetSphericalMove(float size, float verticalAngle, float horizontalAngle)
{
    VECTOR pos = VGet(0.0f, 0.0f, 0.0f);

    pos.x = size * cosf(GetNotExceedAngle(verticalAngle)) * sinf(GetNotExceedAngle(horizontalAngle));
    pos.y = size * sinf(GetNotExceedAngle(verticalAngle));
    pos.z = -(size * cosf(GetNotExceedAngle(verticalAngle)) * cosf(GetNotExceedAngle(horizontalAngle)));

    return pos;
}