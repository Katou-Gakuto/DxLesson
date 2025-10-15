#pragma once
#include <string>

#include "DxLib.h"
#include "../Header/Data_Structs.h"
#include "../Header/Menu_Base.h"

class MenuNewData : public Menu_Base
{
private:
	int mnSelectManagerNumber;	// 選択マネージャー

	std::string mstrPlayerName;	// プレイヤーの名前
	int mnMaxNameNumber;	// 名前最大数
	int mnSelectHeight;	// 名前選択縦
	int mnSelectWidth;	// 名前選択横
	int mnPlayerTypeNumber;	// プレイヤータイプ数で表したもの
	bool mbWordSize;

	char mcPlayerNameSet[2][5][11];	// プレイヤーネームセット用

	int mnNameHandle;	// プレイヤー名表示用ハンドル
	int mnAlphabetHandle;	// アルファベット表示用ハンドル
	int mnNotAlphabetHandle;	// アルファベット以外の表示用ハンドル

	int mnPlayerTypeModelHandle[1];	// プレイヤーモデル画像ハンドル
	float mfPlayerTypeModelDrawPos[4][1];	// プレイヤー描画時画像描画用

	bool mbDrawUpKeyFlag;	// 描画用アップキーフラグ
	bool mbDrawDownKeyFlag;	// 描画用ダウンキーフラグ

	void SetOverride_CheckMenuProcess() override;    // チェック用関数(新データ作成用)

public:
	MenuNewData();	// コンストラクタ
	~MenuNewData();	// デストラクタ

	void MyInitilize() override;	// 個別初期化処理
	void MyFinalize() override;		// 個別終了処理
	void MyUpdate() override;		// 個別更新処理
	void MyDraw() override;			// 個別描画化処理

	void SelectDecision() override;	// 選択決定時処理

	void SetPlayerNameProcess();	// プレイヤー名設定処理
};