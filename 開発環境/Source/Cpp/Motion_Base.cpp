#include "DxLib.h"
#include "../Header/Calculation.h"
#include "../Header/GameManager.h"
#include "../Header/ModelManager.h"
#include "../Header/Motion_Base.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
Motion_Base::Motion_Base(Object_Base_Character *character, const char *fileName, bool notOneAnimFlaga, bool endObjectFlag)
: mpCharacter(character)
, mcModelFileName(const_cast<char *>(fileName))
, mbMoveFlag(false)
, mnModelHandle(-1)
, mnAnimNumber1(-1)
, mnAnimNumber2(-1)
, mbNotOneAnimFlag(notOneAnimFlaga)
, mbLoopFlag1(false)
, mbLoopFlag2(false)
, mnAnimation1(-1)
, mnAnimation2(-1)
, mfAngle((character->GetObjectAngle() / 180.0f) * DX_PI_F)
, mfAnimBlendRate(0.0f)
, mfAnimCount1(0.0f)
, mfAnimCount2(0.0f)
, mbAttackFlag(false)
, mpCharacterEndFlag(nullptr)
, mbEndFlag(false)
, mnEndTime(0)
, mbEndObjectFlag(endObjectFlag)
, mnNextFixedHitSoundTime(0)
{
    // アングル設定
    mvAnglePostion.x = -(sinf((character->GetObjectAngle() / 180.0f) * DX_PI_F));
    mvAnglePostion.y = 0.0f;
    mvAnglePostion.z = cosf((character->GetObjectAngle() / 180.0f) * DX_PI_F);

    mpTimeManager = Master::mpGameManager->GetTimeManager();
}

/*
* @fn デストラクタ
*/
Motion_Base::~Motion_Base()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void Motion_Base::Initilize()
{
    // モデルの情報を取得する。
    mnModelHandle = Master::mpGameManager->GetModelManager()->GetModelNumber(mcModelFileName, true);

    MyInitilize();

    // アニメーション再生時間を初期化
    ChangeAnimation(GetIndexNumber("Neutral"));

    // アニメーションで移動しているフレームを無効にする
    if (mbNotOneAnimFlag) {
        SetMultiAnimFrame();
    }
    else
    {
        SetOneAnimFrame();
    }

    // モデルの初期位置を設定する。
    MV1SetPosition(mnModelHandle, VGet(0.0f, 0.0f, 0.0f));
}

/*
* @fn Update
* @drief 更新
*/
void Motion_Base::Update()
{
    // データを整理
    SetDataSort();

    // アニメーション変更　(変わってなければ関数内で何もしてない)
    ChangeAnimation(GetIndexNumberLookFlag());

    // アニメーションを再生
    PlayAnimation();

    // モデルアングルを設定
    SetAngleProcess();

    // モデル位置を設定
    SetPosition(mpCharacter->GetObjectPosition());

    // 個別アップデート
    MyUpdata();
}

/*
* @fn Draw
* @drief 描画
*/
void Motion_Base::Draw()
{
    MyDraw();
    if (mnModelHandle != -1) {
//        DrawFormatString(0, 240, GetColor(0, 255, 255), "mfAngle : %f", mfAngle);
        // モデル描画
        if (!(mpCharacter->GetHpMinusInvincibleFlag())) {
            MV1DrawModel(mnModelHandle);
        }
        else {
            if (((Master::mpGameManager->GetTimeManager()->GetGameTime() / Master::mpGameManager->GetTimeManager()->GetOneFrame()) % 2) == 0) {
                MV1DrawModel(mnModelHandle);
            }
        }

//        DrawFormatString(0, 180, GetColor(0, 255, 255), "animNumber:%d", mnAnimNumber1);
    }
}

/*
* @fn Finalize
* @drief 終了処理
*/
void Motion_Base::Finalize()
{
    MyFinalize();

    MV1DeleteModel(mnModelHandle);
    for (int i = 0; i < mnAnimHandle.size(); i++)
    {
        MV1DeleteModel(mnAnimHandle[i]);
    }
    mnAnimHandle.clear();
}

/*
* @fn AddAnim
* @drief アニメーション追加
*/
void Motion_Base::AddAnim(const char *fileName)
{
    mcAnimFileName.push_back(const_cast<char *>(fileName));
    
    int setAnimHandle = Master::mpGameManager->GetModelManager()->GetModelNumber(fileName, true);
    mnAnimHandle.push_back(setAnimHandle);
}

/*
* @fn ReSetFlag
* @drief フラグをリセットする
*/
void Motion_Base::ReSetFlag()
{
    mbMoveFlag = false;

    // 追加されたフラグをリセット
    ReSetPlusFlag();
}

/*
* @fn SetDataSort
* @drief データを整理する
*/
void Motion_Base::SetDataSort()
{
    // 追加されたデータを整理
    SetPlusDataSort();
}

/*
* @fn GetAllFlag
* @drief 全フラグがfalseかどうか返す(一つでもtrueがあればtrueを返す)
*/
bool Motion_Base::GetAllFlag()
{
    bool flag = false;

    flag |= mbMoveFlag;

    flag |= mbEndFlag;

    flag |= GetPlusAllFlag();

    return flag;
}

/*
* @fn 
* @drief 全フラグ設定
*/
void Motion_Base::SetAllFlag(bool flag)
{
    mbMoveFlag = flag;

    mbEndFlag = flag;

    SetPlusAllFlag(flag);
}


/*
* @fn 
* @drief インデックスナンバーを行動名で取得する関数のテンプレート
*/
int Motion_Base::GetIndexNumberTemplate(const char *AnimName)
{
    int set = 0;

    if (AnimName == "Neutral") { return set; }
    else { set += 1; }

    if (AnimName == "Run") { return set; }
    else { set += 1; }

    if (AnimName == "JumpIn") { return set; }
    else { set += 1; }

    if (AnimName == "JumpLoop") { return set; }
    else { set += 1; }

    if (AnimName == "JumpOut") { return set; }
    else { set += 1; }

    if (AnimName == "Attack1") { return set; }
    else { set += 1; }

    return -1;
}

/*
* @fn ChangeAnimation
* @drief アニメーション切り替え処理
*/
void Motion_Base::ChangeAnimation(int index)
{
    if (index == -1) {
        return;
    }
    if (mnModelHandle != -1) {
        if (index != mnAnimNumber1)
        {
            // 前のアニメーションナンバーを保持
            mnAnimNumber2 = mnAnimNumber1;
            // 現在のアニメーションナンバーを保持
            mnAnimNumber1 = index;

            // 再生中のアニメーション2が有効状態だったらデタッチしておく
            if (mnAnimation2 != (-1))
            {

                MV1DetachAnim(mnModelHandle, mnAnimation2);
                mnAnimation2 = -1;
            }

            // 今まで再生されていた情報を2の方に保持しておく
            mnAnimation2 = mnAnimation1;
            mfAnimCount2 = mfAnimCount1;
            mbLoopFlag2 = mbLoopFlag1;

            // 新しいアニメーションアタッチして、アタッチ番号を保持しておく
            if (!mbNotOneAnimFlag) {
                mnAnimation1 = MV1AttachAnim(mnModelHandle, index);
            }
            else {
                mnAnimation1 = MV1AttachAnim(mnModelHandle, 0, mnAnimHandle[mnAnimNumber1], FALSE);/*フレーム名が違くてもアタッチするようにしてる*/
            }
            mfAnimCount1 = 0.0f;

            // 新しいアニメーションがループするかどうか
            mbLoopFlag1 = LoopCheck(index);

            // ブレンド率の初期値を設定
            // note: アニメーション2が有効でない場合はブレンドさせないので1.0にしておく  
            mfAnimBlendRate = (mnAnimation2 == -1 ? 1.0f : 0.0f);
        }
    }
}

/*
* @fn PlayAnimation
* @drief アニメーション処理
*/
void Motion_Base::PlayAnimation()
{
    if (mnModelHandle != -1) {

        // ブレンド率を加算していく
        if (mfAnimBlendRate < 1.0f)
        {
            mfAnimBlendRate += CHARA_ANIM_BLEND_SPEED;

            if (mfAnimBlendRate > 1.0f)
            {
                mfAnimBlendRate = 1.0f;
            }
        }
        float fAnimTotalTime;

        // アニメーション1の処理
        if (mnAnimation1 != -1)
        {
            // 総再生時間を取得
            fAnimTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, mnAnimation1);
            
            // 再生時間を進める
            mfAnimCount1 += CHARA_PLAY_ANIM_SPEED;

            // ループさせる
            if (mfAnimCount1 >= fAnimTotalTime && mbLoopFlag1)
            {
                ///
                mfAnimCount1 = fmodf(mfAnimCount1, fAnimTotalTime);
                ///
            }
            else if (mfAnimCount1 >= fAnimTotalTime && !mbLoopFlag1)
            {
                mfAnimCount1 = fAnimTotalTime;
            }

            // モデルに反映
            MV1SetAttachAnimTime(mnModelHandle, mnAnimation1, mfAnimCount1);

            // アニメーション反映率を設定
            MV1SetAttachAnimBlendRate(mnModelHandle, mnAnimation1, mfAnimBlendRate);
        }

        
        // アニメーション2の処理
        if (mnAnimation2 != -1)
        {
            // 総再生時間を取得
            fAnimTotalTime = MV1GetAnimTotalTime(mnModelHandle, mnAnimation2);

            // 再生時間を進める
            mfAnimCount2 += CHARA_PLAY_ANIM_SPEED;

            // ループさせる
            if (mfAnimCount2 >= fAnimTotalTime && mbLoopFlag2)
            {
                ///
                mfAnimCount2 = fmodf(mfAnimCount2, fAnimTotalTime);
                ///
            }
            else if (mfAnimCount2 >= fAnimTotalTime && !mbLoopFlag2)
            {
                mfAnimCount2 -= CHARA_PLAY_ANIM_SPEED;
            }


            // モデルに反映
            MV1SetAttachAnimTime(mnModelHandle, mnAnimation2, mfAnimCount2);

            // アニメーション反映率を設定
            MV1SetAttachAnimBlendRate(mnModelHandle, mnAnimation2, 1.0f - mfAnimBlendRate);
        }
    }
}

/*
* @fn SetAngleProcess
* @drief モデルアングル設定処理
*/
void Motion_Base::SetAngleProcess()
{
    float targetAngle;
    float diffAngle;

    targetAngle = atan2f(mvAnglePostion.x, mvAnglePostion.z);

    diffAngle = targetAngle - mfAngle;

    // ある方向からある方向の差が180度以上になることはないので
    // 差の値が180度以上になっていたら修正する
    /*if (diffAngle < -DX_PI_F)
    {
        diffAngle += DX_TWO_PI_F;
    }
    else if (diffAngle > DX_PI_F)
    {
        diffAngle -= DX_TWO_PI_F;
    }*/
    diffAngle = Calculation::GetNotExceedAngle(diffAngle);

    // 角度の差を0に近づけていく
    if (diffAngle > 0.0f)
    {
        diffAngle -= 0.2f;
        if (diffAngle < 0.0f)
        {
            diffAngle = 0.0f;
        }
    }
    else
    {
        diffAngle += 0.2f;
        if (diffAngle > 0.0f)
        {
            diffAngle = 0.0f;
        }
    }

    // 新しい角度計算
    mfAngle = targetAngle - diffAngle;

    // アングルセット
    MV1SetRotationXYZ(mnModelHandle, VGet(0.0f, mfAngle + DX_PI_F, 0.0f));
}

/*
* @fn GetAnimationTimeFrame
* @drief アニメーションの再生時間を取得する
*/
int Motion_Base::GetAnimationTimeFrame(int number)
{
    int attachIndex;
    if (mbNotOneAnimFlag) {
        attachIndex = MV1AttachAnim(mnModelHandle, 0, mnAnimHandle[number], FALSE);
    }
    else {
        attachIndex = MV1AttachAnim(mnModelHandle, number);
    }
    int animFrame = (MV1GetAttachAnimTotalTime(mnModelHandle, attachIndex) / CHARA_PLAY_ANIM_SPEED);

    MV1DetachAnim(mnModelHandle, attachIndex);
    
    return animFrame;
}

/*
* @fn GetStopMoveMotionFlag
* @drief キャラクターの移動処理をストップするモーションならtrueを返す
*/
bool  Motion_Base::GetStopMoveMotionFlag()
{
    bool flag = false;


    flag |= mbAttackFlag;

    flag |= mbEndFlag;

    // 追加されたフラグの中で止めるもの
    flag |= GetPlusStopMoveMotionFlag();

    return flag;
}

/*
* @fn GetStopAttackFlag
* @drief キャラクターの攻撃処理をストップするフラグが有効であればtrueを返す
*/
bool Motion_Base::GetStopAttackFlag()
{
    bool flag = false;


    flag |= mbAttackFlag;

    flag |= mbEndFlag;

    // 追加されたフラグの中で止めるもの
    flag |= GetPlusStopAttackFlag();

    return flag;
}