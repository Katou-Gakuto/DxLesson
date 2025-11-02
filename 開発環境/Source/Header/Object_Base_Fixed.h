#pragma once
#include "DxLib.h"
#include "../Header/Object_Base.h"

class Object_Base_Fixed : public Object_Base
{
private:
    Object_Base_Fixed *mpPrevFixedObject;   // 前固定オブジェクトへのポインタ
    Object_Base_Fixed *mpNextFixedObject;   // 次固定オブジェクトへのポインタ

protected:
    VECTOR mvPlusPosition;  // プラスポジション
    VECTOR mvMinusPosition; // マイナスポジション

    unsigned int mnMapColor;    // ミニマップ描画用カラー

    void SetPlusMinusPosition(VECTOR plusPosition, VECTOR minusPosition);   // マインスとプラスポジションを設定する

public:
    Object_Base_Fixed(unsigned int mapColor);    // コンストラクタ
    ~Object_Base_Fixed();   // デストラクタ

    virtual void Initilize() override;  // 初期化
    virtual void Update() override;     // 更新
    virtual void Draw() override;       // 描画
    void Finalize() override final;     // 固定オブジェクト共通終了処理
    virtual void MyFinalize() = 0;     // 派生オブジェクト終了処理

    Object_Base_Fixed *GetPrevFixedObject() { return mpPrevFixedObject; }   // 前固定オブジェクトへのポインタ取得
    Object_Base_Fixed *GetNextFixedObject() { return mpNextFixedObject; }   // 次固定オブジェクトへのポインタ取得

    void SetPrevFixedObject(Object_Base_Fixed *fixedObject) { mpPrevFixedObject = fixedObject; }    // 前固定オブジェクトのポインタを設定する関数
    void SetNextFixedObject(Object_Base_Fixed *fixedObject) { mpNextFixedObject = fixedObject; }    // 次固定オブジェクトのポインタを設定する関数

    virtual VECTOR CheckHit_ReturnAmountMoved(VECTOR checkPosition, VECTOR nowPosition, VECTOR moveVec, float size);    // 当たり判定

    VECTOR GetPlusPosition() { return mvPlusPosition; } // プラスポジション取得
    VECTOR GetMinusPosition() { return mvMinusPosition; }   // マイナスポジション取得
    unsigned int GetDrawMapColor() { return mnMapColor; }   // マップ描画用カラー取得
};