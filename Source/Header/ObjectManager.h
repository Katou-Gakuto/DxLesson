#pragma once
#include <vector>
#include "DxLib.h"
#include "../Header/Scene_Enum.h"

class Object_Base;
class Object_Base_Attack;
class Object_Base_Character;
class Object_Base_Fixed;

class ObjectManager
{
private:// 一番後のオブジェクト達消すかも
    Object_Base *mpObject;  // オブジェクト線形リストの一番前
    Object_Base *mpObjectL; // オブジェクト線形リストの一番後

    Object_Base_Attack *mpAttackObject;   // 攻撃オブジェクト線形リストの一番前
    Object_Base_Attack *mpAttackObjectL;  // 攻撃オブジェクト線形リストの一番後

    Object_Base_Character *mpCharacterObject;   // キャラクターオブジェクト線形リストの一番前
    Object_Base_Character *mpCharacterObjectL;  // キャラクターオブジェクト線形リストの一番後

    Object_Base_Fixed *mpFixedObject;   // 固定オブジェクト線形リストの一番前
    Object_Base_Fixed *mpFixedObjectL;  // 固定オブジェクト線形リストの一番後

public:
    ObjectManager();    // コンストラクタ
    ~ObjectManager();   // デストラクタ

    void Initilize();   // 初期化処理を行う関数
    void Update();      // 更新処理を行う関数
    void Draw();        // 描画処理を行う関数
    void Finalize();    // 終了処理を行う関数

    void Add(Object_Base *object);      // リストにオブジェクトを追加する関数
    void Delete(Object_Base *object);   // リストからオブジェクトを除外する関数
    Object_Base *FindByTag(int tag, bool flag = false);                 // タグからオブジェクトを取得
    std::vector<Object_Base *> FindsByTag(int tag, bool flag = false);  // タグから複数オブジェクトを取得

    void AddAttack(Object_Base_Attack *attackObject);      // リストに攻撃オブジェクトを追加
    void AttackDelete(Object_Base_Attack *attackObject);   // リストから攻撃オブジェクトを除外
    Object_Base_Attack *FindByTag_AttackObject(int tag, bool flag = false);               // タグから攻撃オブジェクトを取得
    std::vector<Object_Base_Attack *>FindsByTag_AttackObject(int tag, bool flag = false); // タグから複数攻撃オブジェクトを取得
    bool AllAttackObjectHitCheck(Object_Base_Character *characterObject);   // 攻撃オブジェクトの攻撃判定　当たていればダメージを負う

    void AddCharacter(Object_Base_Character *characterObject);      // リストにキャラクターオブジェクトを追加
    void CharacterDelete(Object_Base_Character *characterObject);   // リストからキャラクターオブジェクトを除外
    Object_Base_Character *FindByTag_CharacterObject(int tag, bool flag = false);               // タグからキャラクターオブジェクトを取得
    std::vector<Object_Base_Character *>FindsByTag_CharacterObject(int tag, bool flag = false); // タグから複数キャラクターオブジェクトを取得

    void AddFixed(Object_Base_Fixed *fixedObject);      // リストに固定オブジェクトを追加
    void FixedDelete(Object_Base_Fixed *fixedObject);   // リストから固定オブジェクトを除外
    Object_Base_Fixed *FindByTag_FixedObject(int tag, bool flag = false);               // タグから固定オブジェクトを取得
    std::vector<Object_Base_Fixed *>FindsByTag_FixedObject(int tag, bool flag = false); // タグから複数固定オブジェクトを取得
    VECTOR FixedObjectHitCheck(VECTOR checkPosition, VECTOR noePosition, VECTOR moveVec, float size);   // 固定オブジェクトに当たっているかチェック


    void SetDeleteSceneObject(SCENE targetScene);    // 指定したシーンで生成されたオブジェクトの削除フラグ有効にする

    void DeleteAll();           // オブジェクト全削除
    void DeleteAllIfNeeded();   // 必要であればオブジェクト削除を行う
};



//class Object;

/*
    オブジェクト管理クラス
*//*
class ObjectManager
{
public:
    ObjectManager();        // コンストラクタ
    ~ObjectManager();       // デストラクタ

    void Initilize();  // 初期化
    void Update();      // 更新
    void Draw();        // 描画
    void Finalize();    // 終了処理

    void Add(Object *object);
    void Delete(Object *object);

private:
    Object *mpObject;
};*/