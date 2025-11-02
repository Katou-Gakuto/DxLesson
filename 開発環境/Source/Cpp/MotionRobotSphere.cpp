#include <cmath>

#include "DxLib.h"
#include "../Header/Attack_Rolling.h"
#include "../Header/Calculation.h"
#include "../Header/CoordinateXY.h"
#include "../Header/GameManager.h"
#include "../Header/MotionRobotSphere.h"
#include "../Header/Motion_Base.h"
#include "../Header/ObjectManager.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/Operation.h"
#include "../Header/SoundManager.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
MotionRobotSphere::MotionRobotSphere(Object_Base_Character *character, int relaxedTime, bool endObjectFlag, bool attackReflectionFlag)
: Motion_Base(character, "Resource/3D/Test/robotSphere.mv1", true, endObjectFlag)
//: Motion_Base(character, "Resource/3D/Hero.x", false)
, mbStartFlag(true)
, mnStartTime(0)
, mbRelaxedFlag(false)
, mnRelaxedTime(0)
, mbAttackStartFlag(false)
, mbAttackMiddleFlag(false)
, mbAttackEndFlag(false)
, mnAttackFlagChangeTime(0)
, mnSetRelaxedTime(relaxedTime)
, mfMaxAttackMiddleMotionTime(0)
, mbAttackReflectionFlag(attackReflectionFlag)
, mnNextWalkSoundTime(0)
, mbOneFlag(true)
{
}

/*
* @fn デストラクタ
*/
MotionRobotSphere::~MotionRobotSphere()
{
}

/*
* @fn MyInitilize
* @drief 初期化
*/
void MotionRobotSphere::MyInitilize()
{
    if (GetNotOneAnimFlag()) {
        MV1SetScale(mnModelHandle, VScale(VGet(20.0f, 20.0f, 20.0f), mpCharacter->GetStatus().size * 0.01));
    }
    AddAnim("Resource/3D/Test/Animation/robotSphere@anim_open.mv1");
    AddAnim("Resource/3D/Test/Animation/robotSphere@anim_Idle_Loop_S.mv1");
    AddAnim("Resource/3D/Test/Animation/robotSphere@anim_open_Idle_F1.mv1");
    AddAnim("Resource/3D/Test/Animation/robotSphere@anim_open_Walk_Loop.mv1");
    AddAnim("Resource/3D/Test/Animation/robotSphere@anim_open_GoToRoll.mv1");
    
    AddAnim("Resource/3D/Test/Animation/robotSphere@anim_cloed_Roll_Loop.mv1"); // 消す
    /*
    AddAnim("Resource/3D/Test/Animation/robotSphere@anim_cloed_Roll_Loop.mv1");*/
    
    AddAnim("Resource/3D/Test/Animation/robotSphere@anim_closed_StopRoll.mv1");
    AddAnim("Resource/3D/Test/Animation/robotSphere@anim_close.mv1");

    {   // スタート時間設定
        //int attachIndex = MV1AttachAnim(mnModelHandle, 0, mnAnimHandle[0], FALSE);
        //float plusTime = MV1GetAttachAnimTotalTime(mnModelHandle, attachIndex);

        //MV1DetachAnim(mnModelHandle, attachIndex);
        if (mbEndObjectFlag) {
            mnStartTime = 0;
        }
        else {
            mnStartTime = (mpTimeManager->GetGameTime() + (/*(plusTime / 0.5)*/GetAnimationTimeFrame(0) * mpTimeManager->GetOneFrame()));
        }
    }

    // 休憩までの時間を設定
    mnRelaxedTime = (mpTimeManager->GetGameTime() + (mpTimeManager->GetOneFrame() * mnSetRelaxedTime));

    // 攻撃中再生時間首取得
    mfMaxAttackMiddleMotionTime = (GetAnimationTimeFrame(GetIndexNumber("AttackMiddle")) * GetPrayAnimSpeed());
}

/*
* @fn MyUpdata
* @drief 更新
*/
void MotionRobotSphere::MyUpdata()
{
    if (mbAttackMiddleFlag) {
        // 回転させる
        float totalRotational = (mfMaxAttackMiddleMotionTime - (GetAnimCount() / mfMaxAttackMiddleMotionTime));

        MV1SetRotationXYZ(mnModelHandle, VGet(totalRotational * (DX_PI_F * 2.0f), mfAngle + DX_PI_F, 0.0f));

        VECTOR tempPosition2 = Calculation::GetSphericalMove(mpCharacter->GetStatus().size, (totalRotational * (DX_PI_F * 2.0f)) + (DX_PI_F * 1.5), -mfAngle);
        //tempPosition2.x = ATTACK_MIDDLE_XYZ_SET * cosf(Calculation::GetNotExceedAngle((totalRotational * (DX_PI_F * 2.0f)) + (DX_PI_F * 1.5))) * sinf(Calculation::GetNotExceedAngle(-mfAngle));
        //tempPosition2.y = ATTACK_MIDDLE_XYZ_SET * sinf(Calculation::GetNotExceedAngle((totalRotational * (DX_PI_F * 2.0f)) + (DX_PI_F * 1.5)));
        //tempPosition2.z = -(ATTACK_MIDDLE_XYZ_SET * cosf(Calculation::GetNotExceedAngle((totalRotational * (DX_PI_F * 2.0f)) + (DX_PI_F * 1.5))) * cosf(Calculation::GetNotExceedAngle(-mfAngle)));

        SetPosition(VAdd(VAdd(mpCharacter->GetObjectPosition(), 
                            VGet(0.0f, mpCharacter->GetStatus().size, 0.0f)),
                    VGet(-tempPosition2.x, tempPosition2.y, -tempPosition2.z)));
    }

}

/*
* @fn MyDraw
* @drief 描画
*/
void MotionRobotSphere::MyDraw()
{
//    DrawFormatString(0, 220, GetColor(0, 255, 255), "時間を表示中  : %d ", mpTimeManager->GetGameTime());
}

/*
* @fn MyFinalize
* @drief 終了処理
*/
void MotionRobotSphere::MyFinalize()
{
}

/*
* @fn ReSetPlusFlag
* @drief 追加したフラグをリセットする
*/
void MotionRobotSphere::ReSetPlusFlag()
{

}

/*
* @fn SetPlusDataSort
* @drief 追加したデータを整理する
*/
void MotionRobotSphere::SetPlusDataSort()
{
    // スタート
    if (mnStartTime <= mpTimeManager->GetGameTime() && mbStartFlag) {
        mbStartFlag = false;
    }
    else if (mbOneFlag) {
        Set3DSound(SOUND_3D::ROBOT_ATTACK_STOP_AND_START);
        mbOneFlag = false;
    }

    if (mbStartFlag == false)
    {
        // 攻撃フラグが有効時の処理
        if (mbAttackFlag)
        {

            // 攻撃フラグが全て有効でないならスタートを有効にする
            if (!mbAttackStartFlag && !mbAttackMiddleFlag && !mbAttackEndFlag)
            {
                mbAttackStartFlag = true;

                // アニメーション再生が終わる時間を記録
                mnAttackFlagChangeTime = (mpTimeManager->GetGameTime() + (GetAnimationTimeFrame(GetIndexNumber("AttackStart")) * mpTimeManager->GetOneFrame()));

                // 攻撃が開始するときのサウンド
                Set3DSound(SOUND_3D::ROBOT_ATTACK_STOP_AND_START);
            }

            // 攻撃スタートアニメーションが終了したら攻撃中フラグを有効化
            if (mbAttackStartFlag)
            {
                if (mnAttackFlagChangeTime <= mpTimeManager->GetGameTime())
                {
                    mbAttackStartFlag = false;
                    mbAttackMiddleFlag = true;

                    // アニメーション再生が終わる時間を記録
                    mnAttackFlagChangeTime = (mpTimeManager->GetGameTime() + ((GetAnimationTimeFrame(GetIndexNumber("AttackMiddle")) * mpTimeManager->GetOneFrame()) * 10 ));  // ここ変更予定
                }
            }

            // 攻撃中フラグを有効にしてから一定時間経ったらアタックエンドフラグ有効か
            if (mbAttackMiddleFlag)
            {
                if (mnAttackFlagChangeTime <= mpTimeManager->GetGameTime())
                {
                    mbAttackMiddleFlag = false;
                    mbAttackEndFlag = true;

                    // アニメーション再生が終わる時間を記録
                    mnAttackFlagChangeTime = (mpTimeManager->GetGameTime() + (GetAnimationTimeFrame(GetIndexNumber("AttackEnd")) * mpTimeManager->GetOneFrame()));

                    // 攻撃が終了するときのサウンド
                    Set3DSound(SOUND_3D::ROBOT_ATTACK_STOP_AND_START);
                }
            }

            // 攻撃エンドアニメーションが終了したら攻撃フラグを無効化する
            if (mbAttackEndFlag)
            {
                if (mnAttackFlagChangeTime <= mpTimeManager->GetGameTime())
                {
                    mbAttackEndFlag = false;
                    mbAttackFlag = false;

                    mpCharacter->SetInvincibleFlag(false);
                }
            }
        }

        // 攻撃フラグが有効で移動中なら移動モーションを無効化
        if (mbMoveFlag && mbAttackFlag)
        {
            mbMoveFlag = false;
        }
        else if (mbMoveFlag) {
            // 歩く時のサウンドを再生
            if (mnNextWalkSoundTime <= mpTimeManager->GetGameTime()) {
                mnNextWalkSoundTime = (mpTimeManager->GetGameTime() + ((GetAnimationTimeFrame(GetIndexNumber("Move")) * mpTimeManager->GetOneFrame())));
                Set3DSound(SOUND_3D::ROBOT_Walk);
            }
        }

        if (mbEndFlag)
        {
            SetAllFlag(false);
            mbEndFlag = true;

            if (mnEndTime <= mpTimeManager->GetGameTime())
            {
                *mpCharacterEndFlag = true;
            }
        }

    }
 
    if (!GetAllFlag()) {
        if (mnRelaxedTime <= mpTimeManager->GetGameTime())
        {
            // 休憩モーション有効化
            mbRelaxedFlag = true;
            mnRelaxedTime = (mpTimeManager->GetGameTime() + ((GetAnimationTimeFrame(GetIndexNumber("Relaxed")) * mpTimeManager->GetOneFrame()) * 2));
        }
    }
    else {

        mbRelaxedFlag = false;
        if (!GetAllFlag())
        {
            if (mnRelaxedTime > mpTimeManager->GetGameTime())
            {
                // 休憩モーション有効化
                mbRelaxedFlag = true;
            }
            else {
                // 休憩までの時間を設定
                mnRelaxedTime = (mpTimeManager->GetGameTime() + (mpTimeManager->GetOneFrame() * mnSetRelaxedTime));
            }
        }
        else {
            // 休憩までの時間を設定
            mnRelaxedTime = (mpTimeManager->GetGameTime() + (mpTimeManager->GetOneFrame() * mnSetRelaxedTime));
        }
    }
}

/*
* @fn GetPlusAllFlag
* @drief 追加したフラグがfalseかどうか返す(一つでもtrueがあればtrueを返す)
*/
bool MotionRobotSphere::GetPlusAllFlag()
{
    bool flag = false;

    flag |= mbStartFlag;

    flag |= mbRelaxedFlag;

    flag |= mbAttackStartFlag;
    flag |= mbAttackMiddleFlag;
    flag |= mbAttackEndFlag;

    return flag;
}

/*
* @fn GetIndexNumber
* @drief インデックスナンバーを行動名で取得
*/
int MotionRobotSphere::GetIndexNumber(const char *AnimName)
{
    int set = 0;

    if (GetNotOneAnimFlag())
    {
        if (AnimName == "Start") { return set; }
        else { set += 1; }

        if (AnimName == "Neutral") { return set; }
        else { set += 1; }

        if (AnimName == "Relaxed") { return set; }
        else { set += 1; }

        if (AnimName == "Move") { return set; }
        else { set += 1; }

        if (AnimName == "AttackStart") { return set; }
        else { set += 1; }

        if (AnimName == "AttackMiddle") { return set; }
        else { set += 1; }

        if (AnimName == "AttackEnd") { return set; }
        else { set += 1; }

        if (AnimName == "End") { return set; }
        else { set += 1; }
        
    }
    else {
        return GetIndexNumberTemplate(AnimName);
    }

    return -1;
}
/*
* @fn GetIndexNumberLookFlag
* @drief インデックスナンバーをフラグで取得
*/
int MotionRobotSphere::GetIndexNumberLookFlag()
{
    int set = 0;

    if (mbStartFlag) { return set; }
    else { set += 1; }

    if (!GetAllFlag()) { return set; }
    else { set += 1; }
    
    if (mbRelaxedFlag) { return set; }
    else { set += 1; }

    if (mbMoveFlag) { return set; }
    else { set += 1; }

    if (mbAttackStartFlag) { return set; }
    else { set += 1; }

    if (mbAttackMiddleFlag) { return set; }
    else { set += 1; }

    if (mbAttackEndFlag) { return set; }
    else { set += 1; }

    if (mbEndFlag) { return set; }
    else { set += 1; }

    return -1;
}

/*
* @fn LoopCheck
* @drief ループチェック用
*/
bool MotionRobotSphere::LoopCheck(int index)
{
    switch (index)
    {
    case 0: // スタート
        return false;
    case 1: // 立った状態(基本)
        return true;
    case 2: // 操作がない時の休憩モーション
        return true;
    case 3: // 移動
        return true;
    case 4: // 攻撃開始
        return false;
    case 5: // 攻撃中
        return true;
    case 6: // 攻撃終了
        return false;
    case 7: // 倒された時
        return false;
    }

    return true;
}

/*
* @fn SetMultiAnimFrame
* @drief アニメーションフレーム固定用 複数
*/
void MotionRobotSphere::SetMultiAnimFrame()
{
}

/*
* @fn SetOneAnimFrame
* @drief アニメーションフレーム固定用 一つ
*/
void MotionRobotSphere::SetOneAnimFrame()
{
    // アニメーションで移動をしているフレームの番号を検索する
    int moveAnimFrameIndex = MV1SearchFrame(mnModelHandle, "root");

    // アニメーションで移動しているフレームを無効にする
    MV1SetFrameUserLocalMatrix(mnModelHandle, moveAnimFrameIndex, MV1GetFrameLocalMatrix(mnModelHandle, moveAnimFrameIndex));
}

/*
* @fn SetMotionEnd
* @drief モーション終了モーションスタート
*/
void MotionRobotSphere::SetMotionEnd(bool *endFlag)
{
    if (!mbEndFlag) {
        // キャラクターのエンドフラグポインタ保存
        mpCharacterEndFlag = endFlag;

        // アニメーション再生が終わる時間を記録
        mnEndTime = (mpTimeManager->GetGameTime() + (GetAnimationTimeFrame(GetIndexNumber("End")) * mpTimeManager->GetOneFrame()));

        // エンドアニメーションフラグ有効化
        mbEndFlag = true;
    }
}

/*
* @fn SetPlusAllFlag
* @drief 追加した全フラグ設定
*/
void MotionRobotSphere::SetPlusAllFlag(bool flag)
{
    mbStartFlag = flag;

    mbAttackStartFlag = flag;
    mbAttackMiddleFlag = flag;
    mbAttackEndFlag = flag;
}

/*
* @fn GetPlusStopMoveMotionFlag
* @drief キャラクターの移動処理をストップする子クラスで追加されたフラグならtrueを返す
*/
bool MotionRobotSphere::GetPlusStopMoveMotionFlag()
{
    bool flag = false;

    flag |= mbStartFlag;

    return flag;
}

/*
* @fn StopMoveProcess
* @drief キャラクターの移動処理の代わりの処理をする
*/
VECTOR  MotionRobotSphere::StopMoveProcess()
{
    VECTOR setMoveVec = VGet(0.0f, 0.0f, 0.0f);

    if (mbStartFlag)
    {
        // 何もしない
    }

    if (mbAttackFlag)   // 調整
    {
        if (mbAttackMiddleFlag)
        {
            // 攻撃中 移動            
            setMoveVec = VScale(mvAnglePostion, mpCharacter->GetStatus().speed * 10);

            if (mbAttackReflectionFlag) {
                VECTOR setVec = Master::mpGameManager->GetObjectManager()->FixedObjectHitCheck(VAdd(mpCharacter->GetObjectPosition(), setMoveVec), mpCharacter->GetObjectPosition(), setMoveVec, mpCharacter->GetStatus().size);
                if ((setVec.x != 0.0f) || (setVec.z != 0.0f)) {
                    if (setVec.x != 0.0f) {
                        mvAnglePostion.x = -mvAnglePostion.x;
                    }
                    if (setVec.z != 0.0f) {
                        mvAnglePostion.z = -mvAnglePostion.z;
                    }
                    float setAngle = atan2f(mvAnglePostion.x, -mvAnglePostion.z);
                    mpCharacter->SetObjectAngle((setAngle + (DX_PI_F)) * (180.0f / DX_PI_F));
                }
            }
        }
    }

    if (mbEndFlag)
    {
        // 何もしない
    }

    return setMoveVec;
}

/*
* @fn SetMotionAttackObject
* @drief モーションに設定されている攻撃をする
*/
void MotionRobotSphere::SetMotionAttackObject()
{
    float setSurvivalTime = ((GetAnimationTimeFrame(GetIndexNumber("AttackMiddle")) * mpTimeManager->GetOneFrame()) * 2) + (GetAnimationTimeFrame(GetIndexNumber("AttackStart")) * mpTimeManager->GetOneFrame()) + (GetAnimationTimeFrame(GetIndexNumber("AttackEnd")) * mpTimeManager->GetOneFrame());

    Attack_Rolling *attackRolling = new Attack_Rolling(mpCharacter, mpCharacter->GetStatus().attackPower, setSurvivalTime, mpCharacter->GetStatus().size, mpCharacter->GetObjectPositionPointer());

    mpCharacter->SetInvincibleFlag(true);
}

/*
* @fn GetPlusStopAttackFlag
* @drief キャラクターの攻撃処理をストップする追加したフラグが有効ならtrueを返す
*/
bool MotionRobotSphere::GetPlusStopAttackFlag()
{
    bool flag = false;

    flag |= mbStartFlag;

    return flag;
}

/*
* @fn StopAttackProcess
* @drief キャラクターの攻撃処理の代わりの処理をする
*/
void MotionRobotSphere::StopAttackProcess()
{
    if (mbStartFlag)
    {
        // 何もしない
    }

    if (mbAttackFlag)
    {
        // 何もしない
    }

    if (mbEndFlag)
    {
        // 何もしない
    }    
}
/*
* @fn GetAttackTime
* @drief 攻撃時間を求める
*/
int MotionRobotSphere::GetAttackTime()
{
    return ((GetAnimationTimeFrame(GetIndexNumber("AttackMiddle")) * mpTimeManager->GetOneFrame()) * 2) + 
            (GetAnimationTimeFrame(GetIndexNumber("AttackStart")) * mpTimeManager->GetOneFrame()) + 
            (GetAnimationTimeFrame(GetIndexNumber("AttackEnd")) * mpTimeManager->GetOneFrame()); 
}

/*
* @fn AttackHitSound
* @drief 攻撃が当たった時のサウンド
*/
void MotionRobotSphere::AttackHitSound()
{
    Set3DSound(SOUND_3D::ROBOT_ATTACK_HIT);
}

/*
* @fn FixedHitSound
* @drief 固定物に当たった時のサウンド
*/
void MotionRobotSphere::FixedHitSound()
{
    if (Master::mpGameManager->GetTimeManager()->GetGameTime() > mnNextFixedHitSoundTime) {
        Set3DSound((GetRand(1) == 0) ? SOUND_3D::ROBOT_FIXED_HIT_1 : SOUND_3D::ROBOT_FIXED_HIT_2);
        mnNextFixedHitSoundTime = (Master::mpGameManager->GetTimeManager()->GetGameTime() + (300));
    }
}

/*
* @fn HpZeroSound
* @drief HPがゼロになった時のサウンド
*/
void MotionRobotSphere::HpZeroSound()
{
    Set3DSound(SOUND_3D::ROBOT_ATTACK_STOP_AND_START);
}

/*
* @fn CangeAttackFlag
* @drief 攻撃フラグを変更する
*/
void MotionRobotSphere::CangeAttackFlag(int number) {
    if (number == 0) {
        mbAttackReflectionFlag = !mbAttackReflectionFlag;
    } 
}