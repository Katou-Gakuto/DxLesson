#pragma once
#include "../Header/Menu_Base.h"

class StageManagerObject;
class SoundManager;

class MenuSystem : public Menu_Base
{
private:
	StageManagerObject *mpStageManager;
	SoundManager *mpSoundManager;

	int	mnSelectManagerNumber;	// 選択管理用ナンバー

	int mnSystemDrawHandle;	// システム選択肢描画用ハンドル
	int mnSystemBackSoundDrawHandle;	// システム選択(バックサウンド用)肢描画用ハンドル
	int mnManualDrawHandle;	// マニュアル文字描画用ハンドル

	bool mbDrawRightKeyFlag;	// 描画用右キーフラグ
	bool mbDrawLeftKeyFlag;	// 描画用左キーフラグ
	bool mbDrawUpKeyFlag;	// 描画用上キーフラグ
	bool mbDrawDownKeyFlag;	// 描画用下キーフラグ

	bool mbTestSoundFlag;	// サウンドのボリュームを確認するための音を出すか判断する

	bool GetAllDrawFlag();	// 描画用フラグのどれかが有効かどうか返す
public:
    MenuSystem();   // コンストラクタ
    ~MenuSystem();  // デストラクタ

	void MyInitilize() override;	// 個別初期化処理
	void MyFinalize() override;		// 個別終了処理
	void MyUpdate() override;		// 個別更新処理
	void MyDraw() override;			// 個別描画化処理

	void SelectDecision() override;	// 選択決定時処理
};