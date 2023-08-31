#include "Field.h"
#include "DxLib.h"
#include "../Source/System/ScreenInfo.h"
#include <iostream>
#include "../CSVData/CSVFile.h"
#include "EMapChipType.h"
#include "../Source/Utility/Vector2D.h"
#include "../Source/Utility/BoxCollisionParams.h"
#include "Ground/Ground.h";
#include "Ground/Wall.h"
#include "Ground/Box.h"

namespace {
    const float map_chip_size = 32.f;
    const float wall_y_size = 40.f;
    const float box_y_size = 40.f;
    const float ground_y_size = 48.f;
    const float half = 2.0f;
    const int vector_index_adjust = 1;
    const int initialize_ignore_limit = -1;
    const int zero_ground_data = 0;

    //地面の画像枚数
    const int wall_mapchip_file_num = 3;
    //画像データの連番数
    //1枚目の連番になる。
    const int wall_first_sequence = 0;

    //地面の画像枚数
    const int ground_mapchip_file_num = 9;
    //画像データの連番数
    //1枚目の連番になる。
    const int ground_first_sequence = 37;
}

Field::Field()
    :csv_file_reader(nullptr)
{
}

Field::~Field()
{
}

void Field::Update(float DeltaTime)
{
}

void Field::Initialize() {

}

void Field::Draw(const Vector2D& screen_offset){

    DrawMap();
   /* for (auto object : StageObjectList) {
        object->Draw(screen_offset);
    }*/
}

bool Field::InitializeField(const char* map_file_name){

    //グラフィックハンドル読み込み
    char file_name[100];
    for (int i = ground_first_sequence, j = 0; j < ground_mapchip_file_num; i++, j++) {
        snprintf(file_name, sizeof(file_name), "Resources/Images/mapchip_0%d.bmp", i);
       // ground_graphic_handle[j] = LoadGraph(file_name);

        if (j <= 2) {
            ground_graphic_handle_upper[j%3] = LoadGraph(file_name);
        }

        if (2 < j && j <= 5) {
            ground_graphic_handle_middle[j%3] = LoadGraph(file_name);
        }

        if (5 < j && j <= 8) {
            ground_graphic_handle_bottom[j%3] = LoadGraph(file_name);
        }
    }


    //char file_name2[100];
    for (int i = wall_first_sequence, j = 0; j < ground_mapchip_file_num; i++, j++) {
        snprintf(file_name, sizeof(file_name), "Resources/Images/mapchip_00%d.bmp", i);
        wall_graphic_handle[j] = LoadGraph(file_name);
    }

    box_graphic_handle = LoadGraph("Resources/Images/mapchip_017.bmp");
    LoadDivGraph("Resources/Images/mapchip_017.bmp", 7, 4, 2, 32, 32, gimmick_box_graphic_handle);

    //CSV読み込み
	csv_file_reader = new CSVFile();
	if (!csv_file_reader->Read(map_file_name)) {
		std::cout << u8"マップの初期化に失敗しました" << std::endl;
		return false;
	}
	map_data = csv_file_reader->GetData();

    ScreenInfo* screen_info = ScreenInfo::GetInstance();
    screen_info->SetMapSize(map_data.size(), map_data.at(map_data.size() - 1).size());

    //以下でフィールドの地形オブジェクトを作成
   
    /*std::vector<Vector2D> load_ground_data = ReadGroundData();
    CreateGround(load_ground_data);

    std::vector<GroundObjectInfo> load_wall = ReadWallData();
    CreateWall(load_wall);

    CreateBox();*/
}

bool Field::CheckMove(const Vector2D& move_to_position, const BoxCollisionParams& collision) {

    //float opponent_center_x = move_to_position.x + collision.center_position.x;
    //float opponent_center_y = move_to_position.y + collision.center_position.y;

    ////中心座標 - 横幅の半分、中心座標 + 縦幅の半分
    //Vector2D opponent_x_leftup = Vector2D(opponent_center_x - collision.box_extent.x, opponent_center_y - collision.box_extent.y);
    //Vector2D opponent_x_rightup = Vector2D(opponent_center_x + collision.box_extent.x, opponent_center_y - collision.box_extent.y);

    //int x_position = opponent_x_leftup.x / 32;
    //int y_position = opponent_x_leftup.y / 32;
    //int object_in_destination = map_data.at(y_position).at(x_position);

    //if (object_in_destination == kGround || object_in_destination == kWall || object_in_destination == kBox) {
    //    return false;
    //}

    //x_position = opponent_x_rightup.x / 32;
    //y_position = opponent_x_rightup.y / 32;
    //object_in_destination = map_data.at(y_position).at(x_position);

    //if (object_in_destination == kGround || object_in_destination == kWall || object_in_destination == kBox) {
    //    return false;
    //}


    //////中心座標 - 横幅の半分、中心座標 + 縦幅の半分
    //Vector2D opponent_y_leftdown = Vector2D(opponent_center_x - collision.box_extent.x, opponent_center_y + collision.box_extent.y);
    //Vector2D opponent_y_rightdown = Vector2D(opponent_center_x + collision.box_extent.x, opponent_center_y + collision.box_extent.y);

    //x_position = opponent_y_leftdown.x / 32-1;
    //y_position = opponent_y_leftdown.y / 32-1;
    //object_in_destination = map_data.at(y_position).at(x_position);

    //if (object_in_destination == kGround || object_in_destination == kBox) {
    //    return false;
    //}

    //x_position = opponent_y_rightdown.x / 32-1;
    //y_position = opponent_y_rightdown.y / 32-1;
    //object_in_destination = map_data.at(y_position).at(x_position);

    //if (object_in_destination == kGround || object_in_destination == kBox) {
    //    return false;
    //}
    //return true;

    float opponent_center_x = move_to_position.x + collision.center_position.x;
    float opponent_center_y = move_to_position.y + collision.center_position.y;

    //中心座標 - 横幅の半分、中心座標 + 縦幅の半分
    Vector2D opponent_y_leftdown = Vector2D(opponent_center_x - collision.box_extent.x, opponent_center_y + collision.box_extent.y);
    Vector2D opponent_y_rightdown = Vector2D(opponent_center_x + collision.box_extent.x, opponent_center_y + collision.box_extent.y);

    int x_position = opponent_y_leftdown.x / map_chip_size;
    int y_position = opponent_y_leftdown.y / map_chip_size;
    int object_in_destination = map_data.at(y_position).at(x_position);


    for(auto obj : StageObjectList) {
   
        BoxCollisionParams ground_collision = obj->GetBodyCollision();
      
        float distance_x = abs(opponent_center_x - ground_collision.center_position.x);
        float distance_y = abs(opponent_center_y - ground_collision.center_position.y);
        //distance_y += 3;
        float size_x = collision.box_extent.x + ground_collision.box_extent.x;
        float size_y = collision.box_extent.y + ground_collision.box_extent.y;

        if (distance_x < size_x && distance_y < size_y) {
           return false;
        }
    }
    return true;
}

bool Field::CheckStande(Vector2D& move_to_position, const BoxCollisionParams& collision){

    float opponent_center_x = move_to_position.x + collision.center_position.x;
    float opponent_center_y = move_to_position.y + collision.center_position.y;

    //中心座標 - 横幅の半分、中心座標 + 縦幅の半分
    Vector2D opponent_y_leftdown = Vector2D(opponent_center_x - collision.box_extent.x, opponent_center_y + collision.box_extent.y + collision.move_velocity.y);
    Vector2D opponent_y_rightdown = Vector2D(opponent_center_x + collision.box_extent.x, opponent_center_y + collision.box_extent.y + collision.move_velocity.y);

    int x_position = opponent_y_leftdown.x / map_chip_size;
    int y_position = opponent_y_leftdown.y / map_chip_size;
    int object_in_destination = map_data.at(y_position).at(x_position);

    if (object_in_destination == kGROUND || object_in_destination == kBOX || object_in_destination == kWALL) {
        return true;
    }
    
    x_position = opponent_y_rightdown.x / map_chip_size;
    y_position = opponent_y_rightdown.y / map_chip_size;
    object_in_destination = map_data.at(y_position).at(x_position);
    
    if (object_in_destination == kGROUND || object_in_destination == kBOX || object_in_destination == kWALL) {
        return true;
    }
    return false;
}

void Field::DrawMap() {

    //自身から上に向かって、同じ地面のチップがどれくらいあるか調べる。
    //存在した数が分かれば、自身がどの層か分かるので、その層にあったチップを渡す。
    for (unsigned y = 0; y < map_data.size(); y++) {
        std::vector<int> one_line_ground;

        for (unsigned x = 0; x < map_data.at(y).size(); x++) {

            int graphic_handle = 0;
            switch (map_data.at(y).at(x)) {

            case kGROUND:
                graphic_handle = GetGroundGraphic(x, y);
                break;

            case kWALL:
                graphic_handle = wall_graphic_handle[0];
                break;

            case kBOX:
                graphic_handle = box_graphic_handle;
                break;
            }

            int x_graphic_size = 0;
            int y_graphic_size = 0;
            GetGraphSize(graphic_handle, &x_graphic_size, &y_graphic_size);

            ScreenInfo* screen_info = ScreenInfo::GetInstance();
            int display_x_top = static_cast<int>(screen_info->GetLeftX()) + map_chip_size * x;
            int display_y_top = static_cast<int>(screen_info->GetLeftY()) + map_chip_size * y;
            //描画する。xとyの位置に、その位置に設定されているハンドル値による画像を描画する。
            DrawGraph(display_x_top, display_y_top, graphic_handle, true);
            //デバック用
            unsigned int color = GetColor(255, 255, 255);
            DrawBox(display_x_top, display_y_top, display_x_top + x_graphic_size, display_y_top + y_graphic_size, color, false);
        }
    }
}

int Field::GetGroundGraphic(const int x, const int y) {

    int ground_chip_num = 0;
    int upper_y = y - 1;

    if (upper_y <= 0) {
        upper_y = 0;
    }

    for (int y_count = y; y_count >= 0; y_count--) {
        if (map_data.at(upper_y).at(x) == kGROUND) {
            upper_y--;
            ground_chip_num++;

        }else {
            break;
        }
    }

    if (ground_chip_num == 0) {
        return ground_graphic_handle_upper[x % 3];

    }else if (ground_chip_num == 1) {
        return ground_graphic_handle_middle[x % 3];

    }else if(ground_chip_num >= 2) {
        return ground_graphic_handle_bottom[x % 3];
    }
   
}

std::vector<Vector2D> Field::ReadGroundData() {
    //y軸から見て、最初に見つけた地面チップの場所を記録
   //そのチップのx軸の地面チップは無視。
   //違う高さのy軸の地面チップを見つければ、そこの地点を記録。
    std::vector<Vector2D> left_pos_ground_data;
    int ignore_y = initialize_ignore_limit;
    for (unsigned x = 0; x < map_data.at(map_data.size() - 1).size(); x++) {
        for (unsigned y = 0; y < map_data.size(); y++) {

            if (map_data.at(y).at(x) == MapChipType::kGROUND) {
                if (ignore_y == y) {
                    break;
                }
                left_pos_ground_data.push_back(Vector2D(x, y));
                ignore_y = y;
                break;
            }

            if (y == map_data.size() - vector_index_adjust) {
                ignore_y = initialize_ignore_limit;
            }
        }
    }
    return left_pos_ground_data;
}

void Field::CreateGround(std::vector<Vector2D>& left_pos_ground_data) {
   
    for (auto& left_pos : left_pos_ground_data) {

        int y_leftup_ground_pos = 0;
        int x_leftup_ground_pos = 0;
        left_pos.ToInt(x_leftup_ground_pos, y_leftup_ground_pos);

        std::vector<std::vector<int>> ground_data;
        int limit_x = -1;
        for (unsigned y = y_leftup_ground_pos; y < map_data.size(); y++) {
            std::vector<int> one_line_ground;

            for (unsigned x = x_leftup_ground_pos; x < map_data.at(y).size(); x++) {
              
                if (map_data.at(y).at(x) == MapChipType::kGROUND) {

                    if (limit_x >= 0) {
                        if (x >= limit_x) {
                            break;
                        }
                        one_line_ground.push_back(map_data.at(y).at(x));
                        continue;
                    }

                    if (y != 0) {
                        if (map_data.at(y - vector_index_adjust).at(x) == MapChipType::kGROUND) {
                            limit_x = x;
                            break;
                        }
                    }
                    one_line_ground.push_back(map_data.at(y).at(x));

                    if (x == map_data.at(y).size() - vector_index_adjust) {
                        limit_x = x+1;
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

        float y_size = static_cast<float>(ground_data.size()) * ground_y_size;
        float x_size = static_cast<float>(ground_data.at(ground_data.size()-1).size()) * map_chip_size;

        float x_center = (static_cast<float>(x_leftup_ground_pos) * map_chip_size) + (x_size / half);
        float y_center = (static_cast<float>(y_leftup_ground_pos) * map_chip_size) + (y_size / half);

        BoxCollisionParams collision = ground->GetBodyCollision();
        collision.center_position = Vector2D(x_center, y_center);
        collision.box_extent = Vector2D(x_size / half, y_size / half);
        collision.object_type = CollisionObjectType::kGROUND_TYPE;
        ground->SetBodyCollision(collision);

        StageObjectList.push_back(ground);
    }
}

std::vector<Field::GroundObjectInfo> Field::ReadWallData() {

    //y軸から見て、最初に見つけた地面チップの場所を記録
 //そのチップのx軸の地面チップは無視。
 //違う高さのy軸の地面チップを見つければ、そこの地点を記録。
    std::vector<GroundObjectInfo> left_pos_ground_data;
    int ignore_y = initialize_ignore_limit;
    for (unsigned x = 0; x < map_data.at(map_data.size() - vector_index_adjust).size(); x++) {
        for (unsigned y = 0; y < map_data.size(); y++) {

            int left_up_pos = map_data.at(y).at(x);
            if (left_up_pos == MapChipType::kWALL) {
                if (ignore_y == y) {
                    break;
                }
                GroundObjectInfo info;
                info.left_up_pos = Vector2D(x, y);
                info.collision.object_type = CollisionObjectType::kGROUND_TYPE;
               
                left_pos_ground_data.push_back(info);
                ignore_y = y;
                break;
            }

            if (y == map_data.size() - vector_index_adjust) {
                ignore_y = initialize_ignore_limit;
            }
        }
    }
    return left_pos_ground_data;
}


void Field::CreateWall(std::vector<GroundObjectInfo>& left_pos_wall_data) {

    for (auto& wall_info : left_pos_wall_data) {

        int y_leftup_ground_pos = 0;
        int x_leftup_ground_pos = 0;
        wall_info.left_up_pos.ToInt(x_leftup_ground_pos, y_leftup_ground_pos);

        std::vector<std::vector<int>> ground_data;
        int limit_x = -1;
        for (unsigned y = y_leftup_ground_pos; y < map_data.size(); y++) {
            std::vector<int> one_line_ground;

            for (unsigned x = x_leftup_ground_pos; x < map_data.at(y).size(); x++) {

                if (map_data.at(y).at(x) == MapChipType::kWALL || map_data.at(y).at(x) == MapChipType::kBROKEN_WALL) {

                    //リミットが設定されているときはここで格納していく。
                    if (limit_x >= 0) {
                        if (x >= limit_x) {
                            break;
                        }
                        one_line_ground.push_back(map_data.at(y).at(x));
                        continue;
                    }

                    //リミットが設定されていないときはこのしたで格納。
                    //yが0の時は上のチップは確認しない
                    if (y != 0) {
                        if (map_data.at(y - vector_index_adjust).at(x) == MapChipType::kWALL) {
                            limit_x = x;
                            break;
                        }
                    }
                    one_line_ground.push_back(map_data.at(y).at(x));

                    if (x == map_data.at(y).size() - vector_index_adjust) {
                        limit_x = x + map_chip_size;
                    }
                }
                else {
                    limit_x = x;
                    break;
                }
            }
            if(one_line_ground.size() != zero_ground_data){
                ground_data.push_back(one_line_ground);
            }
        }
        Wall* ground = new Wall();
        ground->Initialize();
        ground->SetGroundData(ground_data);

        float y_size = static_cast<float>(ground_data.size()) * wall_y_size;
        float x_size = static_cast<float>(ground_data.at(ground_data.size() - vector_index_adjust).size()) * map_chip_size;

        float x_center = (static_cast<float>(x_leftup_ground_pos) * map_chip_size) + (x_size / half);
        float y_center = (static_cast<float>(y_leftup_ground_pos) * map_chip_size) + (y_size / half);

        BoxCollisionParams collision = ground->GetBodyCollision();
        collision.left_up_position = wall_info.left_up_pos;
        collision.center_position = Vector2D(x_center, y_center);
        collision.box_extent = Vector2D(x_size / half, y_size / half);
        //collision.object_type = kGROUND;
        ground->SetBodyCollision(collision);

        StageObjectList.push_back(ground);
    }
}

void Field::CreateBox() {

    for (unsigned y = 0; y < map_data.size(); y++) {
        for (unsigned x = 0; x < map_data.at(y).size(); x++) {
            Box* box = nullptr;
            float x_center = 0.f;
            float y_center = 0.f;
            BoxCollisionParams collision;

            switch (map_data.at(y).at(x)) {
            case kBOX:
                box = new Box();
                box->Initialize();

                x_center = (static_cast<float>(x) * map_chip_size) + (map_chip_size / half);
                y_center = (static_cast<float>(y) * map_chip_size) + (box_y_size / half);

                collision = box->GetBodyCollision();
                collision.left_up_position = Vector2D(x, y);
                collision.center_position = Vector2D(x_center, y_center);
                collision.box_extent = Vector2D(map_chip_size / half, box_y_size/ half);
               // collision.object_type = kGROUND;
                box->SetBodyCollision(collision);
                StageObjectList.push_back(box);
                break;

            case kGIMMICK_BOX:
                //実装予定
                break;

               
            }
        }
    }
}


void Field::AddStageObject(Character*)
{
}
