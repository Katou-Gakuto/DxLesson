#pragma once
#include "../Header/Menu_Base.h"

class SoundManager;

class MenuHowToPlay : public Menu_Base
{
private:
	bool mbUpKyeFlag;	// 上キーフラグ
	bool mbDownKeyFlag;	// 下キーフラグ

	SoundManager *mpSoundManager;	// サウンドマネージャー

	int mnDrawPictureHandle[3];	// 写真ハンドル

	int mnDrawMaxMinStringHandle;	// マックスとミニを描画するためのハンドル
	int mnDrawSoundVolumeStringHandle;	// サウンドボリューム描画用ハンドル

	bool mbDrawRightKeyFlag;	// 描画用右キーフラグ
	bool mbDrawLeftKeyFlag;	// 描画用左キーフラグ

public:
	MenuHowToPlay();	// コンストラクタ
	~MenuHowToPlay();	// デストラクタ

	void MyInitilize() override;	// 個別初期化処理
	void MyFinalize() override;		// 個別終了処理
	void MyUpdate() override;		// 個別更新処理
	void MyDraw() override;			// 個別描画化処理

	void SelectDecision() override;  // 選択決定時処理
};