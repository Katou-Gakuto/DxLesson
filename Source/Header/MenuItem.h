#pragma once
#include <vector>

#include "../Header/Menu_Base.h"

class Item_Base;

class MenuItem : public Menu_Base
{
private:
	std::vector<Item_Base *> mpItems;   // アイテム

	int mnItemDrawHandle;	// アイテム描画用ハンドル

	int mnXMax;	// 最大横描画量
	int mnYMax;	// 最大縦描画量

public:
	MenuItem();	// コンストラクタ
	~MenuItem();	// デストラクタ

	void MyInitilize() override;	// 個別初期化処理
	void MyFinalize() override;		// 個別終了処理
	void MyUpdate() override;		// 個別更新処理
	void MyDraw() override;			// 個別描画化処理

	void SelectDecision() override;  // 選択決定時処理
};