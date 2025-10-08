#include <iostream>
#include <string>

#include "DxLib.h"
#include "../Header/Attack_CloseRange.h"
#include "../Header/Calculation.h"
#include "../Header/CharacterType_Enum.h"
#include "../Header/DataManager.h"
#include "../Header/Data_Structs.h"
#include "../Header/EnemyBattleBoss.h"
#include "../Header/GameManager.h"
#include "../Header/MotionRobotSphere.h"
#include "../Header/ObjectManager.h"
#include "../Header/ObjectTagMacro.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/SceneManager.h"
#include "../Header/Scene_Enum.h"
#include "../Header/Status_Struct.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
EnemyBattleBoss::EnemyBattleBoss(Object_Base_Character *player, VECTOR position, float angle, STATUS status, CHARACTER_TYPE enemyType, std::string name)
: Object_Base_Character(status, angle, name, "NULL")
, mpPlayer(player)
, meEnemyType(enemyType)
, mnActionType(0)
, mnNextActionTime(0)
, mvSetActionVec(VGet(0.0f, 0.0f, 0.0f))
, mnAttackIntervalTime(0)
{
    mvObjectPosition = position;
}

/*
* @fn デストラクタ
*/
EnemyBattleBoss::~EnemyBattleBoss()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void EnemyBattleBoss::Initilize()
{
    SetTag(ENEMY_TAG);

    switch (meEnemyType)
    {
    case CHARACTER_TYPE::BATTLE_BOSS_ENEMY_1:
        mpMotion = new MotionRobotSphere(this, 3000, false, true);
        mpMotion->Initilize();
        break;
    }
}

/*
* @fn Update
* @drief 更新
*/
void EnemyBattleBoss::Update()
{
    // 時間停止フラグが有効なら更新しない
    if (Master::mpGameManager->GetTimeManager()->GetStopFlag()) {
        return;
    }

    // 終了時処理
    EndProcess();

    // モーションフラグを初期化
    mpMotion->ReSetFlag();

    bool attackFlag = false;
    VECTOR setPos = VGet(0.0f, 0.0f, 0.0f);
    if (!mpMotion->GetStopMoveMotionFlag()) {
        if (mnNextActionTime <= Master::mpGameManager->GetTimeManager()->GetGameTime()) {
            NewActionSet();
        }

        switch (meEnemyType)
        {
        case CHARACTER_TYPE::BATTLE_BOSS_ENEMY_1:
            switch (mnActionType)
            {
                // 移動
            case 0:
            case 6:
            case 10:
                mvSetActionVec = VScale(Calculation::GetMovePos(mvObjectPosition, mpPlayer->GetObjectPosition()), (msStatus.speed));
                if (Calculation::Check_Circle_And_Pos(mvObjectPosition, msStatus.size + mpPlayer->GetStatus().size, mpPlayer->GetObjectPosition())) {
                    attackFlag = true;
                    break;
                }
            case 1:
            case 2:
                if (Calculation::Check_Circle_And_Pos(mvObjectPosition, msStatus.size + mpPlayer->GetStatus().size, mpPlayer->GetObjectPosition())) {
                    attackFlag = true;
                }
                setPos = mvSetActionVec;
                mpMotion->SetMoveFlag(true);
                mpMotion->SetAnglePosition(mvSetActionVec);
                break;

                // 攻撃方向設定
            case 3:
            case 7:
            case 11:
            case 4:
            case 8:
            case 12:
                mpMotion->SetAnglePosition(mvSetActionVec);
                break;

                // 何もしない
            case 5:
            case 9:
            case 13:
            case 14:
                break;

            case 15:
                break;
            }
            break;
        }
    }
    else {
        // 移動の処理の代わりの処理
        setPos = mpMotion->StopMoveProcess();
    }
    // 固定物に当たっていれば移動する
    VECTOR  fixedMove = Master::mpGameManager->GetObjectManager()->FixedObjectHitCheck(VAdd(mvObjectPosition, setPos), mvObjectPosition, setPos, msStatus.size);
    mvObjectPosition = VAdd(VAdd(mvObjectPosition, setPos), fixedMove);
    if ((fixedMove.x != 0.0f) || (fixedMove.z != 0.0f)) {
        mpMotion->FixedHitSound();
    }
    
    // 攻撃
    if (!mpMotion->GetStopAttackFlag()) {
        switch (meEnemyType)
        {
        case CHARACTER_TYPE::BATTLE_BOSS_ENEMY_1:
            switch (mnActionType)
            {
            case 0:
            case 6:
            case 10:
                if (attackFlag) {
                    SetMotionAttack();
                }
            case 1:
            case 2:
                if (attackFlag) {
                    // 近距離攻撃
                    if (mnAttackIntervalTime <= Master::mpGameManager->GetTimeManager()->GetGameTime()) {
                        Attack_CloseRange *enemyAttack;
                        enemyAttack = new Attack_CloseRange(this, msStatus.attackPower, Master::mpGameManager->GetTimeManager()->GetOneFrame() * 10, mvObjectPosition, msStatus.size);
                        mnAttackIntervalTime = (Master::mpGameManager->GetTimeManager()->GetOneFrame() * 10) + Master::mpGameManager->GetTimeManager()->GetGameTime();
                    }
                }
                break;

            case 3:
            case 7:
            case 11:
            case 4:
            case 8:
            case 12:
                SetMotionAttack();
                break;

                // 何もしない
            case 5:
            case 9:
            case 13:
            case 14:
                break;

            case 15:
                break;
            }
            break;
        }
    }
    else {
        // 攻撃の処理の代わりの処理
        mpMotion->StopAttackProcess();
    }

    // 敵に当たったか
    Master::mpGameManager->GetObjectManager()->AllAttackObjectHitCheck(this);

    // モーション更新
    mpMotion->Update();
}

/*
* @fn Draw
* @drief 描画
*/
void EnemyBattleBoss::Draw()
{
    // モデル描画
    mpMotion->Draw();

    // ステータス描画
    DrawBillboard_Name_Level_Hp();
}

/*
* @fn MyFinailize
* @drief 終了処理
*/
void EnemyBattleBoss::MyFinailize()
{
}

/*
* @fn HpZeroMove
* @drief HPが0以下時の処理
*/
void EnemyBattleBoss::HpZeroMove()
{
    mpMotion->SetMotionEnd(&mbMotionEndFlag);
}

/*
* @fn EndProcess
* @drief 終了処理
*/
void EnemyBattleBoss::EndProcess()
{
    if (mbMotionEndFlag) {
        Master::mpGameManager->GetSceneManager()->SetNextScene(SCENE::GAME_CLEAR);

        // プレイヤーデータ入力
        if (mpPlayer != nullptr)
        {
            PLAYER_DATA playerData = Master::mpGameManager->GetDataManager()->GetPlayPlayerData();
            playerData.characterData.status = mpPlayer->GetStatus();

            for (int i = 0; i < msStatus.level; i++) {
                playerData.characterData.status.exp += GetRand(10);
            }
            // レベルアップ確認
            LEVEL_DATA levelData = Master::mpGameManager->GetDataManager()->GetLevelData(Master::mpGameManager->GetDataManager()->GetAllData(true), playerData.characterData.templateData.typeNumber);
            bool levelUpFlag = true;
            while (levelUpFlag) {
                if (levelData.levelUpExpNumber[(playerData.characterData.status.level - 1)] <= playerData.characterData.status.exp && (levelData.maxLevelNumber > playerData.characterData.status.level)) {
                    playerData.characterData.status.exp -= levelData.levelUpExpNumber[(playerData.characterData.status.level - 1)];
                    playerData.characterData.status.level += 1;

                    // レベルアップ時ステータス処理
                    {
                        playerData.characterData.status.attackPower += GetRand(3);
                        playerData.characterData.status.defense += GetRand(2);
                        playerData.characterData.status.speed += GetRand(1);
                        int hpUp = GetRand(10);
                        playerData.characterData.status.maxHp += hpUp;
                        playerData.characterData.status.hp += hpUp;
                    }
                }
                else {
                    levelUpFlag = false;
                }
            }

            Master::mpGameManager->GetDataManager()->SetPlayPlayerData(playerData);
        }
    }
}

/*
* @fn NewActionSet
* @drief 新しいアクション設定
*/
void EnemyBattleBoss::NewActionSet()
{
    if ((msStatus.maxHp / 2) < msStatus.hp) {
        mnActionType = GetRand(5);
    }
    else if ((msStatus.maxHp / 4) < msStatus.hp) {
        mnActionType = (GetRand(3) + 6);
    }
    else if (10 < msStatus.hp) {
        mnActionType = (GetRand(4) + 10);
    }
    else if (0 < msStatus.hp) {
        // 周りに敵をまき散らす
        mnActionType = 15;
    }

    // 新しいアクションの初期設定
    float setFloatNumber = 0.0f;
    int setIntNumber = 0;
    switch (meEnemyType)
    {
    case CHARACTER_TYPE::BATTLE_BOSS_ENEMY_1:
        switch (mnActionType)
        {
            // プレイヤーに向かって移動近づいたら転がり攻撃
        case 0:
        case 6:
        case 10:
            mnNextActionTime = (Master::mpGameManager->GetTimeManager()->GetGameTime() + 7000);
            break;

            // プレイヤー方向を設定してその方向に更新しないで移動
        case 1:
            mnNextActionTime = (Master::mpGameManager->GetTimeManager()->GetGameTime() + 7000);
            mvSetActionVec = VScale(Calculation::GetMovePos(mvObjectPosition, mpPlayer->GetObjectPosition()), (msStatus.speed));
            break;

            // ランダム方向に移動
        case 2:
            mnNextActionTime = (Master::mpGameManager->GetTimeManager()->GetGameTime() + 7000);
            setIntNumber = static_cast<int>(Master::mpGameManager->GetSceneManager()->GetMapMaxSize());
            mvSetActionVec = VScale(Calculation::GetMovePos(mvObjectPosition, VGet(GetRand(setIntNumber * 2) - setIntNumber, 0, GetRand(setIntNumber * 2) - setIntNumber)), (msStatus.speed));
            break;

            // プレイヤーに向かって転がり攻撃
        case 3:
        case 7:
        case 11:
            mnNextActionTime = (Master::mpGameManager->GetTimeManager()->GetGameTime() + mpMotion->GetAttackTime());
            mvSetActionVec = VScale(Calculation::GetMovePos(mvObjectPosition, mpPlayer->GetObjectPosition()), (msStatus.speed));
            break;

            // ランダム方向に転がり攻撃
        case 4:
        case 8:
        case 12:
            mnNextActionTime = (Master::mpGameManager->GetTimeManager()->GetGameTime() + mpMotion->GetAttackTime());
            setIntNumber = static_cast<int>(Master::mpGameManager->GetSceneManager()->GetMapMaxSize());
            mvSetActionVec = VScale(Calculation::GetMovePos(mvObjectPosition, VGet(GetRand(setIntNumber * 2) - setIntNumber, 0, GetRand(setIntNumber * 2) - setIntNumber)), (msStatus.speed));
            break;

            // 止まってる
        case 5:
        case 9:
        case 13:
        case 14:
            mnNextActionTime = (Master::mpGameManager->GetTimeManager()->GetGameTime() + 7000);
            break;

            // 周りにエネミーをばらまく
        case 15:
            mnNextActionTime = (Master::mpGameManager->GetTimeManager()->GetGameTime() + 1700000);
            break;
        }
        break;
    }
}