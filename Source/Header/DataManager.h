#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

#include "Data_Structs.h"
#include "Scene_Enum.h"

class DataManager
{
private:
	// プレイ中のプレイヤーデータ
	OnePlayerAllData mstPlayPlayerData;
	// プレイ中のセーブ番号
	int mnPlayPlayerDataNumber;

	// ベースのデータ
	OnePlayerAllData mstBaseData;

	// 初期化用プレイヤーデータ
	std::vector<PLAYER_DATA> mstInitPlayerDatas;

	// 選択用プレイヤー
	std::vector<PLAYER_DATA> mstPlayerDatas;
	// 全プレイヤーデータファイル名
	std::string mstrPlayerDatasFileName;

	// 取得済みデータ場所保存用
	std::map<SCENE, std::list<int>> mmGetFilePosNumbers;

	std::list<std::string> msDeleteItemName;

	// 失敗フラグ
	bool mbFailureFlag;

public:
	// コンストラクタ
	DataManager(std::string startFileName);
	// デストラクタ
	~DataManager();

	// 初期化
	void Init(std::string startFileName);
	// データを保存
	void Save();

	// プレイヤーデータを取得
	std::vector<PLAYER_DATA> GetPlayerData() { return mstPlayerDatas; }
	// プレイヤーデータ設定
	void ChangePlayerData(PLAYER_DATA data, int playerNumber);

	// プレイヤー設定
	void SetPlayPlayer(int playerNumber);
	// プレイプレイヤーデータを取得
	PLAYER_DATA GetPlayPlayerData();
	// プレイプレイヤーデータ設定
	void SetPlayPlayerData(PLAYER_DATA data);

	// プレイ中に設定されたデータを削除する
	void PlayDataDelete(int playerNumber);

	// 一種類分データを取得
	OneData GetOneData(std::string fileName, int fileType, bool baseFlag = false);
	// 指定のシーンに必要な全データを取得
	std::vector<OneData> GetSceneData(SCENE sceneName);
	// 全データを取得
	std::vector<OneData> GetAllData(bool baseFlag = false);
	
	// 一種類分データを変更
	void ChangeOneData(OneData data, std::string fileName, int fileType);
	// 全データを変更
	void ChangeAllData(std::vector<OneData> data);

	// 削除アイテム設定
	void SetDeleteItem(std::string name);
	// 削除する必要があるアイテムを削除する
	void DeleteItemIfNeeded();

	// ファイルオープン失敗フラグ
	bool GetFailureFlag() { return mbFailureFlag; }

	// 渡されたデータから指定のキャラクタータイプのレベルデータを取得する
	static LEVEL_DATA GetLevelData(std::vector<OneData> data, int characterType);

	// 渡されたデータから指定のキャラクターデータを取得する
	//static std::vector<CHARACTER_DATA> GetCharacterData(std::vector<OneData> data, std::string fileName);

private:
	/*ファイルデータ読み込み用(OneData)*/
	OneData GetOneFileData(DATA_STRUCT fileName, std::ifstream *fileData);
	/*ファイルデータ書き込み用(OneData)*/
	void SetOneFileData(OneData setData, std::ofstream* file);


	/*ファイルデータ読み込み用(プレイヤーデータ)*/
	PLAYER_DATA GetPlayerFileData(std::ifstream* file);
	/*ファイルデータ書き込み用(プレイヤーデータ)*/
	void SetPlayerFileData(PLAYER_DATA setData, std::ofstream* file);
};