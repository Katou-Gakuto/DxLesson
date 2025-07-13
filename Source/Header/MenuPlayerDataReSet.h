#pragma once
#include "../Header/Menu_Base.h"

class DataManager;

class MenuPlayerDataReSet : public Menu_Base
{
private:

	void SetOverride_CheckMenuProcess() override;    // チェック用関数(データリセット用)

public:
    MenuPlayerDataReSet();	// コンストラクタ
    ~MenuPlayerDataReSet();	// デストラクタ

	void MyInitilize() override;	// 個別初期化処理
	void MyFinalize() override;		// 個別終了処理
	void MyUpdate() override;		// 個別更新処理
	void MyDraw() override;			// 個別描画化処理

	void SelectDecision() override;  // 選択決定時処理
};