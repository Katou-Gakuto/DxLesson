#pragma once
#include <string>

#include "../Header/Object_Base_Character.h"

struct ItemData;

class Item_Base
{
private:
	int mnItemType;	// アイテムタイプ

protected:
	int mnItemNumber;	// アイテム数
	int mnItemHandle;	// アイテム画像ハンドル
	std::string mstrDisplayName;	// 表示用の名前

public:
	Item_Base(ItemData item);	// コンストラクタ
	virtual ~Item_Base();	// デストラクタ

	void Draw(int x, int y, int sizeX, int sizeY);	// アイテム画像描画

	virtual void ItemEffect(Object_Base_Character *character) = 0;	// アイテム効果

	int GetItemNumber() { return mnItemNumber; }	// アイテム数を取得

	std::string GetItemName() { return mstrDisplayName; }	// アイテム名取得
};