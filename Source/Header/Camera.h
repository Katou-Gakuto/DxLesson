#pragma once
#include "DxLib.h"

/*
* 前方宣言
*/
class Object_Base_Character;

/*
  カメラ　クラス
*/
class Camera
{
public:
    Camera();   // コンストラクタ
    ~Camera();  // デストラクタ

    void InitializeModeTarget(Object_Base_Character *target);                     // ターゲット追尾モードで初期化
    void InitializeModeTargetLRMove(Object_Base_Character *target);               // ターゲット追尾モードLRキーカメラ移動で初期化
    void InitializeModeLook(VECTOR position, VECTOR lookAtPosition);    // 固定モードで初期化
    void Updete();                                                      // 更新

    //-- カメラモード関連 --//
    enum CAMERA_MODE // カメラモード
    {
        TARGET_CHASE_MODE,          // ターゲット追尾モード
        TARGET_CHASE_MODE_L_R_MOVE, // ターゲット追尾モードLRキーカメラ移動
        LOOK_POSITION_MODE,         // 固定モード
    };

    CAMERA_MODE GetCameraMode() { return meCameraMode; }    // 現在のカメラモード取得
    void SetCameraMode(CAMERA_MODE mode);                 // カメラモード設定
    //                      //

    // カメラモード別処理
    VECTOR GetPosition();       // カメラの位置取得
    VECTOR GetLookAtPosition(); // カメラの注視点取得
    VECTOR GetDirection();      // カメラの方向取得
    

    //-- モード「TARGET_CHASE」関連 --//
    float GetTarget_HorizontalAngle() { return mfHorizontalAngle_Target; }  // 水平アングル取得
    float GetTarget_VerticalAngle() { return mfVerticalAngle_Target; }      // 垂直アングル取得

    VECTOR GetTarget_Position() { return mvPosition_Target; }               // ターゲット追尾モードのカメラの位置取得
    VECTOR GetTarget_LookAtPosition() { return mvLookAtPosition_Target; }   // ターゲット追尾モードのカメラの注視点取得
    //                                //

    //-- モード「LOOK_POSITION」関連 --//
    void SetLook_Position(VECTOR position) { mvPosition_Look = position; }              // 固定モードのカメラの位置設定
    VECTOR GetLook_Position() { return mvPosition_Look; }                               // 固定モードのカメラの位置取得

    void SetLook_LookAtPosition(VECTOR position) { mvLookAtPosition_Look = position; }  // 固定モードのカメラの注視点設定
    VECTOR GetLook_LookAtPosition() { return mvLookAtPosition_Look; }                   // 固定モードのカメラの注視点取得
    //                                 //


    void Initialize3DCameraTemplate();  // 3Dカメラのテンプレート設定

private:

    CAMERA_MODE meCameraMode;  // カメラモード


    float mfHorizontalAngle_Target;    // 水平方向アングル
    float mfVerticalAngle_Target;      // 垂直方向アングル
    
    VECTOR mvPosition_Target;          // カメラ位置
    VECTOR mvLookAtPosition_Target;    // カメラ注視点

    Object_Base_Character * mpTarget;           // ターゲットポインタ

    const float ANGLE_SPEED = 3.0f; // カメラスピード


    VECTOR mvPosition_Look;       // 固定カメラ位置
    VECTOR mvLookAtPosition_Look;   // 固定カメラ注視点

    float mfCameraDistance; // カメラと目標物の距離
};