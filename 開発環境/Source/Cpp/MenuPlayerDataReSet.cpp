#include <string>
#include <vector>

#include "DxLib.h"
#include "../Header/CoordinateXY.h"
#include "../Header/DataManager.h"
#include "../Header/DataManagerMacro.h"
#include "../Header/Data_Structs.h"
#include "../Header/GameManager.h"
#include "../Header/MenuCheck.h"
#include "../Header/MenuPlayerDataReSet.h"
#include "../Header/Menu_Base.h"
#include "../Header/Operation.h"

/*
* @fn コンストラクタ
*/
MenuPlayerDataReSet::MenuPlayerDataReSet()
: Menu_Base(3, XYGet(0, 0), IntXY_Change_FloatXY(GetScreenSize()), GetColor(40, 140, 240), DX_BLENDMODE_NOBLEND, 255, false, true)
{
}

/*
* @fn デストラクタ
*/
MenuPlayerDataReSet::~MenuPlayerDataReSet()
{
}

/*
* @fn MyInitilize
* @drief 個別初期化処理
*/
void MenuPlayerDataReSet::MyInitilize()
{
}

/*
* @fn MyFinalize
* @drief 個別終了処理
*/
void MenuPlayerDataReSet::MyFinalize()
{
}

/*
* @fn MyUpdate
* @drief 個別更新処理
*/
void MenuPlayerDataReSet::MyUpdate()
{
    DefaultMenuSelectUpdate();

    // 閉じる
    if (Operation::CheckBKey() && CheckFrame(1)) {
        SetDeleteFlag(true);
    }
}

/*
* @fn MyDraw
* @drief 個別描画化処理
*/
void MenuPlayerDataReSet::MyDraw()
{
    // プレイヤーデータ描画
    DrawPlayerDatas();

    // リセット文字描画
    DrawBoxAA(0, 0, (GetScreenSize().x / 10) * 0.9, (GetScreenSize().y / 10) * 0.9, GetColor(255, 255, 255), TRUE);
    DrawString((GetScreenSize().x / 10) * 0.1, (GetScreenSize().y / 10) * 0.1, "DATA\nRESET", GetColor(0, 0, 0));

    // 戻る操作文字描画
    DrawBoxAA(0, (GetScreenSize().y / 10) * 9.5, (GetScreenSize().x / 10) * 1.5, GetScreenSize().y, GetColor(255, 255, 255), TRUE);
    DrawString((GetScreenSize().x / 10) * 0.1, (GetScreenSize().y / 10) * 9.6, "\"B\"BACK", GetColor(0, 0, 0));
}

/*
* @fn SelectDecision
* @drief 選択決定時処理
*/
void MenuPlayerDataReSet::SelectDecision()
{
    MenuCheck *menuCheck = new MenuCheck(*this, &MenuPlayerDataReSet::SetCheckMenu_0, this);
    menuCheck->Initilize();
//    std::vector<DATA_NAME> fileNames = mpDataManager->GetBaseData_FileName();
//    DATA_NAME setFileName;
//    bool flag = false;
//    for (int i = 0; i < fileNames.size(); i++) {
//        if (fileNames[i].fileTypeName == PLAYER_INIT_DATA_FILE_NAME) {
//            setFileName = fileNames[i];
//            flag = true;
//            break;
//        }
//    }
//
//    if (flag) {
//        PLAYER_DATA changePlayer = mpDataManager->GetFile_PlayerFileDatas(setFileName.fileName)[0];
//
//        std::string playerNumber;
//        switch (mnMenuSelect) 
//        {
//        case 0:
//            playerNumber = "0";
//            break;
//        case 1:
//            playerNumber = "1";
//            break;
//        case 2:
//            playerNumber = "2";
//            break;
//        }
//        changePlayer.playerFolderName = (changePlayer.playerFolderName + playerNumber);
//
//        // プレイヤーデータ変更
//        mpDataManager->ChangeFile_PlayerFileData(mpDataManager->GetFileName_FileType(PLAYER_FILE_NAME, mpDataManager->GetBaseData_FileName()),
//                                                 mpDataManager->GetPlayerData(mnMenuSelect).characterData.templateData.name,
//                                                 changePlayer);
//
//        // プレイヤーファイルデータ削除
//        std::vector<DATA_NAME> deleteFile = mpDataManager->GetFile_fileNameDatas(changePlayer.playerFolderName + "/FileNames_Data.txt");
//        for (int i = 0; i < deleteFile.size(); i++) {
//            mpDataManager->DeleteFile_FileNameData(changePlayer.playerFolderName + "/FileNames_Data.txt", deleteFile[i].fileName, deleteFile[i].fileTypeName.c_str());
//            mpDataManager->Delete_OneFile(deleteFile[i].fileName.c_str(), deleteFile[i].fileTypeName.c_str());
//        }
//
//        mpDataManager->Initilize();
//    }
}

/*
* @fn SetOverride_CheckMenuProcess
* @drief チェック用関数(データリセット用)
*/
void MenuPlayerDataReSet::SetOverride_CheckMenuProcess()
{
    mpDataManager->PlayDataDelete(mnMenuSelect);
}