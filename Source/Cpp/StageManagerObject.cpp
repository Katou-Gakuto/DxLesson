#include <cmath>
#include <vector>

#include "DxLib.h"
#include "../Header/Camera.h"
#include "../Header/CoordinateXY.h"
#include "../Header/CharacterType_Enum.h"
#include "../Header/EnemyBattle.h"
#include "../Header/EnemyBattleBoss.h"
#include "../Header/EnemyMap.h"
#include "../Header/FixedBoxWall.h"
#include "../Header/GameManager.h"
#include "../Header/GenerateInformation_Struct.h"
#include "../Header/MapCharacter.h"
#include "../Header/MapType_Enum.h"
#include "../Header/ObjectManager.h"
#include "../Header/ObjectTagMacro.h"
#include "../Header/Object_Base_Character.h"
#include "../Header/Object_Base_Fixed.h"
#include "../Header/Operation.h"
#include "../Header/PlayerMap.h"
#include "../Header/PlayerRobot.h"
#include "../Header/SceneManager.h"
#include "../Header/Scene_Enum.h"
#include "../Header/StageManagerObject.h"
#include "../Header/Status_Struct.h"

/*
* @fn コンストラクタ
*/
StageManagerObject::StageManagerObject(const char *filename, MAP_TYPE maptype, VECTOR plusPosition, VECTOR minusPosition, bool mapFlag, float *magnificationRate)
: Object_Base()
, msMaptype(maptype)
, mvPlusPosition(plusPosition)
, mvMinusPosition(minusPosition)
, mbMapDrawFlag(mapFlag)
, mfMapAngle(0.0f)
, mfMagnificationRate(magnificationRate)
{
    /*mnMapHandle = -1;
    mnMapHandle = MV1LoadModel(filename);
    */
    mnMapHandleFileName = const_cast<char *>(filename);

    msGenerateInformation.clear();
    

    mfMinMagnificationRate = ((plusPosition.x + plusPosition.z) / 2) / 5;   // 拡大率　最小
    mfMaxMagnificationRate = ((plusPosition.x + plusPosition.z) / 2);       // 拡大率　最大



    // 画面サイズ取得
    COORDINATE_X_Y_INT set = XYGet_Int(0, 0);
    int colorBit = 0;
    GetScreenState(&set.x, &set.y, &colorBit);
    /*
    msMapUpperLeft = XYGet((set.x / 10) * 0.2, set.y / 24); // 左上
    msMapLowerRight = XYGet((set.x / 10) * 1.67, set.y / 4);  // 右下*/
//    /*
    msMapUpperLeft = XYGet((set.x / 10) * 8.33 , set.y / 24); // 左上
    msMapLowerRight = XYGet((set.x / 10) *  9.8, set.y / 4);  // 右下*/
    msMapSide = XYGet((msMapLowerRight.x - msMapUpperLeft.x), (msMapLowerRight.y - msMapUpperLeft.y));  // 一辺
    mnMapFrameDreadth = 5;
    msMapMiddle = XYGet((msMapSide.x / 2) + mnMapFrameDreadth, (msMapSide.y / 2) + mnMapFrameDreadth);

    mnMapDrawHandle = MakeScreen(msMapSide.x + (mnMapFrameDreadth * 2), msMapSide.y + (mnMapFrameDreadth * 2), TRUE);
}

/*
* @fn デストラクタ
*/
StageManagerObject::~StageManagerObject()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void StageManagerObject::Initilize()
{/*
    if (!mbNotExceptionFlag) {
        if (meObjectScene == SCENE::EXCEPTION) {
            Master::mpGameManager->GetSceneManeger()->SetNextScene(meGenerateScene);
        }
        meGenerateScene = meObjectScene;
        meObjectScene = SCENE::EXCEPTION;
    }*/
    SetTag(STAGE_MANAGER_TAG);
}

/*
* @fn Update
* @drief 更新
*/
void StageManagerObject::Update()
{
    //MapMagnification();
}

/*
* @fn Draw
* @drief 描画
*/
void StageManagerObject::Draw()
{/*
    if (mnMapHandle != -1) {
        for (int i = 0; i < (((mvPlusPosition.x / 3) * 0.01) + 2); i++) {
            for (int j = 0; j <= (((mvPlusPosition.z / 3) * 0.01) + 2); j++) {
                MV1SetPosition(mnMapHandle, VGet((i * 600.0f) + mvMinusPosition.x, 0, (j * 600.0f) + mvMinusPosition.z));
                MV1DrawModel(mnMapHandle);
            }
        }
    }
    */
    //DrawFormatString(0, 200, GetColor(255, 255, 255), "%f", mfMapAngle);

    if (mbMapDrawFlag) {
        MapDraw();
    }
}

/*
* @fn Finalize
* @drief 終了処理
*/
void StageManagerObject::Finalize()
{
    DeleteGraph(mnMapDrawHandle);
}

/*
* @fn AddGenerateInforation
* @drief キャラクター情報追加
*/
void StageManagerObject::AddGenerateInforation(GENERATE_INFORATION generateInformation)
{
    msGenerateInformation.push_back(generateInformation);
}

/*
* @fn CharacterGenerate
* @drief キャラクター生成
*/
void StageManagerObject::CharacterGenerate()
{
    for (int i = 0; i < msGenerateInformation.size(); i++) {
        switch (msGenerateInformation[i].characterType) 
        {
        case CHARACTER_TYPE::MAP_PLAYER:
            PlayerMap *playerMap;
            playerMap = new PlayerMap(Master::mpCamera, msGenerateInformation[i].status, msGenerateInformation[i].GeneratePosition, msGenerateInformation[i].angle, msGenerateInformation[i].name, msGenerateInformation[i].dataFileName);
            playerMap->Initilize();
            break;

        case CHARACTER_TYPE::ROBOT_PLAYER:
            PlayerRobot *RobotPlayer;
            RobotPlayer = new PlayerRobot(Master::mpCamera, msGenerateInformation[i].status, msGenerateInformation[i].GeneratePosition, msGenerateInformation[i].angle, msGenerateInformation[i].name, msGenerateInformation[i].dataFileName);
            RobotPlayer->Initilize();
            break;

        case CHARACTER_TYPE::MAP_CHARACTER_1:
            MapCharacter *mapCharacter_1;
            mapCharacter_1 = new MapCharacter(msGenerateInformation[i].status, msGenerateInformation[i].GeneratePosition, msGenerateInformation[i].angle, msGenerateInformation[i].name, msGenerateInformation[i].characterType, msGenerateInformation[i].scene, msGenerateInformation[i].dataFileName);
            mapCharacter_1->Initilize();
            break;

        case CHARACTER_TYPE::MAP_WEAK_ENEMY_1:
            EnemyMap *mapWeakEney_1;
            mapWeakEney_1 = new EnemyMap(Master::mpGameManager->GetObjectManager()->FindByTag_CharacterObject(PLAYER_TAG), msGenerateInformation[i].GeneratePosition, msGenerateInformation[i].angle, msGenerateInformation[i].status, msGenerateInformation[i].scene, msGenerateInformation[i].name, msGenerateInformation[i].dataFileName, msGenerateInformation[i].characterType, msGenerateInformation[i].survivalFlag);
            mapWeakEney_1->Initilize();
            break;

        case CHARACTER_TYPE::MAP_BOSS_ENEMY_1:
            EnemyMap *mapBossEnemy_1;
            mapBossEnemy_1 = new EnemyMap(Master::mpGameManager->GetObjectManager()->FindByTag_CharacterObject(PLAYER_TAG), msGenerateInformation[i].GeneratePosition, msGenerateInformation[i].angle, msGenerateInformation[i].status, msGenerateInformation[i].scene, msGenerateInformation[i].name, msGenerateInformation[i].dataFileName, msGenerateInformation[i].characterType, msGenerateInformation[i].survivalFlag);
            mapBossEnemy_1->Initilize();
            break;

        case CHARACTER_TYPE::BATTLE_WEAK_ENEMY_1:
            EnemyBattle *battleEnemy_1;
            battleEnemy_1 = new EnemyBattle(Master::mpGameManager->GetObjectManager()->FindByTag_CharacterObject(PLAYER_TAG), msGenerateInformation[i].GeneratePosition, msGenerateInformation[i].angle, msGenerateInformation[i].status/*GetStatus(1, 0, 10, 20, 20, 5, 2, 80)*/, CHARACTER_TYPE::BATTLE_WEAK_ENEMY_1, msGenerateInformation[i].name);
            battleEnemy_1->Initilize();
            break;

        case CHARACTER_TYPE::BATTLE_BOSS_ENEMY_1:
            EnemyBattleBoss *enemyBattleBoss_1;
            enemyBattleBoss_1 = new EnemyBattleBoss(Master::mpGameManager->GetObjectManager()->FindByTag_CharacterObject(PLAYER_TAG), msGenerateInformation[i].GeneratePosition, msGenerateInformation[i].angle, msGenerateInformation[i].status/*GetStatus(1, 0, 40, 150, 150, 15, 10, 160)*/, CHARACTER_TYPE::BATTLE_BOSS_ENEMY_1, msGenerateInformation[i].name);
            enemyBattleBoss_1->Initilize();
            break;
        }
    }

    FixedBoxWall *boxWall = new FixedBoxWall(mvPlusPosition, mvMinusPosition, mnMapHandleFileName);
    boxWall->Initilize();
}

/*
* @fn GetStatus
* @drief ステータス取得
*/
STATUS StageManagerObject::GetStatus(int level, int exp, int attackPower, int maxHp, int hp, int defense, int speed, int size)
{
    STATUS status;
    status.level = level;
    status.exp = exp;
    status.attackPower = attackPower;
    status.maxHp = maxHp;
    status.hp = hp;
    status.defense = defense;
    status.speed = speed;
    status.size = size;

    return status;
}

/*
* @fn MapDraw
* @drief マップ描画処理
*/
void StageManagerObject::MapDraw()
{
    // 描画先を変更
    SetDrawScreen(mnMapDrawHandle);
    ClearDrawScreen();
    
    // マップ描画場所
    DrawBoxAA(mnMapFrameDreadth, mnMapFrameDreadth, msMapSide.x + mnMapFrameDreadth, msMapSide.y + mnMapFrameDreadth, GetColor(0, 0, 0), TRUE);
    
    Object_Base_Character *targetObject = Master::mpGameManager->GetObjectManager()->FindByTag_CharacterObject(PLAYER_TAG);
    if (targetObject != nullptr)
    {
        VECTOR set = Master::mpCamera->GetDirection();
        mfMapAngle = atan2(set.x, set.z);
        // マップ土台描画
        {
            std::vector <Object_Base_Fixed *> fixedObject = Master::mpGameManager->GetObjectManager()->FindsByTag_FixedObject(WALL_TAG);
            for (int i = 0; i < fixedObject.size(); i++) {
                COORDINATE_X_Y xPlus_yPlus = GetMapPos(fixedObject[i]->GetPlusPosition());
                COORDINATE_X_Y xPlus_yMinus = GetMapPos(VGet(fixedObject[i]->GetPlusPosition().x, 0, fixedObject[i]->GetMinusPosition().z));
                COORDINATE_X_Y xMinus_yPlus = GetMapPos(VGet(fixedObject[i]->GetMinusPosition().x, 0, fixedObject[i]->GetPlusPosition().z));
                COORDINATE_X_Y xMinus_yMinus = GetMapPos(fixedObject[i]->GetMinusPosition());

                DrawTriangle(xPlus_yPlus.x + msMapMiddle.x, xPlus_yPlus.y + msMapMiddle.y,
                    xPlus_yMinus.x + msMapMiddle.x, xPlus_yMinus.y + msMapMiddle.y,
                    xMinus_yPlus.x + msMapMiddle.x, xMinus_yPlus.y + msMapMiddle.y, fixedObject[i]->GetDrawMapColor(), true);

                DrawTriangle(xMinus_yMinus.x + msMapMiddle.x, xMinus_yMinus.y + msMapMiddle.y,
                    xPlus_yMinus.x + msMapMiddle.x, xPlus_yMinus.y + msMapMiddle.y,
                    xMinus_yPlus.x + msMapMiddle.x, xMinus_yPlus.y + msMapMiddle.y, fixedObject[i]->GetDrawMapColor(), true);
            }
        }

        std::vector<Object_Base_Character *> neutralCharacter = Master::mpGameManager->GetObjectManager()->FindsByTag_CharacterObject(NEUTRAL_CHARACTER);
        for (int i = 0; i < neutralCharacter.size(); i++) {
                COORDINATE_X_Y set = GetMapPos(neutralCharacter[i]->GetObjectPosition());

                DrawCircleAA(set.x + msMapMiddle.x, set.y + msMapMiddle.y, 6 * (mfMinMagnificationRate / *mfMagnificationRate), 32, GetColor(0,255, 0), TRUE);
        }

        // エネミー描画
        std::vector<Object_Base_Character *> enemyObject = Master::mpGameManager->GetObjectManager()->FindsByTag_CharacterObject(ENEMY_TAG);
        for (int i = 0; i < enemyObject.size(); i++) {
            if (enemyObject[i]->GetObjectScene() != SCENE::EXCEPTION) {
                COORDINATE_X_Y set = GetMapPos(enemyObject[i]->GetObjectPosition());

                DrawCircleAA(set.x + msMapMiddle.x, set.y + msMapMiddle.y, 6 * (mfMinMagnificationRate / *mfMagnificationRate), 32, GetColor(255, 0, 0), TRUE);
            }
        }

        // プレイヤー位置描画(中心)
        DrawCircleAA(msMapMiddle.x, msMapMiddle.y, 6 * (mfMinMagnificationRate / *mfMagnificationRate), 32, GetColor(0, 0, 255), TRUE);

        // マップ枠描画
        DrawBox(0, 0, mnMapFrameDreadth, msMapSide.y + (mnMapFrameDreadth * 2), GetColor(0, 0, 0), TRUE); // 左
        DrawBox(mnMapFrameDreadth, 0, msMapSide.x + mnMapFrameDreadth, mnMapFrameDreadth, GetColor(0, 0, 0), TRUE); // 上
        DrawBox(msMapSide.x + mnMapFrameDreadth, 0, msMapSide.x + (mnMapFrameDreadth * 2), msMapSide.y + (mnMapFrameDreadth * 2), GetColor(0, 0, 0), TRUE); // 右
        DrawBox(mnMapFrameDreadth, msMapSide.y + mnMapFrameDreadth, msMapSide.x + mnMapFrameDreadth, msMapSide.y + (mnMapFrameDreadth * 2), GetColor(0, 0, 0), TRUE); // 下

        SetDrawScreen(DX_SCREEN_BACK);
        // 3Dカメラ設定
        Master::mpCamera->Initialize3DCameraTemplate();
        DrawGraph(msMapUpperLeft.x - mnMapFrameDreadth, msMapUpperLeft.y - mnMapFrameDreadth, mnMapDrawHandle, TRUE);
    }
}

/*
* @fn MapMagnification
* @drief 拡大系処理
*/
void StageManagerObject::MapMagnification()
{
    if (Operation::CheckLeftKey()) {
        *mfMagnificationRate -= 80.0f;
        if (*mfMagnificationRate < mfMinMagnificationRate) {
            *mfMagnificationRate = mfMinMagnificationRate;
        }
    }
    if (Operation::CheckRightKey()) {
        *mfMagnificationRate += 80.0f;
        if (*mfMagnificationRate > mfMaxMagnificationRate) {
            *mfMagnificationRate = mfMaxMagnificationRate;
        }
    }
}

/*
* @fn GetMapPos
* @drief マップの何処に描画するか返す
*/
COORDINATE_X_Y StageManagerObject::GetMapPos(VECTOR pos)
{
    COORDINATE_X_Y targetPos = XYGet(0, 0);

    Object_Base_Character *player = Master::mpGameManager->GetObjectManager()->FindByTag_CharacterObject(PLAYER_TAG);

    targetPos.x = (((pos.x - player->GetObjectPosition().x) / *mfMagnificationRate) * (msMapSide.x / 2));// *sinf((mfMapAngle - angle /* (2.0f * DX_PI_F)*/));
    targetPos.y = (((player->GetObjectPosition().z - pos.z) / *mfMagnificationRate) * (msMapSide.x / 2)); //* cosf((mfMapAngle - angle)); //<= 0 ? mfMapAngle : mfMapAngle));

    float angle = atan2(targetPos.x, targetPos.y);
    
    COORDINATE_X_Y setPos = targetPos;
        
    targetPos.x = (setPos.x * cosf(angle)) - (setPos.y * sinf(angle));
    targetPos.y = ((setPos.x * sinf(angle)) + (setPos.y * cosf(angle)));

    setPos = targetPos;

    targetPos.x = setPos.y * sinf(Calculation::GetNotExceedAngle(angle + mfMapAngle));
    targetPos.y = setPos.y * cosf(Calculation::GetNotExceedAngle(angle + mfMapAngle));

    return targetPos;
}

/*
* @fn GetStagePos
* @drief マップの座標はステージの何処を示すか返す
*/
COORDINATE_X_Y StageManagerObject::GetStagePos(COORDINATE_X_Y pos)
{
    COORDINATE_X_Y targetPos = XYGet(0, 0);

    float angle = std::atan2(pos.x, pos.y);

    targetPos.x = (pos.x * cosf(angle)) - (pos.y * sinf(angle));
    targetPos.y = ((pos.x * sinf(angle)) + (pos.y * cosf(angle)));

    COORDINATE_X_Y setPos = targetPos;

    targetPos.x = setPos.y * sinf(Calculation::GetNotExceedAngle(angle + mfMapAngle));
    targetPos.y = setPos.y * cosf(Calculation::GetNotExceedAngle(angle + mfMapAngle));

    Object_Base_Character *player = Master::mpGameManager->GetObjectManager()->FindByTag_CharacterObject(PLAYER_TAG);

    targetPos.x = (targetPos.x + player->GetObjectPosition().x);
    targetPos.y = (targetPos.y + player->GetObjectPosition().z);

    return targetPos;
}

/*
* @fn DrawMApRate
* @drief マップ拡大率描画用
*/
void StageManagerObject::DrawMapRate(float x1, float y1, float x2, float y2, float r, unsigned int color)
{
    DrawCircle(x1, y1, r, color);
    DrawCircle(x2, y2, r, color);
    DrawBox(x1, y1 - (r * 0.85), x2, y2 + (r * 1.1), color, TRUE);

    float maxRate = mfMaxMagnificationRate - mfMinMagnificationRate;
    float rate = *mfMagnificationRate - mfMinMagnificationRate;

    DrawCircle((x1 * (rate / maxRate)) + (x2 * (1 - (rate / maxRate))), (y1 + y2) * 0.5, r * 1.5, GetColor(0, 0, 0));
    DrawCircle((x1 * (rate / maxRate)) + (x2 * (1 - (rate / maxRate))), (y1 + y2) * 0.5, r * 1.4, color);
}