#include "Ground.h"
#include "../Source/System/ScreenInfo.h"
#include "DxLib.h"

namespace {
    //地面の画像枚数
    const int ground_mapchip_file_num = 9;
    //画像データの連番数
    //1枚目の連番になる。
    const int first_sequence = 37;
}

void Ground::Update(float DeltaTime)
{
}

void Ground::Initialize(){
    char file_name[100];
    for (int i = first_sequence, j = 0; j < ground_mapchip_file_num; i++, j++) {
        snprintf(file_name, sizeof(file_name), "Resources/Images/mapchip_0%d.bmp", i);
        ground_graphic_handle[j] = LoadGraph(file_name);
    }
}

void Ground::Draw(const Vector2D& screen_offset) {
    ScreenInfo* screen_info = ScreenInfo::GetInstance();

    int min_handle = 0;
    int max_handle = 0;
    int handle_num = 0;

    for (unsigned y = 0; y < ground_data.size(); y++) {
       
        switch (y) {

        case kFirst:
            min_handle = 0;
            max_handle = 2;
            break;
        case kSecond:
            min_handle = 3;
            max_handle = 5;
            break;
        case kThird:
            min_handle = 6;
            max_handle = 8;
            break;
        }

        handle_num = min_handle;

        for (unsigned x = 0; x < ground_data.at(y).size(); x++) {
            int x_graphic_size = 0;
            int y_graphic_size = 0;
            GetGraphSize(ground_graphic_handle[handle_num], &x_graphic_size, &y_graphic_size);

            int x_left = body_collision.center_position.x - body_collision.box_extent.x;
            int y_left = body_collision.center_position.y - body_collision.box_extent.y;

            int x1 = static_cast<int>(x_left + 32 * x);
            int y2 = static_cast<int>(y_left + 32 * y);
            DrawGraph(x1, y2, ground_graphic_handle[handle_num], true);

            handle_num++;
            if (handle_num > max_handle) {
                handle_num = min_handle;
            }
            //デバック用
            unsigned int color = GetColor(255, 255, 255);
            DrawBox(x1, y2, x1 + 32, y2 + 32, color, false);
        }
    }
}
