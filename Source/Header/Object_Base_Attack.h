#pragma once
#include <vector>
#include "../Header/Object_Base.h"

class Object_Base_Character;

class Object_Base_Attack : public Object_Base
{
private:
    Object_Base_Attack *mpPrevAttackObject;   // 前攻撃オブジェクトへのポインタ
    Object_Base_Attack *mpNextAttackObject;   // 次攻撃オブジェクトへのポインタ

    Object_Base_Character *mpAttackCharacter;   // 攻撃したキャラクター　// ヌルの場合もある

    std::vector<Object_Base_Character *> mpHitCharacter;    // この攻撃が当たったキャラクタ

    bool mbAttackDeleteFlag;    // 攻撃削除フラグ 

protected:
    int mnDamage;   // 与ダメージ
    int mnSurvivalGameTime; // 生存時間

    Object_Base_Character *GetMyObjectCharacter() { return mpAttackCharacter; } // 攻撃しているキャラクター

public:
    Object_Base_Attack(Object_Base_Character *attackCharacter, int damage, int survivalGameTime);
    ~Object_Base_Attack();

    virtual void Initilize() override;  // 初期化
    void Update() override final;       // 更新
    virtual void MyUpdate() = 0;        // 派生オブジェクト更新
    virtual void Draw() override;       // 描画
    void Finalize() override final;     // アタックオブジェクト共通終了処理
    virtual void MyFinailize() = 0;     // 派生オブジェクト終了処理

    Object_Base_Attack *GetPrevAttackObject() { return mpPrevAttackObject; }   // 前攻撃オブジェクトへのポインタ取得
    Object_Base_Attack *GetNextAttackObject() { return mpNextAttackObject; }   // 次攻撃オブジェクトへのポインタ取得

    void SetPrevAttackObject(Object_Base_Attack *attackObject) { mpPrevAttackObject = attackObject; }    // 前攻撃オブジェクトのポインタを設定する関数
    void SetNextAttackObject(Object_Base_Attack *attackObject) { mpNextAttackObject = attackObject; }    // 次攻撃オブジェクトのポインタを設定する関数

    bool CheckCharacter(Object_Base_Character *character);              // キャラクターに攻撃が当たっていればダメージ処理をして記録する
    virtual bool AttackHitCheck(Object_Base_Character *character) = 0;  // キャラクターに攻撃が当たって居るか判定する

};