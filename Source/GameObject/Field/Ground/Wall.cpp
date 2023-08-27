#include "Wall.h"
#include "DxLib.h"
#include <algorithm>
#include "../EMapChipType.h"
namespace {
    //地面の画像枚数
    const int ground_mapchip_file_num = 3;
    //画像データの連番数
    //1枚目の連番になる。
    const int first_sequence = 0;
}
void Wall::Update(float DeltaTime)
{
}

void Wall::Initialize() {

    char file_name[100];
    for (int i = first_sequence, j = 0; j < ground_mapchip_file_num; i++, j++) {
        snprintf(file_name, sizeof(file_name), "Resources/Images/mapchip_00%d.bmp", i);
        wall_graphic_handle[j] = LoadGraph(file_name);
    }
}

void Wall::Draw(const Vector2D& screen_offset) {

    for (unsigned y = 0; y < ground_data.size(); y++) {
        for (unsigned x = 0; x < ground_data.at(y).size(); x++) {

            int x_left = body_collision.center_position.x - body_collision.box_extent.x;
            int y_left = body_collision.center_position.y - body_collision.box_extent.y;

            int x1 = static_cast<int>(x_left + 32 * x);
            int y2 = static_cast<int>(y_left + 32 * y);
            DrawGraph(x1, y2, wall_graphic_handle[0], true);

            //デバック用
            unsigned int color = GetColor(255, 255, 255);
            DrawBox(x1, y2, x1 + 32, y2 + 32, color, false);
        }
    }
}
