#pragma once

/// <summary>
/// マップチップの種類
/// </summary>
enum  MapChipType {

    kNONE = 0,
    kGROUND = 1,
    kWALL,
    kBROKEN_WALL,
    kBOX,
    kGIMMICK_BOX,
    kGOAL,
    kPLAYER_START,
    kBASE_ENEMY = 8,
    kATTACK_ENEMY,
    kCOIN = 10,
    kINVINCIBLE_CAN 
};