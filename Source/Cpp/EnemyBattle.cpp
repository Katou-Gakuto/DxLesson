#include <cmath>
#include <vector>

#include "DxLib.h"
#include "../Header/Calculation.h"
#include "../Header/CharacterType_Enum.h"
#include "../Header/Attack_CloseRange.h"
#include "../Header/DataManager.h"
#include "../Header/Data_Structs.h"
#include "../Header/EnemyBattle.h"
#include "../Header/GameManager.h"
#include "../Header/MotionRobotSphere.h"
#include "../Header/ObjectManager.h"
#include "../Header/ObjectTagMacro.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/Operation.h"
#include "../Header/SceneManager.h"
#include "../Header/Scene_Enum.h"
#include "../Header/TimeManager.h"

/*
* @fn コンストラクタ
*/
EnemyBattle::EnemyBattle(Object_Base_Character *player, VECTOR position, float angle, STATUS status, CHARACTER_TYPE enemyType, std::string name, float closeDistance, float mediumDistance, float farDistance)
: Object_Base_Character(status, angle, name, "NULL")
, mpPlayer(player)
, meEnemyType(enemyType)
, mnAttackTime(0)
, mfCloseDistance(closeDistance)
, mfMediumDistance(mediumDistance)
, mfFarDistance(farDistance)
, mnCloseAttackInterval(0)
, mnMediumAttackInterval(0)
, mnFarAttackInterval(0)
{
    mvObjectPosition = position;
}

/*
* @fn デストラクタ
*/
EnemyBattle::~EnemyBattle()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void EnemyBattle::Initilize()
{
    SetTag(ENEMY_TAG);

    switch (meEnemyType)
    {
    case CHARACTER_TYPE::BATTLE_WEAK_ENEMY_1:
        mpMotion = new MotionRobotSphere(this, 3000);
        mpMotion->Initilize();
        mnCloseAttackInterval = 1020;
        mnMediumAttackInterval = GetRand(5000);
        break;
    }
}

/*
* @fn Update
* @drief 更新
*/
void EnemyBattle::Update()
{
    // 時間停止フラグが有効なら更新しない
    if (Master::mpGameManager->GetTimeManager()->GetStopFlag()) {
        return;
    }

    // 終了時処理
    EndProcess();

    // モーションフラグを初期化
    mpMotion->ReSetFlag();

    // 移動量
    VECTOR setMove = VGet(0, 0, 0);

    switch (PlayerCheck())
    {
    case 0:
        switch (meEnemyType)
        {
        case CHARACTER_TYPE::BATTLE_WEAK_ENEMY_1:

            if (!mpMotion->GetStopMoveMotionFlag()) {
                // 移動
                setMove = VScale(Calculation::GetMovePos(mvObjectPosition, mpPlayer->GetObjectPosition()), (msStatus.speed * 0.05f));
                //mvObjectPosition = VAdd(setMove, mvObjectPosition);
                mpMotion->SetMoveFlag(true);
                mpMotion->SetAnglePosition(setMove);
            }
            else {
                // 移動の処理の代わりの処理
                setMove = mpMotion->StopMoveProcess();
            }

            if (!mpMotion->GetStopAttackFlag()) {
                if (((mnAttackTime + mnCloseAttackInterval) < Master::mpGameManager->GetTimeManager()->GetGameTime()) && (!mpMotion->GetAttackFlag())) {
                    mnAttackTime = Master::mpGameManager->GetTimeManager()->GetGameTime();
                    // 攻撃
                    Attack_CloseRange *enemyAttack;
                    enemyAttack = new Attack_CloseRange(this, msStatus.attackPower, 1020, VAdd(mvObjectPosition, VScale(Calculation::GetMovePos(mvObjectPosition, mpPlayer->GetObjectPosition()), 170.0f)), 80.0f);
                }
            }
            else {
                // 攻撃の処理の代わりの処理
                mpMotion->StopAttackProcess();
            }
            break;
        }
        break;

    case 1:
        switch (meEnemyType)
        {
        case CHARACTER_TYPE::BATTLE_WEAK_ENEMY_1:
            if (!mpMotion->GetStopMoveMotionFlag()) {
                // 移動
                setMove = VScale(Calculation::GetMovePos(mvObjectPosition, mpPlayer->GetObjectPosition()), msStatus.speed);
                //mvObjectPosition = VAdd(setMove, mvObjectPosition);
                mpMotion->SetMoveFlag(true);
                mpMotion->SetAnglePosition(setMove);
            }
            else {
                // 移動の処理の代わりの処理
                setMove = mpMotion->StopMoveProcess();
            }

            if (!mpMotion->GetStopAttackFlag()) {
                if (msStatus.level >= 30) {
                    if (((mnAttackTime + mnMediumAttackInterval) < Master::mpGameManager->GetTimeManager()->GetGameTime()) && (!mpMotion->GetAttackFlag())) {
                        mnAttackTime = Master::mpGameManager->GetTimeManager()->GetGameTime();
                        mnMediumAttackInterval = (mpMotion->GetAttackTime() + GetRand(20000));
                        // 攻撃
                        SetMotionAttack();
                    }
                }
            }
            else {
                // 攻撃の処理の代わりの処理
                mpMotion->StopAttackProcess();
            }
            break;
        }
        break;

    case 2:
        switch (meEnemyType)
        {
        case CHARACTER_TYPE::BATTLE_WEAK_ENEMY_1:
            if (!mpMotion->GetStopMoveMotionFlag()) {
                // 移動
                setMove = VScale(VScale(Calculation::GetMovePos(mvObjectPosition, mpPlayer->GetObjectPosition()), msStatus.speed), 1.5f);
                //mvObjectPosition = VAdd(setMove, mvObjectPosition);
                mpMotion->SetMoveFlag(true);
                mpMotion->SetAnglePosition(setMove);
            }
            else {
                // 移動の処理の代わりの処理
                setMove = mpMotion->StopMoveProcess();
            }
            break;
        }
        break;
    }
    // 固定物に当たっていれば移動する
    VECTOR  fixedMove = Master::mpGameManager->GetObjectManager()->FixedObjectHitCheck(VAdd(mvObjectPosition, setMove), mvObjectPosition, setMove, msStatus.size);
    mvObjectPosition = VAdd(VAdd(mvObjectPosition, setMove), fixedMove);
    if ((fixedMove.x != 0.0f) || (fixedMove.z != 0.0f)) {
        mpMotion->FixedHitSound();
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
void EnemyBattle::Draw()
{
    // モデル描画
    mpMotion->Draw();

    // ステータス描画
    DrawBillboard_Name_Level_Hp();

    //DrawSphere3D(mvObjectPosition, mfCloseDistance - 100.0f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
    //DrawSphere3D(mvObjectPosition, mfMediumDistance - 100.0f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
    //DrawSphere3D(mvObjectPosition, mfFarDistance - 100.0f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
}

/*
* @fn MyFinailize
* @drief 終了処理
*/
void EnemyBattle::MyFinailize()
{
}

/*
* @fn HpZeroMove
* @drief HPが0以下時の処理
*/
void EnemyBattle::HpZeroMove()
{
    mpMotion->SetMotionEnd(&mbMotionEndFlag);
}

/*
* @fn PlayerCheck
* @drief プレイヤーが度の距離にいるのか調べる
*/
int EnemyBattle::PlayerCheck()
{
    int check = 0;

    
    if (mpPlayer != nullptr) {/*
        VECTOR targetPos = VGet((mpPlayer->GetObjectPosition().x - mvObjectPosition.x), 0.0f, (mpPlayer->GetObjectPosition().z - mvObjectPosition.z));

        float targetAngle = std::atan2(targetPos.x, targetPos.z);
        VECTOR setPos = targetPos;
        targetPos.x = (std::cos(targetAngle) * setPos.x) - (std::sin(targetAngle) * setPos.z);
        targetPos.z = (std::sin(targetAngle) * setPos.x) + (std::cos(targetAngle) * setPos.z);

        float targetDistance = std::abs(targetPos.x) + std::abs(targetPos.z);

        check += (targetDistance < mfCloseDistance) ? 0 : 1;
        check += (targetDistance < mfMediumDistance) ? 0 : 1;
        check += (targetDistance < mfFarDistance) ? 0 : 1;*/
        check += (Calculation::Check_Circle_And_Pos(mvObjectPosition, mfCloseDistance, mpPlayer->GetObjectPosition()) ? 0 : 1);
        check += (Calculation::Check_Circle_And_Pos(mvObjectPosition, mfMediumDistance, mpPlayer->GetObjectPosition()) ? 0 : 1);
        check += (Calculation::Check_Circle_And_Pos(mvObjectPosition, mfFarDistance, mpPlayer->GetObjectPosition()) ? 0 : 1);
    }

    return check;
}

/*
* @fn GetMove
* @drief プレイヤーまでの移動量
*/
VECTOR EnemyBattle::PlayerDistance()
{
    return VGet(mpPlayer->GetObjectPosition().x - mvObjectPosition.x, 0.0f, mpPlayer->GetObjectPosition().z - mvObjectPosition.z);
}

/*
* @fn EnemyMove
* @drief このキャラクターの移動量
*/
VECTOR EnemyBattle::EnemyMove()
{
    VECTOR move = PlayerDistance();

    float denominator = std::abs(move.x) + std::abs(move.z);

    move = VGet(((std::abs(move.x) / denominator) * (std::signbit(move.x) ? -1 : 1)) * msStatus.speed, 0.0f, ((std::abs(move.z) / denominator) * (std::signbit(move.z) ? -1 : 1)) * msStatus.speed);

    return move;
}

/*
* @fn EndProcess
* @drief 終了処理
*/
void EnemyBattle::EndProcess()
{
    if (mbMotionEndFlag)
    {
        SetDeleteFlag(true);
        bool flag = false;
        // 全てのエネミーが倒されたか判定
        std::vector<Object_Base_Character *> setEnemy = Master::mpGameManager->GetObjectManager()->FindsByTag_CharacterObject(ENEMY_TAG);
        for (int i = 0; i < setEnemy.size(); i++) {
            if (setEnemy[i]->GetObjectScene() != SCENE::EXCEPTION) {
                if (!setEnemy[i]->IsDeleteFlag()) {
                    flag = true;
                }
            }
        }

        if (!flag) {
            // バトルリザルト処理
            Master::mpGameManager->GetSceneManager()->SetNextScene(SCENE::BATTLE_RESULT);

            if (mpPlayer != nullptr)
            {
                PLAYER_DATA playerData = Master::mpGameManager->GetDataManager()->GetPlayerData(Master::mpGameManager->GetSceneManager()->GetPlayerDataNumber());
                playerData.characterData.status = mpPlayer->GetStatus();
                for (int i = 0; i < msStatus.level; i++) {
                    playerData.characterData.status.exp += GetRand(5);
                }
                // レベルアップ確認
                LEVEL_DATA levelData = Master::mpGameManager->GetDataManager()->GetLevelData();
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

                Master::mpGameManager->GetDataManager()->Set_MyPlayerData(Master::mpGameManager->GetSceneManager()->GetPlayerDataNumber(), playerData);
            }
        }
    }
}