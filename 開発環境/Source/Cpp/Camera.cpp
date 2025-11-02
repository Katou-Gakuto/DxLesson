#include <math.h>

#include "DxLib.h"
#include "../Header/Calculation.h"
#include "../Header/Camera.h"
#include "../Header/GameManager.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/Operation.h"
#include "../Header/SceneManager.h"
#include "../Header/SoundManager.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
Camera::Camera()
: mfHorizontalAngle_Target(0.0f)
, mfVerticalAngle_Target(0.0f)
, mvPosition_Target(VGet(0.0f, 0.0f, 0.0f))
, mvLookAtPosition_Target(VGet(0.0f, 0.0f, 0.0f))
, mvPosition_Look(VGet(0.0f, 0.0f, 0.f))
, mvLookAtPosition_Look(VGet(0.0f, 0.0f, 0.0f))
, mpTarget(nullptr)
, meCameraMode(Camera::LOOK_POSITION_MODE)
, mfCameraDistance(0.0f)
{
}

/*
* @fn デストラクタ
*/
Camera::~Camera()
{
}

/*
* @fn InitializeModeTarget
* @drief 「TARGET_CHASE」で初期化
*/
void Camera::InitializeModeTarget(Object_Base_Character *target)
{
    // プレイヤー情報を保持しておく
    mpTarget = target;

    SetCameraMode(Camera::TARGET_CHASE_MODE);

    mfHorizontalAngle_Target = (0.0f + target->GetObjectAngle());
    mfVerticalAngle_Target = 15.0f;
    mfCameraDistance = 400.0f;

    // 3Dカメラ設定
    Initialize3DCameraTemplate();
}

/*
* @fn InitializeModeTargetLRMove
* @drief 「TARGET_CHASE_MODE_L_R_MOVE」で初期化
*/
void Camera::InitializeModeTargetLRMove(Object_Base_Character *target)
{
    // プレイヤー情報を保持しておく
    mpTarget = target;

    SetCameraMode(Camera::TARGET_CHASE_MODE_L_R_MOVE);

    mfHorizontalAngle_Target = (0.0f + target->GetObjectAngle());
    mfVerticalAngle_Target = 15.0f;
    mfCameraDistance = 400.0f;

    // 3Dカメラ設定
    Initialize3DCameraTemplate();
}

/*
* @fn InitializeModeLook
* @drief 「LOOK_POSITION」で初期化
*/
void Camera::InitializeModeLook(VECTOR position, VECTOR lookAtPosition)
{
    mvPosition_Look = position;
    mvLookAtPosition_Look = lookAtPosition;

    SetCameraMode(Camera::LOOK_POSITION_MODE);
    
    if (mvLookAtPosition_Look.x == mvPosition_Look.x &&
        mvLookAtPosition_Look.z == mvPosition_Look.z) {
        mvPosition_Look.z -= 1.0f;
    }

    // 3Dカメラ設定
    Initialize3DCameraTemplate();
}

/*
* @fn Updete
* @drief 更新
*/
void Camera::Updete()
{
    /*
    // 時間停止フラグが有効なら更新しない
    if (Master::mpGameManager->GetTimeManager()->GetStopFlag()) {
        return;
    }*/

    switch (meCameraMode) {
    case Camera::LOOK_POSITION_MODE:

        // カメラ位置を反映する
        SetCameraPositionAndTarget_UpVecY(mvPosition_Look, mvLookAtPosition_Look);
        Set3DSoundListenerPosAndFrontPos_UpVecY(mvPosition_Look, mvLookAtPosition_Look);
        break;

    case Camera::TARGET_CHASE_MODE_L_R_MOVE:
    case Camera::TARGET_CHASE_MODE:

        // 時間停止フラグが有効なら更新しない
        if (Master::mpGameManager->GetTimeManager()->GetStopFlag()) {
            break;
        }
        // カメラアングル変更
        if (meCameraMode == TARGET_CHASE_MODE)
        {
            if (Operation::CheckLeftKey())
            {
                mfHorizontalAngle_Target += 3.0f;
                if (mfHorizontalAngle_Target >= 180.0f)
                {
                    mfHorizontalAngle_Target -= 360.0f;
                }
            }
            if (Operation::CheckRightKey())
            {
                mfHorizontalAngle_Target -= 3.0f;
                if (mfHorizontalAngle_Target <= (-180.0f))
                {
                    mfHorizontalAngle_Target += 360.0f;
                }
            }

            if (Operation::CheckUpKey())
            {
                mfVerticalAngle_Target += 3.0f;
                if (mfVerticalAngle_Target >= 70.0f)
                {
                    mfVerticalAngle_Target = 70.0f;
                }
            }
            if (Operation::CheckDownKey())
            {
                mfVerticalAngle_Target -= 3.0f;
                if (mfVerticalAngle_Target <= 0.0f)
                {
                    mfVerticalAngle_Target = 0.0f;
                }
            }
        }
        else if (meCameraMode == TARGET_CHASE_MODE_L_R_MOVE)
        {
            if (Operation::CheckLKey())
            {
                mfHorizontalAngle_Target += 3.0f;
                if (mfHorizontalAngle_Target >= 180.0f)
                {
                    mfHorizontalAngle_Target -= 360.0f;
                }
            }
            if (Operation::CheckRKey())
            {
                mfHorizontalAngle_Target -= 3.0f;
                if (mfHorizontalAngle_Target <= (-180.0f))
                {
                    mfHorizontalAngle_Target += 360.0f;
                }
            }
        }
        

        // カメラの位置と向きを設定
        {

            // 注視点はキャラクターモデルの座標から少し高い位置にしておく
            if (mpTarget != nullptr) {
                mvLookAtPosition_Target = mpTarget->GetObjectPosition();
            }
            else {
                mvLookAtPosition_Target = VGet(0.0f, 0.0f, 0.0f);
            }

            mvLookAtPosition_Target.y += 180.0f;

            // 球面座標(3次元の極座標)への変換式を使う
            // x = r * cosφsinθ
            // y = r * sinφ
            // z = r * cosφcosθ
            VECTOR tempPosition2 = Calculation::GetSphericalMove(mfCameraDistance, mfVerticalAngle_Target / 180.0f * DX_PI, mfHorizontalAngle_Target / 180.0f * DX_PI_F);
            //tempPosition2.x = 250.0f * cosf(mfVerticalAngle_Target / 180.0f * DX_PI) * sinf(mfHorizontalAngle_Target / 180.0f * DX_PI_F);
            //tempPosition2.y = 250.0f * sinf(mfVerticalAngle_Target / 180.0f * DX_PI);
            //tempPosition2.z = -(250.0f * cosf(mfVerticalAngle_Target / 180.0f * DX_PI) * cosf(mfHorizontalAngle_Target / 180.0f * DX_PI_F));

            // 算出した座標に注視点の位置を加算したものがカメラ位置
            mvPosition_Target = VAdd(tempPosition2, mvLookAtPosition_Target);

            // カメラ位置を反映する
            SetCameraPositionAndTarget_UpVecY(mvPosition_Target, mvLookAtPosition_Target);
            Set3DSoundListenerPosAndFrontPos_UpVecY(mvPosition_Target, mvLookAtPosition_Target);
        }
        break;

    default:
        break;
    }
}

/*
* @fn SetCameraMode
* @drief カメラのモードを変更
*/
void Camera::SetCameraMode(CAMERA_MODE mode)
{
    switch (mode) 
    {
    case Camera::LOOK_POSITION_MODE:
        if (mvLookAtPosition_Look.x != mvPosition_Look.x ||
            mvLookAtPosition_Look.y != mvPosition_Look.y ||
            mvLookAtPosition_Look.z != mvPosition_Look.z)
        {
            meCameraMode = mode;
        }
        break;

    case Camera::TARGET_CHASE_MODE_L_R_MOVE:
    case Camera::TARGET_CHASE_MODE:
        if (mpTarget != nullptr)
        {
            meCameraMode = mode;
        }
        break;
    }
}

/*
* @fn GetPosition
* @drief モードに合わせたカメラの位置を取得
*/
VECTOR Camera::GetPosition()
{
    switch (meCameraMode) {
    case Camera::LOOK_POSITION_MODE:
        return mvPosition_Look;

    case Camera::TARGET_CHASE_MODE_L_R_MOVE:
    case Camera::TARGET_CHASE_MODE:
        return mvPosition_Target;
    }
}

/*
* @fn GetLookAtPosition
* @drief モードに合わせたカメラの注視点を取得
*/
VECTOR Camera::GetLookAtPosition()
{
    switch (meCameraMode) {
    case Camera::LOOK_POSITION_MODE:
        return mvLookAtPosition_Look;

    case Camera::TARGET_CHASE_MODE_L_R_MOVE:
    case Camera::TARGET_CHASE_MODE:
        return mvLookAtPosition_Target;
    }
}
/*
* @fn GetDirection
* @drief カメラの方向取得
*/
VECTOR Camera::GetDirection()
{
    return VGet(GetLookAtPosition().x - GetPosition().x, GetLookAtPosition().y - GetPosition().y, GetLookAtPosition().z - GetPosition().z);
}

/*
* @fn InitializeTemplate
* @drief カメラ初期化テンプレート
*/
void Camera::Initialize3DCameraTemplate()
{
    // カメラの位置と向きを設定
    SetCameraPositionAndTarget_UpVecY
    (VGet(0.0f, 100.f, -200.0f),
        VGet(0.0f, 100.0f, 0.0f)
    );

    // カメラのクリッピング距離を設定。(カメラが映せる上限範囲)
    SetCameraNearFar(16.f, 7000.0f);
//    SetCameraNearFar(16.f, 3800.0f);

    // 背景の色を灰色にする
    SetBackgroundColor(128, 128, 128);

    // Zバファに書き込む準備
    SetUseZBufferFlag(true);
    SetWriteZBufferFlag(true);

    // 映す場所を指定し直す
    switch (meCameraMode) {
    case Camera::LOOK_POSITION_MODE:
        // カメラ位置を反映する
        SetCameraPositionAndTarget_UpVecY(mvPosition_Look, mvLookAtPosition_Look);
        break;
    case Camera::TARGET_CHASE_MODE_L_R_MOVE:
    case Camera::TARGET_CHASE_MODE:
        // カメラの位置と向きを設定
        {

            // 注視点はキャラクターモデルの座標から少し高い位置にしておく
            if (mpTarget != nullptr) {
                mvLookAtPosition_Target = mpTarget->GetObjectPosition();
            }
            else {
                mvLookAtPosition_Target = VGet(0.0f, 0.0f, 0.0f);
            }

            mvLookAtPosition_Target.y += 180.0f;

            // 球面座標(3次元の極座標)への変換式を使う
            // x = r * cosφsinθ
            // y = r * sinφ
            // z = r * cosφcosθ
            VECTOR tempPosition2 = Calculation::GetSphericalMove(mfCameraDistance, mfVerticalAngle_Target / 180.0f * DX_PI, mfHorizontalAngle_Target / 180.0f * DX_PI_F);
            //tempPosition2.x = 250.0f * cosf(mfVerticalAngle_Target / 180.0f * DX_PI) * sinf(mfHorizontalAngle_Target / 180.0f * DX_PI_F);
            //tempPosition2.y = 250.0f * sinf(mfVerticalAngle_Target / 180.0f * DX_PI);
            //tempPosition2.z = -(250.0f * cosf(mfVerticalAngle_Target / 180.0f * DX_PI) * cosf(mfHorizontalAngle_Target / 180.0f * DX_PI_F));

            // 算出した座標に注視点の位置を加算したものがカメラ位置
            mvPosition_Target = VAdd(tempPosition2, mvLookAtPosition_Target);

            // カメラ位置を反映する
            SetCameraPositionAndTarget_UpVecY(mvPosition_Target, mvLookAtPosition_Target);
        }
        break;

    default:
        break;
    }
}