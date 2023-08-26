#include "Field.h"
#include "DxLib.h"
#include "../Source/System/ScreenInfo.h"
#include <iostream>
#include "../CSVData/CSVFile.h"
#include "EMapChipType.h"
#include "../Source/Utility/Vector2D.h"
#include "../Source/Utility/BoxCollisionParams.h"
#include "Ground/Ground.h";

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

    wall_graphic_handle = LoadGraph("Resources/Images/mapchip_033.bmp");
    box_graphic_handle = LoadGraph("Resources/Images/mapchip_017.bmp");
}

void Field::Draw(const Vector2D& screen_offset){

    for (auto object : StageObjectList) {
        object->Draw(screen_offset);
    }
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

    std::vector<Vector2D> leftup_pos_ground_data = ReadGroundData();
    CreateGround(leftup_pos_ground_data);
}

bool Field::CheckMove(const Vector2D& move_to_position, const BoxCollisionParams& collision) {

    float opponent_center_x = move_to_position.x + collision.center_position.x;
    float opponent_center_y = move_to_position.y + collision.center_position.y;

    for(auto obj : StageObjectList) {
   
        BoxCollisionParams ground_collision = obj->GetBodyCollision();
      
        float distance_x = abs(opponent_center_x - ground_collision.center_position.x);
        float distance_y = abs(opponent_center_y - ground_collision.center_position.y);
       
        float size_x = collision.box_extent.x + ground_collision.box_extent.x;
        float size_y = collision.box_extent.y + ground_collision.box_extent.y;

        if (distance_x < size_x && static_cast<int>(distance_y) < static_cast<int>(size_y)) {
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

    //中心座標 - 横幅の半分、中心座標 + 縦幅の半分
    Vector2D opponent_y_leftdown = Vector2D(opponent_center_x - collision.box_extent.x, opponent_center_y + collision.box_extent.y);
    Vector2D opponent_y_rightdown = Vector2D(opponent_center_x + collision.box_extent.x, opponent_center_y + collision.box_extent.y);

    int x_position = opponent_y_leftdown.x / 32;
    int y_position = opponent_y_leftdown.y / 32;
    int object_in_destination = map_data.at(y_position).at(x_position);

    if (object_in_destination == kGround || object_in_destination == kBox) {
        return true;
    }
    
    x_position = opponent_y_rightdown.x / 32;
    y_position = opponent_y_rightdown.y / 32;
    object_in_destination = map_data.at(y_position).at(x_position);
    
    if (object_in_destination == kGround || object_in_destination == kBox) {
        return true;
    }
    return false;
}

std::vector<Vector2D> Field::ReadGroundData() {
    //y軸から見て、最初に見つけた地面チップの場所を記録
   //そのチップのx軸の地面チップは無視。
   //違う高さのy軸の地面チップを見つければ、そこの地点を記録。
    std::vector<Vector2D> left_pos_ground_data;
    int ignore_y = -1;
    for (unsigned x = 0; x < map_data.at(map_data.size() - 1).size(); x++) {
        for (unsigned y = 0; y < map_data.size(); y++) {

            if (map_data.at(y).at(x) == MapChipType::kGround) {
                if (ignore_y == y) {
                    break;
                }
                left_pos_ground_data.push_back(Vector2D(x, y));
                ignore_y = y;
                break;
            }

            if (y == map_data.size() - 1) {
                ignore_y = -1;
            }
        }
    }
    return left_pos_ground_data;
}

void Field::CreateGround(std::vector<Vector2D>& left_pos_ground_data) {
   
    for (auto left_pos : left_pos_ground_data) {

        int y_leftup_ground_pos = 0;
        int x_leftup_ground_pos = 0;
        left_pos.ToInt(x_leftup_ground_pos, y_leftup_ground_pos);

        std::vector<std::vector<int>> ground_data;
        int limit_x = -1;
        for (unsigned y = y_leftup_ground_pos; y < map_data.size(); y++) {
            std::vector<int> one_line_ground;

            for (unsigned x = x_leftup_ground_pos; x < map_data.at(y).size(); x++) {
              
                if (map_data.at(y).at(x) == MapChipType::kGround) {

                    if (limit_x >= 0) {
                        if (x > limit_x) {
                            break;
                        }
                        one_line_ground.push_back(map_data.at(y).at(x));
                        continue;
                    }

                    if (y != 0) {
                        if (map_data.at(y - 1).at(x) == MapChipType::kGround) {
                            limit_x = x;
                            break;
                        }
                    }
                    one_line_ground.push_back(map_data.at(y).at(x));

                    if (x == map_data.at(y).size() - 1) {
                        limit_x = x;
                    }
                }
                else {
                    limit_x = x;
                    break;
                }
            }
            ground_data.push_back(one_line_ground);
        }
        Ground* ground = new Ground();
        ground->Initialize();
        ground->SetGroundData(ground_data);

        float y_size = static_cast<float>(ground_data.size()) * 32.0f;
        float x_size = static_cast<float>(ground_data.at(ground_data.size()-1).size()) * 32.0f;

        float x_center = (static_cast<float>(x_leftup_ground_pos) * 32.0f) + (x_size/2.0f);
        float y_center = (static_cast<float>(y_leftup_ground_pos) * 32.0f) + (y_size/2.0f) +1;

        BoxCollisionParams collision = ground->GetBodyCollision();
        collision.center_position = Vector2D(x_center, y_center);
        collision.box_extent = Vector2D(x_size / 2.0f, y_size / 2.0f);
        collision.object_type = kGROUND;
        ground->SetBodyCollision(collision);

        StageObjectList.push_back(ground);
    }
}


void Field::AddStageObject(Character*)
{
}
