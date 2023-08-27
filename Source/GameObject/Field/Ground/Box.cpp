#include "Box.h"
#include "DxLib.h"

void Box::Update(float DeltaTime)
{
}

void Box::Initialize() {
	box_graphic_handle = LoadGraph("Resources/Images/mapchip_017.bmp");
	LoadDivGraph("Resources/Images/mapchip_017.bmp", 7, 4, 2, 32, 32, gimmick_box_graphic_handle);
}

void Box::Draw(const Vector2D& screen_offset) {

    int x_left = body_collision.center_position.x - body_collision.box_extent.x;
    int y_left = body_collision.center_position.y - body_collision.box_extent.y;

    int x1 = static_cast<int>(x_left);
    int y2 = static_cast<int>(y_left);
    DrawGraph(x1, y2, box_graphic_handle, true);

    //デバック用
    unsigned int color = GetColor(255, 255, 255);
    DrawBox(x1, y2, x1 + 32, y2 + body_collision.box_extent.y*2, color, false);
   
}
