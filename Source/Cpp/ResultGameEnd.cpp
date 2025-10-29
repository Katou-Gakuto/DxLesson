#include <vector>

#include "DxLib.h"
#include "../Header/CoordinateXY.h"
#include "../Header/DataManager.h"
#include "../Header/Data_Structs.h"
#include "../Header/GameManager.h"
#include "../Header/GraphManager.h"
#include "../Header/MenuManager.h"
#include "../Header/Menu_Base.h"
#include "../Header/ObjectManager.h"
#include "../Header/ObjectTagMacro.h"
#include "../Header/Operation.h"
#include "../Header/ResultGameEnd.h"
#include "../Header/SceneManager.h"
#include "../Header/Scene_Enum.h"

/*
* @fn コンストラクタ
*/
ResultGameEnd::ResultGameEnd()
: Menu_Base(0, XYGet(0.0f, 0.0f), XYGet(0.0f, 0.0f), (Master::mpGameManager->GetSceneManager()->GetNowScene() == SCENE::GAME_CLEAR) ? GetColor(80, 80, 150) : GetColor(0.0f, 0.0f, 0.0f), DX_BLENDMODE_NOBLEND, 255, true, true)
, mnResultHandle(-1)
, mnSelectHandle(-1)
, mnWidth(-1)
, mnHeight(-1)
{
}

/*
* @fn デストラクタ
*/
ResultGameEnd::~ResultGameEnd()
{
}

/*
* @fn Initilize
* @drief 初期化
*/
void ResultGameEnd::MyInitilize()
{
    // 画面サイズ取得
    int colorBit = 0;
    GetScreenState(&mnWidth, &mnHeight, &colorBit);
    msLowerRight.x = mnWidth;
    msLowerRight.y = mnHeight;


    PLAYER_DATA playerData;
    switch (meObjectScene)
    {
    case SCENE::GAME_OVER:
        // ステージマネージャーを削除
        DeleteSetTag(STAGE_MANAGER_TAG, true);

        { // 文字サイズハンドル設定
            mnResultHandle = CreateFontToHandle(NULL, 100, 9);
            mnSelectHandle = CreateFontToHandle(NULL, 30, 5);
        }

        // 選択最大数設定
        mnMaxMenuSelect = static_cast<int>(GAME_OVER::MAX);
        break;

    case SCENE::GAME_CLEAR:
        // ステージマネージャーを削除
        DeleteSetTag(STAGE_MANAGER_TAG, true);

        { // 文字サイズハンドル設定
            mnResultHandle = CreateFontToHandle(NULL, 50, 9);
            mnSelectHandle = CreateFontToHandle(NULL, 30, 5);
            mnPlayerHandle = CreateFontToHandle(NULL, 25, 3);
        }

        // 選択最大数設定
        mnMaxMenuSelect = static_cast<int>(GAME_CLEAR::MAX);

        // プレイヤーデータ取得
        playerData = mpDataManager->GetPlayPlayerData();

        // プレイヤーデータ入力
        {
            for (int i = 0; i < 7; i++) {
                playerData = GetPlayer_ItemPlus(playerData);
            }
            playerData.characterData.position = VGet(0.0f, 0.0f, 0.0f);
            playerData.characterData.angle = 0.0f;
            playerData.characterData.mapType = SCENE::DEFAULT_MAP_ONE;
        }
        mpDataManager->SetPlayPlayerData(playerData);
        mpDataManager->ReSetItem();
        break;

    case SCENE::GAME_NOTHING:
        // ステージマネージャーを削除
        DeleteSetTag(STAGE_MANAGER_TAG, true);

        { // 文字サイズハンドル設定
            mnResultHandle = CreateFontToHandle(NULL, 100, 9);
            mnSelectHandle = CreateFontToHandle(NULL, 30, 5);
        }

        // 選択最大数設定
        mnMaxMenuSelect = static_cast<int>(GAME_NOTHING::MAX);
        break;
    }
}

/*
* @fn Update
* @drief 更新
*/
void ResultGameEnd::MyUpdate()
{
    if (CheckUpKeyAndFrame())
    {
        mnMenuSelect -= 1;
        if (mnMenuSelect < 0) {
            mnMenuSelect = 0;
        }
    }

    if (CheckDownKeyAndFrame())
    {
        mnMenuSelect += 1;


        switch (meObjectScene) 
        {
        case SCENE::GAME_OVER:
            if (mnMenuSelect >= mnMaxMenuSelect) {
                mnMenuSelect = (mnMaxMenuSelect - 1);
            }
            break;

        case SCENE::GAME_CLEAR:
            if (mnMenuSelect >= mnMaxMenuSelect) {
                mnMenuSelect = (mnMaxMenuSelect - 1);
            }
            break;

        case SCENE::GAME_NOTHING:
            if (mnMenuSelect >= mnMaxMenuSelect) {
                mnMenuSelect = (mnMaxMenuSelect - 1);
            }
            break;
        }
    }
    
    CheckDecision_AKeyAndFrame();
}       

/*
* @fn Draw
* @drief 描画
*/
void ResultGameEnd::MyDraw()
{
    switch (meObjectScene) 
    {
        // ゲームオーバー処理
    case SCENE::GAME_OVER:
        DrawStringToHandle((mnWidth / 9), (mnHeight / 6), "GAME OVER", GetColor(255, 255, 255), mnResultHandle);
        DrawStringToHandle((mnWidth / 2.5), (mnHeight / 2) + (mnHeight / 10), "TITLE", mnMenuSelect == 0 ? GetColor(255, 0, 0) : GetColor(255, 255, 255), mnSelectHandle);
        DrawStringToHandle((mnWidth / 2.35), (mnHeight / 2) + (mnHeight / 5), "END", mnMenuSelect == 1 ? GetColor(255, 0, 0) : GetColor(255, 255, 255), mnSelectHandle);
        break;

        // ゲームクリア処理
    case SCENE::GAME_CLEAR:
        DrawClear();
        break;

        // ゲーム無し処理
    case SCENE::GAME_NOTHING:
        DrawStringToHandle((mnWidth / 5), (mnHeight / 6), "NOTHING", GetColor(255, 255, 255), mnResultHandle);
        DrawStringToHandle((mnWidth / 2.5), (mnHeight / 2) + (mnHeight / 10), "TITLE", mnMenuSelect == 0 ? GetColor(255, 0, 0) : GetColor(255, 255, 255), mnSelectHandle);
        DrawStringToHandle((mnWidth / 2.35), (mnHeight / 2) + (mnHeight / 5), "END", mnMenuSelect == 1 ? GetColor(255, 0, 0) : GetColor(255, 255, 255), mnSelectHandle);
        break;
    }
}

/*
* @fn Finalize
* @drief 終了処理
*/
void ResultGameEnd::MyFinalize()
{
    switch (meObjectScene)
    {
    case SCENE::GAME_OVER:
        DeleteFontToHandle(mnResultHandle);
        DeleteFontToHandle(mnSelectHandle);
        break;

    case SCENE::GAME_CLEAR:
        DeleteFontToHandle(mnResultHandle);
        DeleteFontToHandle(mnSelectHandle);
        DeleteFontToHandle(mnPlayerHandle);
        break;

    case SCENE::GAME_NOTHING:
        DeleteFontToHandle(mnResultHandle);
        DeleteFontToHandle(mnSelectHandle);
        break;

    }
}

/*
* @fn SelectDecision
* @drief 選択決定時処理
*/
void ResultGameEnd::SelectDecision()
{
    switch (meObjectScene) 
    {
        // ゲームオーバー処理
    case SCENE::GAME_OVER:
        switch (static_cast<GAME_OVER>(mnMenuSelect))
        {
        case GAME_OVER::RE_START:
            Master::mpGameManager->GetSceneManager()->SetNextScene(SCENE::TITLE);
            Master::mpGameManager->GetMenuManager()->DecreaseMenuNumber();
            break;

        case GAME_OVER::END:
            Master::mpGameManager->SetEndFlag(true);
            break;
        }
        break;

        // ゲームクリア処理
    case SCENE::GAME_CLEAR:
        switch (static_cast<GAME_CLEAR>(mnMenuSelect))
        {
        case GAME_CLEAR::RE_START:
            Master::mpGameManager->GetSceneManager()->SetNextScene(SCENE::DEFAULT_MAP_ONE);
            Master::mpGameManager->GetMenuManager()->DecreaseMenuNumber();
            break;

        case GAME_CLEAR::END:
            Master::mpGameManager->SetEndFlag(true);
            break;
        }
        break;

        // ゲーム無し処理
    case SCENE::GAME_NOTHING:
        switch (static_cast<GAME_NOTHING>(mnMenuSelect))
        {
        case GAME_NOTHING::RE_START:
            Master::mpGameManager->GetSceneManager()->SetNextScene(SCENE::TITLE);
            Master::mpGameManager->GetMenuManager()->DecreaseMenuNumber();
            break;

        case GAME_NOTHING::END:
            Master::mpGameManager->SetEndFlag(true);
            break;
        }
        break;
    }
}

/*
* @fn GetPlayer_ItemPlus
* @drief アイテムを取得したデータを返す
*/
PLAYER_DATA ResultGameEnd::GetPlayer_ItemPlus(PLAYER_DATA playerData)
{
    ITEM_DATA item;
    item.possessionCount = 1;
    item.templateData.typeNumber = (int)ItemType::RECOVERY_MEDICIN_LARGE;// "RecoveryMedicine(Large)";
    item.itemPhotoFileName = "Resource/2D/RecoveryMedicine(Large).png";
    item.templateData.name = "LargeMedicine";

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

    return playerData;
}

/*
* @fn DrawClear
* @drief クリア画面描画用
*/
void ResultGameEnd::DrawClear()
{
    // リザルト文字
    DrawBoxAA(0, 0, (GetScreenSize().x / 10) * 2.15, (GetScreenSize().y / 10) * 1.05, GetColor(0, 0, 0), TRUE);
    DrawBoxAA((GetScreenSize().x / 10) * 0.05, (GetScreenSize().y / 10) * 0.05, (GetScreenSize().x / 10) * 2.1, (GetScreenSize().y / 10) * 1, GetColor(255, 255, 255), TRUE);
    DrawStringToHandle((GetScreenSize().x / 10) * 0.05, (GetScreenSize().y / 10) * 0.05, "CLEAR", GetColor(0, 0, 0), mnResultHandle);

    // 選択文字
    DrawBoxAA(0,                               (GetScreenSize().y / 10) * 1.2, (GetScreenSize().x / 10) * 1.55, (GetScreenSize().y / 10) * 3.2, GetColor(0, 0, 0), TRUE);
    DrawBoxAA((GetScreenSize().x / 10) * 0.05, (GetScreenSize().y / 10) * 1.25, (GetScreenSize().x / 10) * 1.5, (GetScreenSize().y / 10) * 3.15, GetColor(255, 255, 255), TRUE);
    DrawBoxAA(0,                               (GetScreenSize().y / 10) * 1.2, (GetScreenSize().x / 10) * 1.05, (GetScreenSize().y / 10) * 1.9, GetColor(0, 0, 0), TRUE);
    DrawBoxAA((GetScreenSize().x / 10) * 0.05, (GetScreenSize().y / 10) * 1.25, (GetScreenSize().x / 10) * 1.0, (GetScreenSize().y / 10) * 1.85, GetColor(255, 255, 255), TRUE);
    DrawStringToHandle((GetScreenSize().x / 10) * 0.05, (GetScreenSize().y / 10) * 1.25, "NEXT", GetColor(0, 0, 0), mnSelectHandle);
    DrawStringToHandle((GetScreenSize().x / 10) * 0.05, (GetScreenSize().y / 10) * 1.95, "STAGER", (mnMenuSelect == 0) ? GetColor(255, 0, 0) : GetColor(0, 0, 0), mnSelectHandle);
    DrawStringToHandle((GetScreenSize().x / 10) * 0.05, (GetScreenSize().y / 10) * 2.55, "END", (mnMenuSelect == 1) ? GetColor(255, 0, 0): GetColor(0, 0, 0), mnSelectHandle);

    // ステータス描画用
    DrawBoxAA((GetScreenSize().x / 10) * 3.85, 0, GetScreenSize().x, (GetScreenSize().y / 10) * 4.05, GetColor(255, 255, 255), TRUE);
    DrawBoxAA((GetScreenSize().x / 10) * 3.9, (GetScreenSize().y / 10) * 0.05, (GetScreenSize().x / 10) * 9.95, (GetScreenSize().y / 10) * 4, GetColor(0, 0, 0), TRUE);

    // ゲットしたアイテム表示用土台
    DrawBoxAA(0, (GetScreenSize().y / 10) * 4.75, (GetScreenSize().x / 10) * 4.55, GetScreenSize().y, GetColor(255, 255, 255), TRUE);
    DrawBoxAA((GetScreenSize().x / 10) * 0.05, (GetScreenSize().y / 10) * 4.8, (GetScreenSize().x / 10) * 4.5, (GetScreenSize().y / 10) * 9.95, GetColor(50, 50, 50), TRUE);

    // ゲットアイテム文字
    DrawBox((GetScreenSize().x / 10) * 0.1, (GetScreenSize().y / 10) * 4.25, (GetScreenSize().x / 10) * 1.95, (GetScreenSize().y / 10) * 4.95, GetColor(0, 0, 0), TRUE);
    DrawBox((GetScreenSize().x / 10) * 0.15, (GetScreenSize().y / 10) * 4.3, (GetScreenSize().x / 10) * 1.9, (GetScreenSize().y / 10) * 4.9, GetColor(255, 255, 255), TRUE);

    // ステージ文字
    //DrawBoxAA((GetScreenSize().x / 10) * 7.95, (GetScreenSize().y / 10) * 9.15, GetScreenSize().x, GetScreenSize().y, GetColor(0, 0, 0), TRUE);
    //DrawBoxAA((GetScreenSize().x / 10) * 8, (GetScreenSize().y / 10) * 9.2, (GetScreenSize().x / 10) * 9.95, (GetScreenSize().y / 10) * 9.95, GetColor(255, 255, 255), TRUE);


    //        DrawStringToHandle((mnWidth / 1.3), (mnHeight / 1.2), "\"A\"STAGE", mnMenuSelect == 0 ? GetColor(255, 0, 0) : GetColor(255, 255, 255), mnSelectHandle);
    ///////////DrawStringToHandle((GetScreenSize().x / 10) * 8, (GetScreenSize().y / 10) * 9.3, "\"A\"STAGE", GetColor(255, 0, 0), mnSelectHandle);
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
    DrawBoxAA((GetScreenSize().x / 10) * 5.45, (GetScreenSize().y / 10) * 4.45, (GetScreenSize().x / 10) * 9.55, (GetScreenSize().y / 10) * 9.55, GetColor(255, 255, 255), TRUE);
    DrawExtendGraph((GetScreenSize().x / 10) * 5.5, (GetScreenSize().y / 10) * 4.5, (GetScreenSize().x / 10) * 9.5, (GetScreenSize().y / 10) * 9.5, mnDrawPlayerPictureHandle[mpSceneManager->GetPlayerDataNumber()], FALSE);
}