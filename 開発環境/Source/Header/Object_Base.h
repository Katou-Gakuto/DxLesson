#pragma once
#include "DxLib.h"
#include "../Header/Scene_Enum.h"

/*
    オブジェクト　ベースクラス

    全ての生成されるオブジェクトはこれを継承することを前提とする。
    2Dのオブジェクト、3Dのオブジェクトは問わない。
    何か特殊な事情がある場合は除く。(シーン系や管理クラス系など。そのほかは基本継承させて問題がないように作っていく)
*/


class Object_Base
{
private:
    //int positionX;
    //int positionY;
    //int positionZ;

    ////--- 派生オブジェクトに移動 ---//
    //float mnHp;                 // 残りHP
    //const float mnMaxHp = 100;        // 最大HP
    //float mfAttackPower;        // 攻撃力

    //bool AttackHitPlayerFlag;   // 攻撃が有効フラグ
    ////---                        ---//

    Object_Base* mpPrevObject;                                                  // 前オブジェクトへのポインタ
    Object_Base* mpNextObject;                                                  // 次オブジェクトへのポインタ

    bool mbIsDeleteFlag;    // 削除フラグ
    int mnTag;              // 識別タグ


protected:
    SCENE meObjectScene;    // 生成されたシーン

public:
    Object_Base();                                                              // コンストラクタ
    ~Object_Base();                                                             // デストラクタ

    virtual void Initilize() = 0;                                               // 初期化処理を行う関数
    virtual void Finalize() = 0;                                                // 終了処理を行う関数
    virtual void Update() = 0;                                                  // 更新処理を行う関数
    virtual void Draw() = 0;                                                    // 描画処理を行う関数

    Object_Base* GetPrevObject() { return mpPrevObject; }   // 前オブジェクトへのポインタ取得
    Object_Base* GetNextObject() { return mpNextObject; }   // 次オブジェクトへのポインタ取得

    void SetPrevObject(Object_Base* object) { mpPrevObject = object; }          // 前オブジェクトのポインタを設定する関数
    void SetNextObject(Object_Base* object) { mpNextObject = object; }          // 次オブジェクトのポインタを設定する関数

    void SetDeleteFlag(bool flag) { mbIsDeleteFlag = flag; }    // 削除フラグ設定
    bool IsDeleteFlag() { return mbIsDeleteFlag; }  // 削除フラグ取得

    void SetTag(int tag) { mnTag = tag; }       // タグ設定
    int GetTag() { return mnTag; }              // タグ取得
    void DeleteSetTag(int number, bool flag);   // タグにあったオブジェクトの削除フラグを有効化
    
    virtual bool ObjectHitTag(VECTOR* position, VECTOR moveVec, VECTOR old_Position, float radius, bool flag, VECTOR size = VGet(0.0f, 200.0f, 0.0f));   // 当たっているかどうか   
    virtual bool ObjectHitsTag(VECTOR *position, VECTOR moveVec, VECTOR old_Position, float radius, bool flag, VECTOR size = VGet(0.0f, 200.0f, 0.0f));   // 当たっているかどうか(複数当たっている場合使う)

    

    SCENE GetObjectScene() { return meObjectScene; }    // 生成されたシーンを取得
};
