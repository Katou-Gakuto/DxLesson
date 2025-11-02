#include <cmath>

#include "../Header/Camera.h"
#include "../Header/CoordinateXY.h"
#include "../Header/GameManager.h"
#include "../Header/MenuPlay.h"
#include "../Header/Motion_Base.h"
#include "../Header/ObjectManager.h"
#include "../Header/ObjectTagMacro.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/Operation.h"
#include "../Header/Player_Base.h"
#include "../Header/SceneManager.h"
#include "../Header/Scene_Enum.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
Player_Base::Player_Base(Camera *camera, STATUS status, VECTOR position, float angle, std::string name, std::string dataFileName, int attackInterval)
: Object_Base_Character(status, angle, name, dataFileName)
, mpCanera(camera)
, mvMoveVec(VGet(0.0f, 0.0f, 0.0f))
, mvFrontVec(VGet(0.0f, 0.0f, 0.0f))
, mvRightVec(VGet(0.0f, 0.0f, 0.0f))
, mvSetMoveVec(VGet(0.0f, 0.0f, 0.0f))
, mbFrontMoveFlag(false)
, mbBackMoveFlag(false)
, mbRightMoveFlag(false)
, mbLeftMoveFlag(false)
, mnAttackTime(0)
, mnAttackInterval(attackInterval)
, mnDrawPlayerStatusSizeHandle(-1)
{
    mvObjectPosition = position;
}

/*
* @fn デストラクタ
*/
Player_Base::~Player_Base()
{
}


/*
* @fn Initilize
* @drief 初期化
*/
void Player_Base::Initilize()
{
    SetTag(PLAYER_TAG);

    mnAttackTime = Master::mpGameManager->GetTimeManager()->GetGameTime();

    { // 文字サイズハンドル設定
        mnDrawPlayerStatusSizeHandle = CreateFontToHandle(NULL, 30, 25, DX_FONTTYPE_EDGE);
    }

    MyInitilize();
}

/*
* @fn Update
* @drief 更新
*/
void Player_Base::Update()
{
    // 時間停止フラグが有効なら更新しない
    if (Master::mpGameManager->GetTimeManager()->GetStopFlag()) {
        return;
    }

    // 終了するかどうかフラグを取得
    EndProcess();
    
    // モーションフラグを初期化
    mpMotion->ReSetFlag();

    // 個別更新処理
    MyUpdate();

    // 攻撃に当たったか
    Master::mpGameManager->GetObjectManager()->AllAttackObjectHitCheck(this);
    
    // モーション更新
    mpMotion->Update();
    //mpMotion->SetPosition(mvObjectPosition);

    if (Operation::CheckXKey()) {
        // メニュー画面
        MenuPlay* menuPlay = new MenuPlay(this);
        menuPlay->Initilize();

        mnAttackTime = Master::mpGameManager->GetTimeManager()->GetGameTime();
    }
}

/*
* @fn Draw
* @drief 描画
*/
void Player_Base::Draw()
{
    mpMotion->Draw();

    // 画面サイズ取得
    COORDINATE_X_Y_INT set = XYGet_Int(0, 0);
    int colorBit = 0;
    GetScreenState(&set.x, &set.y, &colorBit);

    // HP
    {
        DrawBoxAA((set.x / 10) * 0, (set.y / 10) * 0.1,
                  (set.x / 10) * 6, (set.y / 10) * 1,
            GetColor(150, 150, 150), TRUE);

        DrawBoxAA((set.x / 10) * 0.8, (set.y / 10) * 0.2,
                  (set.x / 10) * 5.9, (set.y / 10) * 0.9,
            GetColor(0, 0, 0), TRUE);
        
        DrawBoxAA((set.x / 10) * 0.8, (set.y / 10) * 0.2,
                  (set.x / 10) * (0.8 + (5.1 * (static_cast<float>(msStatus.hp) / static_cast<float>(msStatus.maxHp)))), (set.y / 10) * 0.9,
            GetHpColor(), TRUE);

        DrawStringToHandle((set.x / 10) * 0.1, (set.y / 10) * 0.2, "HP", GetColor(255, 255, 255), mnDrawPlayerStatusSizeHandle);
    }

    //DrawFormatStringToHandle(0, 0, GetColor(0, 0, 0), mnDrawPlayerStatusSizeHandle, "%s\nLv%d\n", mstrName.c_str(), msStatus.level);

    MyDraw();
    /*DrawSphere3D(mvObjectPosition, msStatus.size, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
    /*DrawFormatString(0, 0, GetColor(255, 0, 0), "x:%f y:%f  z:%f", mvObjectPosition.x, mvObjectPosition.y, mvObjectPosition.z);
    DrawFormatString(0, 60, GetColor(255, 0, 0), "x:%f y:%f  z:%f", mpCanera->GetPosition().x, mpCanera->GetPosition().y, mpCanera->GetPosition().z);
    DrawFormatString(0, 80, GetColor(255, 0, 0), "x:%f y:%f  z:%f", mpCanera->GetLookAtPosition().x, mpCanera->GetLookAtPosition().y, mpCanera->GetLookAtPosition().z);*/
    //DrawFormatString(0, 140, GetColor(255, 0, 0), "hp:%d", msStatus.hp);
}

/*
* @fn Finalize
* @drief 終了処理
*/
void Player_Base::MyFinailize()
{
    DeleteFontToHandle(mnDrawPlayerStatusSizeHandle);
}

/*
* @fn HpZeroMove
* @drief HPが0以下時の処理
*/
void Player_Base::HpZeroMove()
{
    mpMotion->SetMotionEnd(&mbMotionEndFlag);
    // ゲームオーバー画面移動
    //Master::mpGameManager->GetSceneManager()->SetNextScene(SCENE::GAME_OVER);
}

/*
* @fn SetVec
* @drief 移動方向ベクトル設定
*/
void Player_Base::SetVec()
{
    mvMoveVec = VGet(0.0f, 0.0f, 0.0f);

    float denominator = std::fabs(mpCanera->GetDirection().x) + std::fabs(mpCanera->GetDirection().z);//std::abs(mvObjectPosition.x - mpCanera->GetPosition().x) + std::abs(mvObjectPosition.z - mpCanera->GetPosition().z);
    mvFrontVec = VGet((mpCanera->GetDirection().x / denominator) * msStatus.speed, 0.0f, (mpCanera->GetDirection().z / denominator) * msStatus.speed);

    mvRightVec = VGet(mvFrontVec.z, 0.0f, -mvFrontVec.x);

    mbFrontMoveFlag = false;
    mbBackMoveFlag = false;
    mbRightMoveFlag = false;
    mbLeftMoveFlag = false;
}

/*
* @fn SetCamera
* @drief カメラをこのオブジェクトを見るようにする
*/
void Player_Base::SetCamera()
{
    Master::mpCamera->InitializeModeTargetLRMove(this);
}

/*
* @fn GoMove
* @drief 移動処理
*/
void Player_Base::GoMove()
{
    if (!mpMotion->GetStopMoveMotionFlag())
    {
        if (mbFrontMoveFlag) {
            mvMoveVec = VGet(mvFrontVec.x + mvMoveVec.x, 0.0f, mvFrontVec.z + mvMoveVec.z);
        }
        if (mbBackMoveFlag) {
            mvMoveVec = VGet(-mvFrontVec.x + mvMoveVec.x, 0.0f, -mvFrontVec.z + mvMoveVec.z);
        }
        if (mbRightMoveFlag) {
            mvMoveVec = VGet(mvRightVec.x + mvMoveVec.x, 0.0f, mvRightVec.z + mvMoveVec.z);
        }
        if (mbLeftMoveFlag) {
            mvMoveVec = VGet(-mvRightVec.x + mvMoveVec.x, 0.0f, -mvRightVec.z + mvMoveVec.z);
        }
        if (mbFrontMoveFlag || mbBackMoveFlag || mbRightMoveFlag || mbLeftMoveFlag) {

            bool moveFlag = true;

            // 動いていない場合false
            if ((mbFrontMoveFlag && mbBackMoveFlag) && !(mbRightMoveFlag || mbLeftMoveFlag)) { moveFlag = false; }
            if (!(mbFrontMoveFlag || mbBackMoveFlag) && (mbRightMoveFlag && mbLeftMoveFlag)) { moveFlag = false; }
            if (mbFrontMoveFlag && mbBackMoveFlag && mbRightMoveFlag && mbLeftMoveFlag) { moveFlag = false; }

            if (moveFlag) {
                float setAngle = atan2f(mvMoveVec.x, -mvMoveVec.z);
                mfAngle = (setAngle + (DX_PI_F)) * (180.0f / DX_PI_F);//((setAngle < 0) ? (setAngle + (DX_PI_F * 2.0f)) * (180.0f / DX_PI_F) : (setAngle) * (180.0f / DX_PI_F));
                mpMotion->SetMoveFlag(true);
                mpMotion->SetAnglePosition(mvMoveVec);
            }
        }
    }
    else
    {
        mvMoveVec = mpMotion->StopMoveProcess();
    }

    VECTOR  fixedMove = Master::mpGameManager->GetObjectManager()->FixedObjectHitCheck(VAdd(mvObjectPosition, mvMoveVec), mvObjectPosition, mvMoveVec, msStatus.size);
    mvMoveVec = VAdd(fixedMove, mvMoveVec);
    if ((fixedMove.x != 0.0f) || (fixedMove.z != 0.0f)) {
        mpMotion->FixedHitSound();
    }

    /*if (mbFrontMoveFlag ||
        mbBackMoveFlag  ||
        mbRightMoveFlag ||
        mbLeftMoveFlag)
    {
        mvSetMoveVec = mvMoveVec;
    }*/

    mvObjectPosition = VAdd(mvMoveVec, mvObjectPosition);

}

/*
* @fn GetKey_SetMoveFlag
* @drief キー状況によって移動フラグを設定する
*/
void Player_Base::GetKey_SetMoveFlag()
{
    if (Operation::CheckUpKey()) {
        mbFrontMoveFlag = true;
    }
    if (Operation::CheckDownKey()) {
        mbBackMoveFlag = true;
    }
    if (Operation::CheckRightKey()) {
        mbRightMoveFlag = true;
    }
    if (Operation::CheckLeftKey()) {
        mbLeftMoveFlag = true;
    }
}

/*
* @fn MoveProcess
* @drief 移動全処理をひとまとめにした物
*/
void Player_Base::MoveProcess()
{
    SetVec();
    GetKey_SetMoveFlag();
    GoMove();
}

/*
* @fn AttackProcess
* @drief 攻撃処理
*/
void Player_Base::AttackProcess()
{
    if (Operation::CheckAKey()) {
        if (!mpMotion->GetStopAttackFlag()) {
            if (((mnAttackTime + mnAttackInterval) < Master::mpGameManager->GetTimeManager()->GetGameTime()) && !mpMotion->GetAttackFlag()) {
                mnAttackTime = Master::mpGameManager->GetTimeManager()->GetGameTime();


                // 攻撃オブジェクト生成
                GenerationAttackObject();
            }
        }
        else {
            // 攻撃の処理の代わりの処理
            mpMotion->StopAttackProcess();
        }
    }
}

/*
* @fn EndProcess
* @drief 終了処理
*/
void Player_Base::EndProcess()
{
    if (mbMotionEndFlag) {
        // ゲームオーバー画面移動
        Master::mpGameManager->GetSceneManager()->SetNextScene(SCENE::GAME_OVER);
    }
}