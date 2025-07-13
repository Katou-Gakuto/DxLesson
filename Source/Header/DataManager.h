#pragma once

#include <fstream>
#include <vector>

#include "../Header/CharacterType_Enum.h"
#include "../Header/DataManagerMacro.h"
#include "../Header/Data_Structs.h"
#include "../Header/Item_Base.h"
#include "../Header/Scene_Enum.h"

class DataManager 
{
private:
    bool mbFailureFlag; // ファイルオープン失敗フラグ

    //PLAYER_DATA msPlayerData[PLAYER_DATA_NUMBER];   // プレイヤーデータ

    //std::vector<DATA_STRUCT> msEnemyData;   // エネミーデータ
    OnePlayerAllData msBaseDatas; //ファイルネームデータ保存用
    std::vector<DATA_NAME> msPlayerFileNameData; //プレイヤーファイルネームデータ保存用
    
    std::vector<Item_Base *> mpItem;    // アイテム

    LEVEL_DATA mslevelData; // レベルデータ

    OnePlayerAllData msPlayerData[PLAYER_DATA_NUMBER];

public:
    DataManager();  // コンストラクタ
    ~DataManager(); // デストラクタ

    void Initilize();   // 初期化

    void SetAllData(const char* fileName);  // 全データ設定
    std::vector<OneData> GetAllDatas(std::string dataNames);    // 指定されているファイルにあるデータを返す
    template <typename dataTemplate>
    dataTemplate GetFileData(std::string typeName, const char* fileName);
    OneData GetNotPlayer_OneData(std::string fileTypeName, std::string fileName, bool *playerDataFlag);   // ファイルのタイプに合ったデータに入力を返す
    std::vector<int> CheckDataType(std::string checkTypeName, std::vector<OneData> detas);   // 指定のタイプが何個目にあるかを返す

    bool GetFailureFlag() { return mbFailureFlag; } // ファイルオープン失敗フラグ取得

    void Delete_OneFile(const char *fileName, const char *fileTypeName);    // ファイル削除

    std::string GetFileName_FileType(const char *fileType, std::vector<DATA_NAME> fileNameData);                // 指定されたファイルの中から指定のファイルタイプのファイル名を一つ返す
    std::vector<std::string>GetFileNames_FileType(const char *fileType, std::vector<DATA_NAME> fileNameData);  // 指定されたファイルの中から指定のファイルタイプのファイル名を全て返す

    DATA_NAME GetFileName_SceneType(SCENE scene);               // 指定されたシーンで生成されるファイルデータを一つ返す
    std::vector<DATA_NAME>GetFileNames_SceneType(SCENE scene); // 指定されたシーンで生成されるファイルデータを全て返す

    std::vector<DATA_NAME> GetBaseData_FileName() { return msBaseDatas.oneDatas[0].fileNameDatas; }    // 基本データ名全取得

    void Init_PlayerFileName_And_Item(int playerNumber);    // プレイヤー用ファイルの名前とアイテム情報取得

// ファイル名用メンバ関数
        DATA_NAME GetFileNameInitializationData();    // 初期化されたファイル名データ
 
        SCENE GetSceneType(std::string sceneType);    // 文字列をシーンタイプのenumに変換する

        void SetFile_FileNameData(std::ofstream * file, DATA_NAME nameData); // ファイル名用　ファイル情報　書き込み処理
        DATA_NAME GetFile_fileNameData(std::ifstream * file);    // ファイル名用　ファイル情報　読み取り処理

        void SetBaseAllData(std::string fileName);     // 基本データを全取得
        void AddFile_FileNameData(std::string fileName, DATA_NAME dataName);     // ファイル名データを追加
        void DeleteFile_FileNameData(std::string fileName, std::string deleteFileName, const char *deleteFileTypeName);  // ファイル名データを削除

        std::vector<DATA_NAME> GetFile_fileNameDatas(std::string fileName); // ファイル名取得
//


// プレイヤー用メンバ関数
        void SetFile_PlayerFileData(std::ofstream *file, PLAYER_DATA playerData);   // プレイヤー用　ファイル情報　書き込み処理
        PLAYER_DATA GetData_PlayerFileData(std::ifstream *file);    // プレイヤー用　ファイル情報読み取り

        std::vector<PLAYER_DATA> GetFile_PlayerFileDatas(std::string fileName);   // ファイルからプレイヤーデータを複数取得

        void SetPlayerData(std::string fileName);   // メンバプレイヤーデータに保存
        PLAYER_DATA GetPlayerData(int index) { return msPlayerData[index].playerData; }    // プレイヤーデータ取得
        void Set_MyPlayerData(int index, PLAYER_DATA playerData) { msPlayerData[index].playerData = playerData; }  // メンバプレイヤーデータ設定
        std::string GetPlayerFilePos(std::string fileName, int number) { return (msPlayerData[number].playerData.playerFolderName + fileName); }   // プレイヤーファイル位置取得

        void SetFile_PlayerFileNameDatas(std::string fileName);    // プレイヤー用ファイルネームデータを設定
        std::vector<DATA_NAME>GetFile_PlayerFileNameDatas() { return msPlayerFileNameData; }    // 設定されたプレイヤー用ファイル名データを取得

        void ChangeFile_PlayerFileData(std::string fileName, std::string playerName, PLAYER_DATA playerData);   // プレイヤーデータ変更

        void SetItems(int playerNumber);    // アイテムセット
        void DeleteItem(std::string itemName);  // アイテム削除
        std::vector<Item_Base *> GetItems() { return mpItem; }  // 生成されているアイテム取得
//

// キャラクター用メンバ関数    
        void SetFile_CharacterFileData(std::ofstream * file, CHARACTER_DATA characterData);    // キャラクター用 ファイル情報 書き込み処理
        CHARACTER_DATA GetFile_CharacterFileData(std::ifstream * file);    // キャラクター用 ファイル情報 読み取り処理

        CHARACTER_DATA GetCharacterInitializationData();    // 初期化されたキャラクターデータ

        std::vector<CHARACTER_DATA> GetData_CharacterFileDatas(std::string fileName);   // キャラクター用　ファイル内全キャラクター情報　取得

        void AddCharacterFile(std::string fileName, CHARACTER_DATA characterData);        // キャラクター用ファイル追加
        void AddFile_CharacterFileData(std::string fileName, CHARACTER_DATA characterData);    // キャラクター用ファイル情報追加

        void DeleteFile_CharacterFileData(std::string fileName, std::string characterName); // キャラクター用ファイル情報削除

        void ChangeFile_CharacterFileData(std::string fileName, std::string characterName, CHARACTER_DATA characterData); // キャラクター用ファイル内容一部変更

        std::string GetCharacterNameStr(CHARACTER_TYPE characterType);  // キャラクタータイプ文字列変換
        CHARACTER_TYPE GetCharacterNameEnumClass(std::string characterType);    // キャラクタータイプenum変換
//

// マップ用メンバ関数
        std::vector<MAP_DATA> GetData_MapFile(std::string fileName);  // マップファイルを取得
//

// レベル用メンバ関数
        void SetLevelData(std::string fileName);    // レベル情報取得
        LEVEL_DATA GetLevelData() { return mslevelData; }   // レベル情報取得
//

        // 数　変換用
        int GetCharacterNameMaxNumber();    // キャラクタータイプ最大数
        std::string GetCharacterName_Number(int number);    // キャラクタータイプ名取得

    void SetTestFileData(const char *fileName); // データを設定
    /*
    void CheckData();
    */
};