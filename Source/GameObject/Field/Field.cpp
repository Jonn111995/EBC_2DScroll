#include "Field.h"
#include "DxLib.h"
#include "../Source/System/ScreenInfo.h"
#include <iostream>
#include "../CSVData/CSVFile.h"
#include "EMapChipType.h"
#include "../Source/Utility/Vector2D.h"
#include "../Source/Utility/BoxCollisionParams.h"

namespace {
    const int ground_mapchip_file_num = 9;
    const int first_sequence = 37;
}

Field::Field()
{
}

Field::~Field()
{
}

void Field::Update(float DeltaTime)
{
}

void Field::Initialize() {

    char file_name[100];

    for (int i = first_sequence, j = 0; j < ground_mapchip_file_num; i++, j++) {
        snprintf(file_name, sizeof(file_name), "Resources/Images/mapchip_0%d.bmp", i);
        ground_graphic_handle[j] = LoadGraph(file_name);
    }

    wall_graphic_handle = LoadGraph("Resources/Images/mapchip_033.bmp");
    box_graphic_handle = LoadGraph("Resources/Images/mapchip_017.bmp");

    wall_collision.center_position = Vector2D(16, 24);
    wall_collision.box_extent = Vector2D(8, 12);
    box_collision.center_position = Vector2D(16, 24);
    box_collision.box_extent = Vector2D(8, 12);
}

void Field::Draw(const Vector2D& screen_offset){
    ScreenInfo* screen_info = ScreenInfo::GetInstance();
    int graph = 0;
  
    for (unsigned y = 0; y < map_data.size(); y++) {
        for (unsigned x = 0; x < map_data.at(y).size(); x++) {
            
            //配列の要素にアクセスしたら、その値(0か1が入っている。)が0か1なのかを
            //確認する。その値によって、graph変数に入れるハンドルの値を変える。
            if (map_data.at(y).at(x) == MapChipType::kWall) {
                graph = wall_graphic_handle;
            }
            //要素の値が1だったら、kRoadと同じ値なので、roadのハンドルを代入。
            else if (map_data.at(y).at(x) == MapChipType::kBox){
                graph = box_graphic_handle;
            }
            else {
                continue;
            }

            int x_graphic_size = 0;
            int y_graphic_size = 0;
            GetGraphSize(graph, &x_graphic_size, &y_graphic_size);
           
            int x1 = static_cast<int>(screen_info->GetLeftX()) + 32 * x;
            int y2 = static_cast<int>(screen_info->GetLeftY()) + 32 * y;
            //描画する。xとyの位置に、その位置に設定されているハンドル値による画像を描画する。
            DrawGraph(x1, y2, graph, true);
            unsigned int color = GetColor(255, 255, 255);
            /*x += body_collision.center_position.x;
            y += body_collision.center_position.y;*/
            DrawBox(x1, y2, x1+32, y2+32, color, false);
        }
    }
    DrawGroundSet();
}

bool Field::InitializeField(const char* map_file_name){

	csv_file_reader = new CSVFile();
	if (!csv_file_reader->Read(map_file_name)) {
		std::cout << u8"マップの初期化に失敗しました" << std::endl;
		return false;
	}

	map_data = csv_file_reader->GetData();

    ScreenInfo* screen_info = ScreenInfo::GetInstance();
    screen_info->SetMapSize(map_data.size(), map_data.at(map_data.size() - 1).size());

}

bool Field::CheckMove(const Vector2D& move_to_position, const BoxCollisionParams& collision) {

   /* int x_position = move_to_position.x / 32;
    int y_position = move_to_position.y / 32;*/

    float opponent_center_x = move_to_position.x + collision.center_position.x;
    float opponent_center_y = move_to_position.y + collision.center_position.y;

    Vector2D Check_posi = Vector2D((opponent_center_x + -collision.box_extent.x),
        (opponent_center_y + -collision.box_extent.y));

    int x_position = Check_posi.x / 32;
    int y_position = Check_posi.y / 32;

    int object_in_destination = map_data.at(y_position).at(x_position);

    if (object_in_destination == kWall || object_in_destination == kGround || object_in_destination == kBox) {
        //地面や壁のコリジョンを持っておく？
     /*   ScreenInfo* screen_info = ScreenInfo::GetInstance();
        int left_x = static_cast<int>(screen_info->GetLeftX()) + x_position * 32;
        int left_y = static_cast<int>(screen_info->GetLeftY()) + y_position * 32;*/

        ScreenInfo* screen_info = ScreenInfo::GetInstance();
        int left_x = static_cast<int>(screen_info->GetLeftX()) + x_position * 32;
        int left_y = static_cast<int>(screen_info->GetLeftY()) + y_position * 32;

        int center_position_x = wall_collision.center_position.x + left_x;
        int center_position_y = wall_collision.center_position.x + left_y;

        int distance_x = abs(opponent_center_x - center_position_x);
        int distance_y = abs(opponent_center_y - center_position_y);

        int size_x = (collision.box_extent.x * 2 + wall_collision.box_extent.x * 2) / 2;
        int size_y = (collision.box_extent.y * 2 + wall_collision.box_extent.y * 2) / 2;

        if (distance_x < size_x && distance_y < size_y) {

            return false;
        }
        return true;
    }

    x_position = (Check_posi.x + 32) / 32;
    object_in_destination = map_data.at(y_position).at(x_position);
    if (object_in_destination == kWall || object_in_destination == kGround || object_in_destination == kBox) {
        //地面や壁のコリジョンを持っておく？
       /* ScreenInfo* screen_info = ScreenInfo::GetInstance();
        int left_x = static_cast<int>(screen_info->GetLeftX()) + x_position * 32;
        int left_y = static_cast<int>(screen_info->GetLeftY()) + y_position * 32;*/
        ScreenInfo* screen_info = ScreenInfo::GetInstance();
        int left_x = static_cast<int>(screen_info->GetLeftX()) + x_position * 32;
        int left_y = static_cast<int>(screen_info->GetLeftY()) + y_position * 32;

        int center_position_x = wall_collision.center_position.x + left_x;
        int center_position_y = wall_collision.center_position.x + left_y;

        int distance_x = abs(opponent_center_x - center_position_x);
        int distance_y = abs(opponent_center_y - center_position_y);

        int size_x = (collision.box_extent.x * 2 + wall_collision.box_extent.x * 2) / 2;
        int size_y = (collision.box_extent.y * 2 + wall_collision.box_extent.y * 2) / 2;

        if (distance_x < size_x && distance_y < size_y) {

            return false;
        }

    }
    return true;
}

bool Field::CheckStande(Vector2D& move_to_position, const BoxCollisionParams& collision){

    bool check_left = false;
    bool check_right = false;
    float opponent_center_x = move_to_position.x + collision.center_position.x;
    float opponent_center_y = move_to_position.y + collision.center_position.y;

    Vector2D Check_posi = Vector2D((opponent_center_x  + -collision.box_extent.x),
        (opponent_center_y + -collision.box_extent.y));

    int x_position = Check_posi.x / 32;
    int y_position = (Check_posi.y + 32) / 32;

    int object_in_destination = map_data.at(y_position).at(x_position);
    if (object_in_destination == kWall || object_in_destination == kGround || object_in_destination == kBox) {
        ScreenInfo* screen_info = ScreenInfo::GetInstance();
        int left_x = static_cast<int>(screen_info->GetLeftX()) + x_position * 32;
        int left_y = static_cast<int>(screen_info->GetLeftY()) + y_position * 32;

        int center_position_x = wall_collision.center_position.x + left_x;
        int center_position_y = wall_collision.center_position.x + left_y;

        int distance_x = abs(opponent_center_x - center_position_x);
        int distance_y = abs(opponent_center_y - center_position_y);

        int size_x = (collision.box_extent.x * 2 + wall_collision.box_extent.x * 2) / 2;
        int size_y = (collision.box_extent.y * 2 + wall_collision.box_extent.y * 2) / 2;

        if (distance_y < size_y) {

            return true;
        }
        check_left = false;
    }

    x_position = (move_to_position.x + 32) / 32;
    y_position = (move_to_position.y + 32) / 32;

    object_in_destination = map_data.at(y_position).at(x_position);
    if (object_in_destination == kWall || object_in_destination == kGround || object_in_destination == kBox) {
        ScreenInfo* screen_info = ScreenInfo::GetInstance();
        int left_x = static_cast<int>(screen_info->GetLeftX()) + x_position * 32;
        int left_y = static_cast<int>(screen_info->GetLeftY()) + y_position * 32;

        int center_position_x = wall_collision.center_position.x + left_x;
        int center_position_y = wall_collision.center_position.x + left_y;

        int distance_x = abs(opponent_center_x - center_position_x);
        int distance_y = abs(opponent_center_y - center_position_y);

        int size_x = (collision.box_extent.x * 2 + wall_collision.box_extent.x * 2) / 2;
        int size_y = (collision.box_extent.y * 2 + wall_collision.box_extent.y * 2) / 2;

        if (distance_y < size_y) {

            return true;
        }
        check_right = false;
    }
    //右も左もついてなければ立てない
    return !(!check_left && !check_right);
}

void Field::DrawGroundSet() {
    ScreenInfo* screen_info = ScreenInfo::GetInstance();
    int i = 0; 
    int j = 0;
    bool first = false;
    int graph = 0;
    for (unsigned x = 0; x < map_data.at(map_data.size()-1).size(); x++) {
        for (unsigned y = 0; y < map_data.size(); y++) {

            if (map_data.at(y).at(x) == MapChipType::kGround) {
            
                if (!first) {
                    first = true;
                    int index = 0;
                    for (int i = 0; i < (map_data.size() - y); i++) {

                        int x_graphic_size = 0;
                        int y_graphic_size = 0;
                        GetGraphSize(ground_graphic_handle[index], &x_graphic_size, &y_graphic_size);
                        int x1 = static_cast<int>(screen_info->GetLeftX()) + x_graphic_size * x;
                        int y2 = static_cast<int>(screen_info->GetLeftY()) + 32 * (y + i);
                        //描画する。xとyの位置に、その位置に設定されているハンドル値による画像を描画する。
                        DrawGraph(x1, y2, ground_graphic_handle[index], true);

                        if (index < 6) {
                            index += 3;
                        }
                    }
                }
            }     
        }
        first = false;
    }
}

void Field::AddStageObject(Character*)
{
}
