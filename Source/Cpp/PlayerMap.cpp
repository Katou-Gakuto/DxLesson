#include <iostream>
#include <string>

#include "DxLib.h"
#include "../Header/Camera.h"
#include "../Header/DataManager.h"
#include "../Header/GameManager.h"
#include "../Header/MotionRobotSphere.h"
#include "../Header/PlayerMap.h"
#include "../Header/Player_Base.h"
#include "../Header/SceneManager.h"
#include "../Header/Status_Struct.h"

/*
* @fn コンストラクタ
*/
PlayerMap::PlayerMap(Camera *camera, STATUS status, VECTOR position, float angle, std::string name, std::string dataFileName)
: Player_Base(camera, status, position, angle, name, dataFileName, 0)
{
}

/*
* @fn デストラクタ
*/
PlayerMap::~PlayerMap()
{
}

/*
* @fn MyInitilize
* @drief 初期化
*/
void PlayerMap::MyInitilize()
{
    DataManager *dataManager = Master::mpGameManager->GetDataManager();
    SceneManager *sceneManager = Master::mpGameManager->GetSceneManager();

    switch ((CHARACTER_TYPE)dataManager->GetPlayPlayerData().characterData.templateData.typeNumber)
    {
    case CHARACTER_TYPE::ROBOT_PLAYER:
        mpMotion = new MotionRobotSphere(this, 3000);
        mpMotion->Initilize();
        break;
    }
}

/*
* @fn MyUpdate
* @drief 更新
*/
void PlayerMap::MyUpdate()
{
    // HPチェック
    CheckHp_Invincible();

    // 移動系
    MoveProcess();
}

/*
* @fn MyDraw
* @drief 描画
*/
void PlayerMap::MyDraw()
{
}

/*
* @fn MyFinailize
* @drief 終了処理
*/
void PlayerMap::MyFinailize()
{
}

/*
* @fn GenerationAttackObject
* @drief 攻撃オブジェクト生成
*/
void PlayerMap::GenerationAttackObject()
{
}