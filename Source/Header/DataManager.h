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
	OneData GetOneData(std::string fileName, std::string fileTypeName, bool baseFlag = false);
	// 指定のシーンに必要な全データを取得
	std::vector<OneData> GetSceneData(SCENE sceneName);
	// 全データを取得
	std::vector<OneData> GetAllData(bool baseFlag = false);
	
	// 一種類分データを変更
	void ChangeOneData(OneData data, std::string fileName, std::string fileTypeName);
	// 全データを変更
	void ChangeAllData(std::vector<OneData> data);

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