#pragma once
#include <vector>
#include "DxLib.h"
#include "../Header/Calculation.h"
#include "../Header/CoordinateXY.h"
#include "../Header/GenerateInformation_Struct.h"
#include "../Header/MapType_Enum.h"
#include "../Header/Object_Base.h"
//#include "../Header/Object_Base_Character.h"
#include "../Header/Scene_Enum.h"
#include "../Header/Status_Struct.h"

//class Object_Base_Character;

class StageManagerObject : public Object_Base 
{
private:
    char * mnMapHandleFileName; // マップモデルハンドルファイルネーム

    MAP_TYPE msMaptype; // マップタイプ

    std::vector<GENERATE_INFORATION> msGenerateInformation; // 生成情報入れ

    VECTOR mvPlusPosition;  // プラスポジション
    VECTOR mvMinusPosition; // マイナスポジション

    //bool mbNotExceptionFlag;    // 非例外フラグ

    int mnMapDrawHandle;    // マップ表示用ハンドル
    
    int mnMapFrameDreadth;  // マップフレームの幅

    bool mbMapDrawFlag;   // マップ表示フラグ

    COORDINATE_X_Y msMapUpperLeft;  // マップの左上
    COORDINATE_X_Y msMapLowerRight; // マップの右下
    COORDINATE_X_Y msMapMiddle;     // マップの中央
    COORDINATE_X_Y msMapSide;       // マップの一辺

    // 壁の四座標用変数ベクターツクール
    float mfMinMagnificationRate;   // 最小マップ拡大率
    float *mfMagnificationRate;      // マップ拡大率
    float mfMaxMagnificationRate;   // 最大マップ拡大率

    float mfMapAngle;   // マップのアングル
    enum class MapAngleFlag 
    {
        UP,     // 上
        RIGHT,  // 右
        DOWN,   // 下
        LEFT,   // 左

    };

public:

    StageManagerObject(const char *filename, MAP_TYPE maptype, VECTOR plusPosition, VECTOR minusPosition, bool mapFlag, float *magnificationRate);   // コンストラクタ
    ~StageManagerObject();   // デストラクタ


    void Initilize()    override;   // 初期化
    void Update()       override;   // 更新
    void Draw()         override;   // 描画
    void Finalize()     override;   // 終了処理

    void AddGenerateInforation(GENERATE_INFORATION generateInformation);    // キャラクター情報追加
    void CharacterGenerate();   // ステージ生成

    MAP_TYPE GetMapType() { return msMaptype; } // マップタイプ取得

    STATUS GetStatus(int level, int exp, int attackPower, int maxHp, int hp, int defense, int speed, int size); // ステータス取得

    void MapDraw(); // マップ描画処理
    void MapMagnification();    // 拡大系処理

    COORDINATE_X_Y GetMapPos(VECTOR pos);   // マップの何処に描画するか返す
    COORDINATE_X_Y GetStagePos(COORDINATE_X_Y pos); // マップの座標はステージの何処を示すか返す

    void DrawMapRate(float x1, float y1, float x2, float y2, float r, unsigned int color);  // マップ拡大率描画用
};