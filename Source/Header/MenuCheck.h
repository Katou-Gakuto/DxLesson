#pragma once
#include "../Header/Menu_Base.h"
#include "../Header/Object_Base.h"

class MenuCheck : public Menu_Base
{
private:
	Menu_Base *mpMenu;
	Menu_Base &mpMenuClass;
    void(Menu_Base:: *mfnDecisionProcess)();	// 選択関数

	void(*mfnNotMenuDecisionProcess)(Object_Base *object);	// 実行関数
	Object_Base *mpObject;	// 実行オブジェクト

	int mnCheckHandle;	// チェック文字ハンドル
	int mnSelectHandle;	// 選択文字ハンドル

	bool mbMenuFlag;	// 実行する関数がメニューの関数であるかのフラグ

public:
    MenuCheck(Menu_Base &menuClass, void(Menu_Base:: *decisionProcess)(), Menu_Base* menu);	// コンストラクタ
    MenuCheck(void(*decisionProcess)(Object_Base *object), Object_Base *object);	// コンストラクタ
    ~MenuCheck();	// デストラクタ

	void MyInitilize() override;	// 個別初期化処理
	void MyFinalize() override;		// 個別終了処理
	void MyUpdate() override;		// 個別更新処理
	void MyDraw() override;			// 個別描画化処理

	void SelectDecision() override;  // 選択決定時処理
};