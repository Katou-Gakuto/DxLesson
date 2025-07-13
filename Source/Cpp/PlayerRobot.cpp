#include <cmath>
#include "DxLib.h"
#include "../Header/Camera.h"
//#include "../Header/Attack_CloseRange.h"
#include "../Header/GameManager.h"
#include "../Header/MotionRobotSphere.h"
#include "../Header/ObjectManager.h"
#include "../Header/ObjectTagMacro.h"
#include "../Header/Operation.h"
#include "../Header/PlayerRobot.h"
#include "../Header/Player_Base.h"
#include "../Header/SceneManager.h"
#include "../Header/Scene_Enum.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
PlayerRobot::PlayerRobot(Camera *camera, STATUS status, VECTOR position, float angle, std::string name, std::string dataFileName)
: Player_Base(camera, status, position, angle, name, dataFileName, 1020)
, mbReflectionAttackFlag(false)
, mnNextChengeTime(0)
{
}

/*
* @fn デストラクタ
*/
PlayerRobot::~PlayerRobot()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void PlayerRobot::MyInitilize()
{
    if (msStatus.level >= 50) {
        mpMotion = new MotionRobotSphere(this, 3000, false, true);
        mpMotion->Initilize();
        mbReflectionAttackFlag = true;
    }
    else {
        mpMotion = new MotionRobotSphere(this, 3000);
        mpMotion->Initilize();
    }
}

/*
* @fn Update
* @drief 更新
*/
void PlayerRobot::MyUpdate()
{
    // HPチェック
    CheckHp_Invincible();

    // 移動系
    MoveProcess();

    // 攻撃
    AttackProcess();

    if (mbReflectionAttackFlag && (mnNextChengeTime <= Master::mpGameManager->GetTimeManager()->GetGameTime()) && Operation::CheckYKey()) {
        mpMotion->CangeAttackFlag(0);
        mnNextChengeTime = (Master::mpGameManager->GetTimeManager()->GetGameTime() + 1700);
    }
}

/*
* @fn Draw
* @drief 描画
*/
void PlayerRobot::MyDraw()
{
    //DrawSphere3D(mvObjectPosition, msStatus.size, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
    /*DrawFormatString(0, 0, GetColor(255, 0, 0), "x:%f y:%f  z:%f", mvObjectPosition.x, mvObjectPosition.y, mvObjectPosition.z);
    DrawFormatString(0, 60, GetColor(255, 0, 0), "x:%f y:%f  z:%f", mpCanera->GetPosition().x, mpCanera->GetPosition().y, mpCanera->GetPosition().z);
    DrawFormatString(0, 80, GetColor(255, 0, 0), "x:%f y:%f  z:%f", mpCanera->GetLookAtPosition().x, mpCanera->GetLookAtPosition().y, mpCanera->GetLookAtPosition().z);*/
    //DrawFormatString(0, 140, GetColor(255, 0, 0), "hp:%d", msStatus.hp);
}

/*
* @fn Finalize
* @drief 終了処理
*/
void PlayerRobot::MyFinailize()
{
}

/*
* @fn GenerationAttackObject
* @drief 攻撃オブジェクト生成
*/
void PlayerRobot::GenerationAttackObject()
{
    SetMotionAttack();

    //Attack_CloseRange *playerAttack = new Attack_CloseRange(this, msStatus.attackPower, 1003, VAdd(mvObjectPosition, mvMoveVec), 120.0f);
    //playerAttack->Initilize();
}