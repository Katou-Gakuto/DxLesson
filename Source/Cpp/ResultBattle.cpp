#include "DxLib.h"
#include "../Header/CoordinateXY.h"
#include "../Header/DataManager.h"
#include "../Header/Data_Structs.h"
#include "../Header/GameManager.h"
#include "../Header/GraphManager.h"
#include "../Header/Menu_Base.h"
#include "../Header/ObjectManager.h"
#include "../Header/ObjectTagMacro.h"
#include "../Header/Operation.h"
#include "../Header/SceneManager.h"
#include "../Header/ResultBattle.h"

/*
* @fn コンストラクタ
*/
ResultBattle::ResultBattle()
: Menu_Base(ResultBattle::MAX, XYGet(0.0f, 0.0f), XYGet(0.0f, 0.0f), GetColor(80, 80, 150), DX_BLENDMODE_NOBLEND, 255, false, true)
, mnResultHandle(-1)
, mnSelectHandle(-1)
, mnPlayerHandle(-1)
, mnWidth(-1)
, mnHeight(-1)
{
    msPlusItem.clear();
}

/*
* @fn デストラクタ
*/
ResultBattle::~ResultBattle()
{
}

/*
* @fn Initilize
* @drief 初期化処理
*/
void ResultBattle::MyInitilize()
{
    // 画面サイズ取得
    int colorBit = 0;
    GetScreenState(&mnWidth, &mnHeight, &colorBit);
    msLowerRight.x = mnWidth;
    msLowerRight.y = mnHeight;

    { // 文字サイズハンドル設定
        mnResultHandle = CreateFontToHandle(NULL, 50, 9);
        mnSelectHandle = CreateFontToHandle(NULL, 30, 5);
        mnPlayerHandle = CreateFontToHandle(NULL, 25, 3);
    }

    // アイテム入手処理
    {
        PLAYER_DATA playerData = mpDataManager->GetPlayPlayerData();
        int setRandNumber = GetRand(3);

        for (int i = 0; i < setRandNumber; i++) {
            playerData = GetPlayer_PlusNewItem(playerData);
        }

        mpDataManager->SetPlayPlayerData(playerData);
    }

    //// プレイヤーデータ変更
    //mpDataManager->ChangeFile_PlayerFileData(mpDataManager->GetFileName_FileType(PLAYER_FILE_NAME, mpDataManager->GetBaseData_FileName()),
    //    mpDataManager->GetPlayerData(mpSceneManager->GetPlayerDataNumber()).characterData.templateData.name,
    //    mpDataManager->GetPlayerData(mpSceneManager->GetPlayerDataNumber()));

    //// アイテム設定
    //mpDataManager->Init_PlayerFileName_And_Item(mpSceneManager->GetPlayerDataNumber());
}

/*
* @fn Updete
* @drief 更新処理
*/
void ResultBattle::MyUpdate()
{
    //DefaultMenuSelectUpdate();
    CheckDecision_AKeyAndFrame();

  /*  if (Operation::CheckUpKey()) {
        mnSelectNumber -= 1;
        if (mnSelectNumber < 0) {
            mnSelectNumber = 0;
        }
    }

    if (Operation::CheckDownKey()) {
        mnSelectNumber += 1;
        if (mnSelectNumber >= ResultBattle::MAX) {
            mnSelectNumber = (ResultBattle::MAX - 1);
        }
    }

    if (Operation::CheckAKey()) {
        SelectDecision();
    }*/
}

/*
* @fn Draw
* @drief 描画処理
*/
void ResultBattle::MyDraw()
{
    // リザルト文字
    DrawBoxAA(0,                            0,                                  (GetScreenSize().x / 10) * 2.55, (GetScreenSize().y / 10) * 1.05, GetColor(0, 0, 0), TRUE);
    DrawBoxAA((GetScreenSize().x / 10) * 0.05, (GetScreenSize().y / 10) * 0.05, (GetScreenSize().x / 10) * 2.5,  (GetScreenSize().y / 10) * 1, GetColor(255, 255, 255), TRUE);

    // ステータス描画用
    DrawBoxAA((GetScreenSize().x / 10) * 3.85, 0,                               GetScreenSize().x,                (GetScreenSize().y / 10) * 4.05, GetColor(255, 255, 255), TRUE);
    DrawBoxAA((GetScreenSize().x / 10) * 3.9,  (GetScreenSize().y / 10) * 0.05, (GetScreenSize().x / 10) * 9.95,  (GetScreenSize().y / 10) * 4, GetColor(0, 0, 0), TRUE);

    // ゲットしたアイテム表示用土台
    DrawBoxAA(0,                               (GetScreenSize().y / 10) * 4.75, (GetScreenSize().x / 10) * 4.55,   GetScreenSize().y, GetColor(255, 255, 255), TRUE);
    DrawBoxAA((GetScreenSize().x / 10) * 0.05, (GetScreenSize().y / 10) * 4.8,  (GetScreenSize().x / 10) * 4.5,   (GetScreenSize().y / 10) * 9.95,  GetColor(50, 50, 50), TRUE);

    // ゲットアイテム文字
    DrawBox((GetScreenSize().x / 10) * 0.1, (GetScreenSize().y / 10) * 4.25, (GetScreenSize().x / 10) * 1.95, (GetScreenSize().y / 10) * 4.95, GetColor(0, 0, 0), TRUE);
    DrawBox((GetScreenSize().x / 10) * 0.15, (GetScreenSize().y / 10) * 4.3, (GetScreenSize().x / 10) * 1.9, (GetScreenSize().y / 10) * 4.9, GetColor(255, 255, 255), TRUE);

    // ステージ文字
    DrawBoxAA((GetScreenSize().x / 10) * 7.95, (GetScreenSize().y / 10) * 9.15, GetScreenSize().x, GetScreenSize().y, GetColor(0, 0, 0), TRUE);
    DrawBoxAA((GetScreenSize().x / 10) * 8,   (GetScreenSize().y / 10) * 9.2, (GetScreenSize().x / 10) * 9.95, (GetScreenSize().y / 10) * 9.95, GetColor(255, 255, 255), TRUE);

    DrawStringToHandle((GetScreenSize().x / 10) * 0.05, (GetScreenSize().y / 10) * 0.05, "RESULT", GetColor(0, 0, 0), mnResultHandle);

    //        DrawStringToHandle((mnWidth / 1.3), (mnHeight / 1.2), "\"A\"STAGE", mnMenuSelect == 0 ? GetColor(255, 0, 0) : GetColor(255, 255, 255), mnSelectHandle);
    DrawStringToHandle((GetScreenSize().x / 10) * 8, (GetScreenSize().y / 10) * 9.3, "\"A\"STAGE", GetColor(255, 0, 0), mnSelectHandle);
    //DrawStringToHandle((mnWidth / 1.3), (mnHeight / 1.1), "IN DETAIL", mnMenuSelect == 1 ? GetColor(255, 0, 0) : GetColor(255, 255, 255), mnSelectHandle);

    PLAYER_DATA playerData = mpDataManager->GetPlayPlayerData();
    PLAYER_DATA oldPlayerData = mpSceneManager->GetOldPlayerData();
    bool statusUpFlag[6];

    statusUpFlag[0] = (playerData.characterData.status.level > oldPlayerData.characterData.status.level);
    statusUpFlag[1] = ((playerData.characterData.status.exp > oldPlayerData.characterData.status.exp) || (statusUpFlag[0]));
    statusUpFlag[2] = (playerData.characterData.status.attackPower > oldPlayerData.characterData.status.attackPower);
    statusUpFlag[3] = (playerData.characterData.status.maxHp > oldPlayerData.characterData.status.maxHp);
    statusUpFlag[4] = (playerData.characterData.status.defense > oldPlayerData.characterData.status.defense);
    statusUpFlag[5] = (playerData.characterData.status.speed > oldPlayerData.characterData.status.speed);

    for (int i = 0; i < 6; i++) {
        if (statusUpFlag[i]) {
            DrawBoxAA((GetScreenSize().x / 10) * 3.41, (GetScreenSize().y / 10) * (0.62 + (i * 0.5)), (GetScreenSize().x / 10) * 3.78, (GetScreenSize().y / 10) * (1.03 + (i * 0.5)), GetColor(0, 0, 0), TRUE);
            DrawBoxAA((GetScreenSize().x / 10) * 3.44, (GetScreenSize().y / 10) * (0.65 + (i * 0.5)), (GetScreenSize().x / 10) * 3.75, (GetScreenSize().y / 10) * (1 + (i * 0.5)), GetColor(255, 255, 255), TRUE);
            DrawString((GetScreenSize().x / 10) * 3.47, (GetScreenSize().y / 10) * (0.67 + (i * 0.5)), "UP", GetColor(255, 0, 0));
        }
    }

    DrawFormatStringToHandle((GetScreenSize().x / 10) * 3.95, (GetScreenSize().y / 10) * 0.1, GetColor(255, 255, 255), mnPlayerHandle, "NAME   :%s", playerData.characterData.templateData.name.c_str());
    if (statusUpFlag[0]) {  // レベル
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 3.95, (GetScreenSize().y / 10) * 0.6, GetColor(255, 255, 255), mnPlayerHandle, "LEVEL  :%d → %d", oldPlayerData.characterData.status.level, playerData.characterData.status.level);
    }
    else {
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 3.95, (GetScreenSize().y / 10) * 0.6, GetColor(255, 255, 255), mnPlayerHandle, "LEVEL  :%d", playerData.characterData.status.level);
    }
    if (statusUpFlag[1]) {  // 経験値
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 3.95, (GetScreenSize().y / 10) * 1.1, GetColor(255, 255, 255), mnPlayerHandle, "EXP    :%d → %d", oldPlayerData.characterData.status.exp, playerData.characterData.status.exp);
    }
    else {
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 3.95, (GetScreenSize().y / 10) * 1.1, GetColor(255, 255, 255), mnPlayerHandle, "EXP    :%d", playerData.characterData.status.exp);
    }
    if (statusUpFlag[2]) {  // 攻撃力
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 3.95, (GetScreenSize().y / 10) * 1.6, GetColor(255, 255, 255), mnPlayerHandle, "ATTACK :%d → %d", oldPlayerData.characterData.status.attackPower, playerData.characterData.status.attackPower);
    }
    else {
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 3.95, (GetScreenSize().y / 10) * 1.6, GetColor(255, 255, 255), mnPlayerHandle, "ATTACK :%d", playerData.characterData.status.attackPower);
    }
    if (statusUpFlag[3]) {  // HP
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 3.95, (GetScreenSize().y / 10) * 2.1, GetColor(255, 255, 255), mnPlayerHandle, "MAX HP :%d → %d", oldPlayerData.characterData.status.maxHp, playerData.characterData.status.maxHp);
    }
    else {
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 3.95, (GetScreenSize().y / 10) * 2.1, GetColor(255, 255, 255), mnPlayerHandle, "MAX HP :%d", playerData.characterData.status.hp);
    }
    if (statusUpFlag[4]) {  // 防御力
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 3.95, (GetScreenSize().y / 10) * 2.6, GetColor(255, 255, 255), mnPlayerHandle, "DEFENSE:%d → %d", oldPlayerData.characterData.status.defense, playerData.characterData.status.defense);
    }
    else {
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 3.95, (GetScreenSize().y / 10) * 2.6, GetColor(255, 255, 255), mnPlayerHandle, "DEFENSE:%d", playerData.characterData.status.defense);
    }
    if (statusUpFlag[5]) {  // 速度
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 3.95, (GetScreenSize().y / 10) * 3.1, GetColor(255, 255, 255), mnPlayerHandle, "SPEED  :%d → %d", oldPlayerData.characterData.status.speed, playerData.characterData.status.speed);
    }
    else {
        DrawFormatStringToHandle((GetScreenSize().x / 10) * 3.95, (GetScreenSize().y / 10) * 3.1, GetColor(255, 255, 255), mnPlayerHandle, "SPEED  :%d", playerData.characterData.status.speed);
    }

    // アイテム
    DrawStringToHandle((GetScreenSize().x / 10) * 0.2, (GetScreenSize().y / 10) * 4.35, "GET ITEM", GetColor(0, 0, 0), mnPlayerHandle);
    for (int i = 0; i < msPlusItem.size(); i++) {
        DrawBoxAA((GetScreenSize().x / 10) * 0.1, (GetScreenSize().y / 10) * ((i * 0.7) + 5), ((GetScreenSize().x / 10) * 0.1) + (GetScreenSize().y / 10) * 0.7, (GetScreenSize().y / 10) * (((i + 1) * 0.7) + 4.95), GetColor(255, 255, 255), TRUE);
        DrawExtendGraph((GetScreenSize().x / 10) * 0.1, (GetScreenSize().y / 10) * ((i * 0.7) + 5), ((GetScreenSize().x / 10) * 0.1) + ((GetScreenSize().y / 10) * 0.7), (GetScreenSize().y / 10) * (((i + 1) * 0.7) + 4.95), mnItemHandle[i], TRUE);
        DrawFormatStringToHandle(((GetScreenSize().x / 10) * 0.2) + ((GetScreenSize().y / 10) * 0.7), (GetScreenSize().y / 10) * ((i * 0.7) + 5.1), GetColor(255, 255, 255), mnPlayerHandle, "%s", msPlusItem[i].templateData.name.c_str());
    }

    // プレイヤー画像
    DrawBoxAA((GetScreenSize().x / 10) * 5.45, (GetScreenSize().y / 10) * 4.45, (GetScreenSize().x / 10) * 9.55, (GetScreenSize().y / 10) * 8.95, GetColor(255, 255, 255), TRUE);
    DrawExtendGraph((GetScreenSize().x / 10) * 5.5, (GetScreenSize().y / 10) * 4.5, (GetScreenSize().x / 10) * 9.5, (GetScreenSize().y / 10) * 8.9, mnDrawPlayerPictureHandle[mpSceneManager->GetPlayerDataNumber()], FALSE);
}

/*
* @fn Finalize
* @drief 終了処理
*/
void ResultBattle::MyFinalize()
{
    DeleteFontToHandle(mnResultHandle);
    DeleteFontToHandle(mnSelectHandle);
    DeleteFontToHandle(mnPlayerHandle);
}

/*
* @fn SelectDecision
* @drief 選択決定時処理
*/
void ResultBattle::SelectDecision()
{
    //switch (mnMenuSelect)
    //{
    //case ResultBattle::MAP:
 

    // マップにシーン移動
    mpSceneManager->SetNextScene(mpDataManager->GetPlayPlayerData().characterData.mapType);

    //    break;

    //}
}

/*
* @fn GetPlayer_PlusNewItem
* @drief アイテムを追加したプレイヤーデータを取得
*/
PLAYER_DATA ResultBattle::GetPlayer_PlusNewItem(PLAYER_DATA playerData)
{
    int getItemNumber = GetRand(10);
    ITEM_DATA item;
    item.possessionCount = 1;


    switch (getItemNumber)
    {
    case 0:
        item.possessionCount = 0;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        item.templateData.typeNumber = (int)ItemType::RECOVERY_MEDICIN_SMALL;//"RecoveryMedicine(Small)";
        item.itemPhotoFileName = "Resource/2D/RecoveryMedicine(Small).png";
        item.templateData.name = "SmallMedicine";
        break;
    case 7:
    case 8:
    case 9:
        item.templateData.typeNumber = (int)ItemType::RECOVERY_MEDICIN_MEDIUM;//""RecoveryMedicine(Medium)";
        item.itemPhotoFileName = "Resource/2D/RecoveryMedicine(Medium).png";
        item.templateData.name = "MediumMedicine";
        break;
    case 10:
        item.templateData.typeNumber = (int)ItemType::RECOVERY_MEDICIN_LARGE;//""RecoveryMedicine(Large)";
        item.itemPhotoFileName = "Resource/2D/RecoveryMedicine(Large).png";
        item.templateData.name = "LargeMedicine";
        break;
    }

    if (item.possessionCount > 0) {

        bool flag = false;
        for (int i = 0; i < playerData.itemNumber && (!flag); i++) {
            if (playerData.itemData[i].templateData.name == item.templateData.name) {
                if (playerData.itemData[i].possessionCount < 999) {
                    // 追加
                    playerData.itemData[i].possessionCount += 1;
                    msPlusItem.push_back(item);
                    mnItemHandle.push_back(Master::mpGameManager->GerGraphManager()->GetGraphNumber(item.itemPhotoFileName.c_str(), true));
                }
                flag = true;
            }
        }

        // 持っていなら新しく追加
        if (!flag) {
            playerData.itemNumber += 1;
            playerData.itemData.push_back(item);
            msPlusItem.push_back(item);
            mnItemHandle.push_back(Master::mpGameManager->GerGraphManager()->GetGraphNumber(item.itemPhotoFileName.c_str(), true));
        }
    }

    return playerData;
}