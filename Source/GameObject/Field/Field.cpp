#include "Field.h"
#include "DxLib.h"
#include "../Source/System/ScreenInfo.h"
#include <iostream>
#include <typeinfo>
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
    ,ground_graphic_handle_upper()
    ,ground_graphic_handle_middle()
    ,ground_graphic_handle_bottom()
    ,wall_graphic_handle()
    ,box_graphic_handle()
    ,gimmick_box_graphic_handle()
{
}

Field::~Field()
{
}

void Field::Update(float delta_time) {
    __super::Update(delta_time);
}

void Field::Initialize() {
    __super::Initialize();
}

void Field::Finalize() {
    stage_object_list.clear();
    delete(csv_file_reader);
    csv_file_reader = nullptr;
}

void Field::Draw(const Vector2D& screen_offset){
    __super::Draw(screen_offset);
    DrawMap();
}

bool Field::InitializeField(const char* map_file_name){

    //グラフィックハンドル読み込み
    char file_name[100];
    for (int i = ground_first_sequence, j = 0; j < ground_mapchip_file_num; i++, j++) {
        snprintf(file_name, sizeof(file_name), "Resources/Images/mapchip_0%d.bmp", i);
      
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

}

bool Field::InitializeStageObjectPosition() {
    
    for (auto& stage_obj : stage_object_list) {

        switch (stage_obj->GetBodyCollision().object_type) {

        case kPLAYER_TYPE:
            SetInitialPosition(*stage_obj, kPLAYER_START);
            break;
        case kENEMY_TYPE:
            SetInitialPosition(*stage_obj, kENEMY);
            break;
        }
    }
    return false;
}

bool Field::CheckMove(const Vector2D& move_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) {

    float opponent_center_x = move_to_position.x + move_amount.x + collision.center_position.x;
    float opponent_center_y = move_to_position.y + collision.center_position.y;
   
   /* float opponent_center_x = move_to_position.x + collision.center_position.x;
    float opponent_center_y = move_to_position.y + collision.center_position.y;*/

    //中心座標 - 横幅の半分、中心座標 + 縦幅の半分
    Vector2D opponent_x_leftup = Vector2D(opponent_center_x - collision.box_extent.x, opponent_center_y - collision.box_extent.y);
    Vector2D opponent_x_rightup = Vector2D(opponent_center_x + collision.box_extent.x, opponent_center_y - collision.box_extent.y);

    int x_position = opponent_x_leftup.x / 32;
    int y_position = opponent_x_leftup.y / 32;
    int object_in_destination = map_data.at(y_position).at(x_position);

    if (object_in_destination == kGROUND || object_in_destination == kWALL || object_in_destination == kBOX) {

        ScreenInfo* screen_info = ScreenInfo::GetInstance();
        float ground_center_pos_x = (screen_info->GetLeftX() + map_chip_size * x_position) + (map_chip_size / 2);
        float ground_center_pos_y = (screen_info->GetLeftY() + map_chip_size * y_position) + (map_chip_size / 2);

        float distance_x = abs(opponent_center_x - ground_center_pos_x);
        float distance_y = abs(opponent_center_y - ground_center_pos_y);
        //distance_y += 3;
        float size_x = collision.box_extent.x + (map_chip_size / 2);
        float size_y = collision.box_extent.y + (map_chip_size / 2);

        if (distance_x < size_x && distance_y < size_y) {
            return false;
        }
       // return false;
    }

    x_position = opponent_x_rightup.x / 32;
    y_position = opponent_x_rightup.y / 32;
    object_in_destination = map_data.at(y_position).at(x_position);

    if (object_in_destination == kGROUND || object_in_destination == kWALL || object_in_destination == kBOX) {
        ScreenInfo* screen_info = ScreenInfo::GetInstance();
        float ground_center_pos_x = (screen_info->GetLeftX() + map_chip_size * x_position) + (map_chip_size / 2);
        float ground_center_pos_y = (screen_info->GetLeftY() + map_chip_size * y_position) + (map_chip_size / 2);

        float distance_x = abs(opponent_center_x - ground_center_pos_x);
        float distance_y = abs(opponent_center_y - ground_center_pos_y);
        //distance_y += 3;
        float size_x = collision.box_extent.x + (map_chip_size / 2);
        float size_y = collision.box_extent.y + (map_chip_size / 2);

        if (distance_x < size_x && distance_y < size_y) {
            return false;
        }
       // return false;
    }


    opponent_center_x = move_to_position.x + collision.center_position.x;
    opponent_center_y = move_to_position.y + move_amount.y + collision.center_position.y;

    ////中心座標 - 横幅の半分、中心座標 + 縦幅の半分
    Vector2D opponent_y_leftdown = Vector2D(opponent_center_x - collision.box_extent.x, opponent_center_y + collision.box_extent.y);
    Vector2D opponent_y_rightdown = Vector2D(opponent_center_x + collision.box_extent.x, opponent_center_y + collision.box_extent.y);

    x_position = opponent_y_leftdown.x / 32;
    y_position = opponent_y_leftdown.y / 32;
    object_in_destination = map_data.at(y_position).at(x_position);

    if (object_in_destination == kGROUND || object_in_destination == kWALL || object_in_destination == kBOX) {
        ScreenInfo* screen_info = ScreenInfo::GetInstance();
        float ground_center_pos_x = (screen_info->GetLeftX() + map_chip_size * x_position) + (map_chip_size / 2);
        float ground_center_pos_y = (screen_info->GetLeftY() + map_chip_size * y_position) + (map_chip_size / 2);

        float distance_x = abs(opponent_center_x - ground_center_pos_x);
        float distance_y = abs(opponent_center_y - ground_center_pos_y);
        //distance_y += 3;
        float size_x = collision.box_extent.x + (map_chip_size / 2);
        float size_y = collision.box_extent.y + (map_chip_size / 2);

        if (distance_x < size_x && distance_y < size_y) {
            return false;
        }
        // return false;
    }

    x_position = opponent_y_rightdown.x / 32;
    y_position = opponent_y_rightdown.y / 32;
    object_in_destination = map_data.at(y_position).at(x_position);

    if (object_in_destination == kGROUND || object_in_destination == kWALL || object_in_destination == kBOX) {
        ScreenInfo* screen_info = ScreenInfo::GetInstance();
        float ground_center_pos_x = (screen_info->GetLeftX() + map_chip_size * x_position) + (map_chip_size / 2);
        float ground_center_pos_y = (screen_info->GetLeftY() + map_chip_size * y_position) + (map_chip_size / 2);

        float distance_x = abs(opponent_center_x - ground_center_pos_x);
        float distance_y = abs(opponent_center_y - ground_center_pos_y);
        //distance_y += 3;
        float size_x = collision.box_extent.x + (map_chip_size / 2);
        float size_y = collision.box_extent.y + (map_chip_size / 2);

        if (distance_x < size_x && distance_y < size_y) {

            return false;
        }
        //return false;
    }
    return true;

    //float opponent_center_x = move_to_position.x + collision.center_position.x;
    //float opponent_center_y = move_to_position.y + collision.center_position.y;

    ////中心座標 - 横幅の半分、中心座標 + 縦幅の半分
    //Vector2D opponent_y_leftdown = Vector2D(opponent_center_x - collision.box_extent.x, opponent_center_y + collision.box_extent.y);
    //Vector2D opponent_y_rightdown = Vector2D(opponent_center_x + collision.box_extent.x, opponent_center_y + collision.box_extent.y);

    //int x_position = opponent_y_leftdown.x / map_chip_size;
    //int y_position = opponent_y_leftdown.y / map_chip_size;
    //int object_in_destination = map_data.at(y_position).at(x_position);


    //for(auto obj : StageObjectList) {
   
    //    BoxCollisionParams ground_collision = obj->GetBodyCollision();
    //  
    //    float distance_x = abs(opponent_center_x - ground_collision.center_position.x);
    //    float distance_y = abs(opponent_center_y - ground_collision.center_position.y);
    //    //distance_y += 3;
    //    float size_x = collision.box_extent.x + ground_collision.box_extent.x;
    //    float size_y = collision.box_extent.y + ground_collision.box_extent.y;

    //    if (distance_x < size_x && distance_y < size_y) {
    //       return false;
    //    }
    //}
    //return true;
}

void Field::AddStageObject(StageObject& stage_object) {
    stage_object_list.push_back(&stage_object);
}


bool Field::CheckMoveToX(const Vector2D& move_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) {

    //X方向にだけ動いた移動先を求める
    float opponent_center_x = move_to_position.x + move_amount.x + collision.center_position.x;
    float opponent_center_y = move_to_position.y + collision.center_position.y;
    Vector2D opponent_center = Vector2D(opponent_center_x, opponent_center_y);

    //中心座標 - 横幅の半分、中心座標 + 縦幅の半分
    Vector2D opponent_x_leftup = Vector2D(opponent_center_x - collision.box_extent.x, opponent_center_y - collision.box_extent.y);
    Vector2D opponent_x_rightup = Vector2D(opponent_center_x + collision.box_extent.x, opponent_center_y - collision.box_extent.y);
    Vector2D opponent_x_leftdown = Vector2D(opponent_center_x - collision.box_extent.x, opponent_center_y + collision.box_extent.y);
    Vector2D opponent_x_rightdown = Vector2D(opponent_center_x + collision.box_extent.x, opponent_center_y + collision.box_extent.y);
    Vector2D opponent_x_leftmiddle = Vector2D(opponent_center_x + collision.box_extent.x, opponent_center_y);
    Vector2D opponent_x_rightmiddle = Vector2D(opponent_center_x - collision.box_extent.x, opponent_center_y);
   
    std::vector<Vector2D> check_positions =
    { opponent_center,opponent_x_leftup,opponent_x_rightup,opponent_x_leftdown,opponent_x_rightdown,opponent_x_leftmiddle,opponent_x_rightmiddle };

    for(auto& check_position : check_positions) {
        if (!CheckHitGround(check_position, opponent_center, collision)) {

            return false;
        }
    }
    return true;
}

bool Field::CheckMoveToY(const Vector2D& move_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) {

    float opponent_center_x = move_to_position.x + collision.center_position.x;
    float opponent_center_y = move_to_position.y + move_amount.y + collision.center_position.y;
    Vector2D opponent_center = Vector2D(opponent_center_x, opponent_center_y);

    //中心座標 - 横幅の半分、中心座標 + 縦幅の半分
    Vector2D opponent_y_leftdown = Vector2D(opponent_center_x - collision.box_extent.x, opponent_center_y + collision.box_extent.y);
    Vector2D opponent_y_rightdown = Vector2D(opponent_center_x + collision.box_extent.x, opponent_center_y + collision.box_extent.y);
    Vector2D opponent_y_left_top = Vector2D(opponent_center_x - collision.box_extent.x, opponent_center_y - collision.box_extent.y);
    Vector2D opponent_y_right_top = Vector2D(opponent_center_x + collision.box_extent.x, opponent_center_y - collision.box_extent.y);
    Vector2D opponent_y_left_middle = Vector2D(opponent_center_x, opponent_center_y - collision.box_extent.y);
    Vector2D opponent_y_right_middle = Vector2D(opponent_center_x, opponent_center_y - collision.box_extent.y);

    std::vector<Vector2D> check_positions =
    { opponent_y_leftdown, opponent_y_rightdown, opponent_y_left_top, opponent_y_right_top, opponent_y_left_middle,opponent_y_right_middle };


    for (auto& check_position : check_positions) {
        if (!CheckHitGround(check_position, opponent_center, collision)) {
            return false;
        }
    }
    return true;
}

bool Field::CheckHitGround(Vector2D& opponent_check_position, const Vector2D& oppnent_center, const BoxCollisionParams& collision) {

    int x_position = opponent_check_position.x / map_chip_size;
    int y_position = opponent_check_position.y / map_chip_size;
    int object_in_destination = map_data.at(y_position).at(x_position);

    if (object_in_destination == kGROUND || object_in_destination == kWALL || object_in_destination == kBOX) {
        ScreenInfo* screen_info = ScreenInfo::GetInstance();
        int x_left = screen_info->GetLeftX() + map_chip_size * int(x_position);
        int y_down = screen_info->GetLeftY() + map_chip_size * int(y_position);
        float ground_center_pos_x = (screen_info->GetLeftX() + map_chip_size * x_position) + (map_chip_size / 2);
        float ground_center_pos_y = (screen_info->GetLeftY() + map_chip_size * y_position) + (map_chip_size / 2);

        float distance_x = abs(oppnent_center.x - ground_center_pos_x);
        float distance_y = abs(oppnent_center.y - ground_center_pos_y);
        //distance_y += 3;
        float size_x = collision.box_extent.x + (map_chip_size / 2);
        float size_y = collision.box_extent.y + (map_chip_size / 2);

        //差が微小の場合は当たったと見なすための処理
        if (abs(distance_x - size_x) <= .1f) {
            distance_x = size_x;
        }
        if (abs(distance_y - size_y) <= .1f) {
            distance_y = size_y;
        }


        if (distance_x <= size_x && distance_y <= size_y) { 
            return false;
        }
    }
    return true;
}

bool Field::CheckStande(Vector2D& move_to_position, const BoxCollisionParams& collision){

    float opponent_center_x = move_to_position.x + collision.center_position.x;
    float opponent_center_y = move_to_position.y + collision.center_position.y;

    //中心座標 - 横幅の半分、中心座標 + 縦幅の半分
    Vector2D opponent_y_leftdown = Vector2D(opponent_center_x - collision.box_extent.x, opponent_center_y + collision.box_extent.y);
    Vector2D opponent_y_rightdown = Vector2D(opponent_center_x + collision.box_extent.x, opponent_center_y + collision.box_extent.y);

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

void Field::SetInitialPosition(StageObject& stage_obj, const MapChipType chip_type) {
   
    ScreenInfo* screen_info = ScreenInfo::GetInstance();
   
    for (unsigned y = 0; y < map_data.size(); y++) {
        for (unsigned x = 0; x < map_data.at(y).size(); x++) {

            if (map_data.at(y).at(x) == chip_type) {

                const BoxCollisionParams collison = stage_obj.GetBodyCollision();
                //キャラクターの画像サイズが、キャラが描かれている範囲より大きいので、左上座標をそのままセットすると、
                //透過されている部分を含めた左上座標の位置に描画される。
                //それを避けるため、センターポジションまでのオフセット分だけ引いて、キャラが描かれている左上座標を、
                //指定したマップの座標位置まで持っていく必要がある。
                int x_left = (screen_info->GetLeftX() + x * map_chip_size) - collison.center_position.x;
                int y_top = (screen_info->GetLeftY() + y * map_chip_size) - collison.center_position.y;
                stage_obj.SetPosition(Vector2D(x_left, y_top));

                float center_pos_x = stage_obj.GetPosition().x + collison.center_position.x;
                float center_pos_y = stage_obj.GetPosition().y + collison.center_position.y;
                stage_obj.SetCenterPosition(Vector2D(center_pos_x, center_pos_y));

                return;
            }
        }
    }
}
