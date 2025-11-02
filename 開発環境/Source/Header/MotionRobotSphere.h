#pragma once
#include "DxLib.h"
#include "../Header/Motion_Base.h"
#include "../Header/Object_Base_Character.h"

class MotionRobotSphere : public Motion_Base
{
private:
    bool mbStartFlag;   // スタート時フラグ
    int mnStartTime;    // スタートモーション終了までの時間

    bool mbRelaxedFlag; // 休憩モーションフラグ
    int mnRelaxedTime;  // 休憩モーションに入るまでの時間を保存
    int mnSetRelaxedTime;   // セット用　休憩モーションまでの時間

    bool mbAttackStartFlag;     // 攻撃開始時モーションフラグ
    bool mbAttackMiddleFlag;    // 攻撃中フラグ
    bool mbAttackEndFlag;       // 攻撃終了時フラグ
    int mnAttackFlagChangeTime; // 攻撃フラグ変更時間

    float mfMaxAttackMiddleMotionTime;    // 攻撃中モーションの最大再生時間

    bool mbAttackReflectionFlag; //  固定物に当たったら攻撃を反射させるフラグ

    int mnNextWalkSoundTime;    // 次の歩きサウンドまでの時間
    bool mbOneFlag; // 一回のみフラグ

public:
    MotionRobotSphere(Object_Base_Character *character, int relaxedTime, bool endObjectFlag = false, bool attackReflectionFlag = false);
    ~MotionRobotSphere();

    void MyInitilize() override;
    void MyUpdata() override;
    void MyDraw() override;
    void MyFinalize() override;

    void ReSetPlusFlag() override;   // 追加したフラグをリセットする
    void SetPlusDataSort() override; // 追加したデータを整理する
    
    bool GetPlusAllFlag() override;// 追加したフラグがfalseかどうか返す(一つでもtrueがあればtrueを返す)

    int GetIndexNumber(const char *AnimName) override;    // インデックスナンバーを行動名で取得
    int GetIndexNumberLookFlag() override;  // インデックスナンバーをフラグで取得
    
    bool LoopCheck(int index) override; // ループチェック用

    void SetMultiAnimFrame() override;  // アニメーションフレーム固定用 複数
    void SetOneAnimFrame() override;    // アニメーションフレーム固定用 一つ

    void SetMotionEnd(bool *endFlag) override;  // モーション終了モーションスタート

    void SetPlusAllFlag(bool flag) override;    // 追加した全フラグ設定

    bool GetPlusStopMoveMotionFlag() override;  // キャラクターの移動処理をストップする追加さしたフラグならtrueを返す
    VECTOR StopMoveProcess() override;    // キャラクターの移動処理の代わりの処理をする

    void SetMotionAttackObject() override;  // モーションに設定されている攻撃をする

    bool GetPlusStopAttackFlag() override;  // キャラクターの攻撃処理をストップする追加したフラグが有効ならtrueを返す
    void StopAttackProcess() override;  // キャラクターの攻撃処理の代わりの処理をする

    int GetAttackTime() override;  // 攻撃時間を求める

    void AttackHitSound() override; // 攻撃が当たった時のサウンド
    void FixedHitSound() override;  // 固定物に当たった時のサウンド
    void HpZeroSound() override;    // HPがゼロになった時のサウンド

    void CangeAttackFlag(int number) override;  // 攻撃フラグを変更する
};