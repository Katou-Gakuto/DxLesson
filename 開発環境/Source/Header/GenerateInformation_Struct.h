#pragma once
#include <iostream>

#include "DxLib.h"
#include "../Header/CharacterType_Enum.h"
#include "../Header/Scene_Enum.h"
#include "../Header/Status_Struct.h"

typedef struct GenerateInformation  // 生成情報
{
    std::string name;
    std::string dataFileName;

    CHARACTER_TYPE characterType;   // キャラクタータイプ
    VECTOR GeneratePosition;        // 生成場所

    STATUS status;

    SCENE scene;

    float angle;    // 見ている方向

    bool survivalFlag;  // 生存フラグ

}GENERATE_INFORATION;