#include <cmath>
#include <vector>

#include "DxLib.h"
#include "../Header/Calculation.h"
#include "../Header/CharacterType_Enum.h"
#include "../Header/DataManager.h"
#include "../Header/Data_Structs.h"
#include "../Header/EnemyMap.h"
#include "../Header/GameManager.h"
#include "../Header/MotionRobotSphere.h"
#include "../Header/ObjectTagMacro.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/SceneManager.h"
#include "../Header/Scene_Enum.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
EnemyMap::EnemyMap(Object_Base_Character * player, VECTOR position, float angle, STATUS status, SCENE setScene, std::string name, std::string dataFileName, CHARACTER_TYPE enemyType, bool survivalFlag)
: Object_Base_Character(status, angle, name, dataFileName)
, mpPlayer(player)
, meSetScene(setScene)
, meEnemyType(enemyType)
{
    mvObjectPosition = position;

    mnSurvivalFlag = (survivalFlag == false ? 0 : 1);
}

/*
* @fn デストラクタ
*/
EnemyMap::~EnemyMap()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void EnemyMap::Initilize()
{
    SetTag(ENEMY_TAG);

    switch (meEnemyType)
    {
    case CHARACTER_TYPE::MAP_WEAK_ENEMY_1:
        mpMotion = new MotionRobotSphere(this, 3000, (mnSurvivalFlag == 0) ? true : false);
        mpMotion->Initilize();
        break;

    case CHARACTER_TYPE::MAP_BOSS_ENEMY_1:
        mpMotion = new MotionRobotSphere(this, 5000, (mnSurvivalFlag == 0) ? true : false);
        mpMotion->Initilize();
        break;
    }

    // データ削除処理
    if (mnSurvivalFlag == 0) {
        SetDeleteData();
    }
}

/*
* @fn Update
* @drief 更新
*/
void EnemyMap::Update()
{
    //mbEncounterFlag = false;
    if (mnSurvivalFlag == 0) {
        mpMotion->SetMotionEnd(&mbMotionEndFlag);
        mnSurvivalFlag = 2;
    }
    else if (mnSurvivalFlag == 2) {
        // モーションフラグを初期化
        mpMotion->ReSetFlag();

        // モーション更新
        mpMotion->Update();

        if (mbMotionEndFlag) {
            SetDeleteFlag(true);
        }
    }
    else if (mnSurvivalFlag == 1) {
        if (PlayerCheck() && meObjectScene != SCENE::EXCEPTION) {

            // 時間停止フラグが有効なら更新しない
            if (Master::mpGameManager->GetTimeManager()->GetStopFlag()) {
                return;
            }

            Master::mpGameManager->GetSceneManager()->SetNextScene(meSetScene);

            // 例外化
            meObjectScene = SCENE::EXCEPTION;
            
            // プレイヤーデータ入力
            if (mpPlayer != nullptr)
            {
                PLAYER_DATA playerData = Master::mpGameManager->GetDataManager()->GetPlayPlayerData();
                playerData.characterData.position = mpPlayer->GetObjectPosition();
                playerData.characterData.status = mpPlayer->GetStatus();
                playerData.characterData.angle = mpPlayer->GetObjectAngle();

                Master::mpGameManager->GetDataManager()->SetPlayPlayerData(playerData);
            }
        }
        else if (meObjectScene == SCENE::EXCEPTION) {
            switch (Master::mpGameManager->GetSceneManager()->GetNowScene())
            {
            case SCENE::BATTLE_RESULT:
            case SCENE::GAME_CLEAR:
                SetDeleteFlag(true);

                SetEnemyDataSurvivalFlag();
                break;

            case SCENE::GAME_OVER:
            case SCENE::GAME_NOTHING:
                SetDeleteFlag(true);
                break;

            default:
                break;
            }
        }
        else if (meObjectScene != SCENE::EXCEPTION) {
            // 時間停止フラグが有効なら更新しない
            if (Master::mpGameManager->GetTimeManager()->GetStopFlag()) {
                return;
            }
            // モーションフラグを初期化
            mpMotion->ReSetFlag();

            // 移動
            if (!mpMotion->GetStopMoveMotionFlag()) {
            }
            else {
                mpMotion->StopMoveProcess();
            }
            // 攻撃現在の時間
            if (!mpMotion->GetStopAttackFlag()) {
            }
            else {
                // 攻撃の処理の代わりの処理
                mpMotion->StopAttackProcess();
            }


            // モーション更新
            mpMotion->Update();
        }
    }
}

/*
* @fn Draw
* @drief 描画
*/
void EnemyMap::Draw()
{
    if (meObjectScene != SCENE::EXCEPTION) {


        //DrawSphere3D(mvObjectPosition, mfSearchRange - 100.0f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);

        mpMotion->Draw();

        DrawBillboard_Name_Level();

        /*if (mbEncounterFlag) {
            DrawString(0, 20, "true", GetColor(255, 0, 0));
        }
        DrawFormatString(0, 40, GetColor(255, 0, 0), "x:%f y:%f  z:%f", mvObjectPosition.x, mvObjectPosition.y, mvObjectPosition.z);
        */

        //DrawFormatString(0, 120, GetColor(255, 0, 0), "x:%f y:%f  z:%f", /*std::abs*/(mpPlayer->GetObjectPosition().x - mvObjectPosition.x), 0.0f, /*std::abs*/(mpPlayer->GetObjectPosition().z - mvObjectPosition.z));
        //DrawFormatString(0, 140, GetColor(255, 0, 0), "atn2:%f", std::atan2(/*std::abs*/(mpPlayer->GetObjectPosition().x - mvObjectPosition.x), /*std::abs*/(mpPlayer->GetObjectPosition().z - mvObjectPosition.z)));
        //DrawFormatString(0, 160, GetColor(255, 0, 0), "xPos:%f", (std::cos(std::atan2(/*std::abs*/(mpPlayer->GetObjectPosition().x - mvObjectPosition.x), /*std::abs*/(mpPlayer->GetObjectPosition().z - mvObjectPosition.z))) * /*std::abs*/(mpPlayer->GetObjectPosition().x - mvObjectPosition.x)) - (std::sin(std::atan2(/*std::abs*/(mpPlayer->GetObjectPosition().x - mvObjectPosition.x), /*std::abs*/(mpPlayer->GetObjectPosition().z - mvObjectPosition.z))) * /*std::abs*/(mpPlayer->GetObjectPosition().z - mvObjectPosition.z)));
        //DrawFormatString(0, 180, GetColor(255, 0, 0), "zPos:%f", (std::sin(std::atan2(/*std::abs*/(mpPlayer->GetObjectPosition().x - mvObjectPosition.x), /*std::abs*/(mpPlayer->GetObjectPosition().z - mvObjectPosition.z))) * /*std::abs*/(mpPlayer->GetObjectPosition().x - mvObjectPosition.x)) + (std::cos(std::atan2(/*std::abs*/(mpPlayer->GetObjectPosition().x - mvObjectPosition.x), /*std::abs*/(mpPlayer->GetObjectPosition().z - mvObjectPosition.z))) * /*std::abs*/(mpPlayer->GetObjectPosition().z - mvObjectPosition.z)));
    }
}

/*
* @fn Finalize
* @drief 終了処理
*/
void EnemyMap::MyFinailize()
{
}

/*
* @fn HpZeroMove
* @drief HPが0以下時の処理
*/
void EnemyMap::HpZeroMove()
{
    mpMotion->SetMotionEnd(&mbMotionEndFlag);

    SetDeleteFlag(true);
}

/*
* @fn PlayerCheck
* @drief プレイヤーが近くに居るか
*/
bool EnemyMap::PlayerCheck()
{
    bool flag = false;
/*
    var targetPos = GetTargetPos(this.targetPlayer.transform.localPosition);
    {
        float targetAngle = Mathf.Atan2(targetPos.x, targetPos.z);
        var setPos = targetPos;
        targetPos.x = (Mathf.Cos(targetAngle) * setPos.x) - (Mathf.Sin(targetAngle) * setPos.z);
        targetPos.z = (Mathf.Sin(targetAngle) * setPos.x) + (Mathf.Cos(targetAngle) * setPos.z);
    }
    var targetDistance = Mathf.Abs(targetPos.x) + Mathf.Abs(targetPos.z);
    */
    if (mpPlayer != nullptr) {
        /*VECTOR targetPos = VGet((mpPlayer->GetObjectPosition().x - mvObjectPosition.x), 0.0f, (mpPlayer->GetObjectPosition().z - mvObjectPosition.z));

        float targetAngle = std::atan2(targetPos.x, targetPos.z);
        VECTOR setPos = targetPos;
        targetPos.x = (std::cos(targetAngle) * setPos.x) - (std::sin(targetAngle) * setPos.z);
        targetPos.z = (std::sin(targetAngle) * setPos.x) + (std::cos(targetAngle) * setPos.z);

        float targetDistance = std::abs(targetPos.x) + std::abs(targetPos.z);

        flag |= targetDistance < mfSearchRange;*/
        flag |= Calculation::Check_Circle_And_Pos(mvObjectPosition, (msStatus.size * 1.5f) + (mpPlayer->GetStatus().size * 1.5f), mpPlayer->GetObjectPosition());
    }

    return flag;
}

/*
* @fn SetEnemyDataSurvivalFlag
* @drief このエネミーのデータの生存フラグをfalseにする
*/
void EnemyMap::SetEnemyDataSurvivalFlag()
{
    OneData oneData = Master::mpGameManager->GetDataManager()->GetOneData(mstrDataFileName, (int)DataType::CHARACTER);
    for (int i = 0; i < oneData.datas.characterDatas.size(); ++i) {
        if (oneData.datas.characterDatas[i].templateData.name == mstrName) {
            oneData.datas.characterDatas[i].survivalFlag = false;
            break;
        }
    }
    Master::mpGameManager->GetDataManager()->ChangeOneData(oneData, mstrDataFileName, (int)DataType::CHARACTER);
}

/*
* @fn SetDeleteData
* @drief このデータを削除する
*/
void EnemyMap::SetDeleteData()
{
    CHARACTER_DATA deleteCharacter;
    OneData oneData = Master::mpGameManager->GetDataManager()->GetOneData(mstrDataFileName, (int)DataType::CHARACTER);
    for (int i = 0; i < oneData.datas.characterDatas.size(); ++i) {
        if (oneData.datas.characterDatas[i].templateData.name == mstrName) {
            oneData.datas.characterDatas.erase(oneData.datas.characterDatas.begin() + i);
            break;
        }
    }
    Master::mpGameManager->GetDataManager()->ChangeOneData(oneData, mstrDataFileName, (int)DataType::CHARACTER);
}