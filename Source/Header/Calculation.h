#pragma once
#include "DxLib.h"
#include "../Header/CoordinateXY.h"
// 計算用クラス
class  Calculation{
public:
    /// <summary>
    /// 円とポジションの当たり判定 使うのはx軸とz軸
    /// </summary>
    /// <param name="CirclePos">円の中心</param>
    /// <param name="range">判定距離</param>
    /// <param name="Pos">ポジション</param>
    /// <returns>判定</returns>
    static bool Check_Circle_And_Pos(VECTOR CirclePos, float range, VECTOR Pos);

    /// <summary>
    /// ターゲットに対しての移動量割合を取得
    /// </summary>
    /// <param name="myPos">自分の位置</param>
    /// <param name="targetPos">ターゲットの位置</param>
    /// <returns>移動量割合</returns>
    static VECTOR GetMovePos(VECTOR myPos, VECTOR targetPos);
    
    /// <summary>
    /// 方向を2から-2になるように調整する
    /// </summary>
    /// <param name="angle">方向</param>
    /// <returns>方向</returns>
    static float GetNotExceedAngle(float angle);

    // 
    /// <summary>
    /// 円の中心を軸に方向を得る関数
    /// </summary>
    /// <param name="centerOfTheCircle">円の中心</param>
    /// <param name="target">ターゲット座標</param>
    /// <returns>方向</returns>
    static float GetCirclePosAngle(COORDINATE_X_Y centerOfTheCircle, COORDINATE_X_Y target);

    /// <summary>
    /// 円の中心を軸に方向を初期化したポジション
    /// </summary>
    /// <param name="centerOfTheCircle">円の中心</param>
    /// <param name="target">ターゲット座標</param>
    /// <returns>中心から0の方向まで移動させたの場所</returns>
    static COORDINATE_X_Y GetNotAnglePos_Circle(COORDINATE_X_Y centerOfTheCircle, COORDINATE_X_Y target);

    /// <summary>
    /// 円の中心を軸に指定の地点を指定量回した座標
    /// </summary>
    /// <param name="centerOfTheCircle">円の中心</param>
    /// <param name="target">ターゲット</param>
    /// <param name="angle">方向</param>
    /// <returns>指定された方向分移動させた場所</returns>
    static COORDINATE_X_Y GetAnglePos_Circle(COORDINATE_X_Y centerOfTheCircle, COORDINATE_X_Y target, float angle);
    
    /// <summary>
    /// 球面移動した場所を返す
    /// </summary>
    /// <param name="size">中心からの距離</param>
    /// <param name="verticalAngle">垂直</param>
    /// <param name="horizontalAngle">水平方向</param>
    /// <returns>(0,0,0)を中心とした移動座標</returns>
    static VECTOR GetSphericalMove(float size, float verticalAngle, float horizontalAngle);
};