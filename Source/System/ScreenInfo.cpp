#include "ScreenInfo.h"
#include "SystemTypes.h"

namespace {
    //����
    const int half = 2;
    //�}�b�v�`�b�v�T�C�Y
    const int map_chip_size = 32;
}

ScreenInfo* ScreenInfo::screen_info = nullptr;

ScreenInfo::ScreenInfo()
{
}

ScreenInfo::~ScreenInfo()
{
}

void ScreenInfo::CreateInstance() {

    if (screen_info == nullptr) {
        screen_info = new ScreenInfo();
    }
}

ScreenInfo* ScreenInfo::GetInstance() {
    return screen_info;
}

void ScreenInfo::DeleteInstance() {
    delete screen_info;
    screen_info = nullptr;
}

void ScreenInfo::Initialize() {

    resolution_x = SCREEN_RESOLUTION_X;
    resolution_y = SCREEN_RESOLUTION_Y;

    display_center_x = resolution_x / half;
    display_center_y = resolution_y / half;
}

int ScreenInfo::GetResolutionX()
{
    return resolution_x;
}

int ScreenInfo::GetResolutionY()
{
    return resolution_y;
}

int ScreenInfo::GetCenterX()
{
    return display_center_x;
}

int ScreenInfo::GetCenterY()
{
    return display_center_y;
}

void ScreenInfo::SetMapSize(int x, int y) {

    map_x_size = x;
    map_y_size = y;

    //�}�b�v�̈�ԍ���̍��W�����_���v�Z������B
    //��ʂ̒��S����A(�}�b�v��x�T�C�Y*�}�b�v�`�b�v�̑傫��=�S��ʂ̑傫��) / ����
    map_left_x = static_cast<float>(display_center_x % display_center_x); //- static_cast<float>((x * map_chip_size) / half);
    map_left_y = static_cast<float>(display_center_y % display_center_y);
}

float ScreenInfo::GetLeftX()
{
    return map_left_x;
}

float ScreenInfo::GetLeftY()
{
    return map_left_y;
}
