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
#include "../StageObject/Character/Character.h"
#include <vector>


namespace {
    const float MAP_CHIP_SIZE = 32.f;
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
    __super::Finalize();

    stage_object_list.clear();
    delete(csv_file_reader);
    csv_file_reader = nullptr;
}

void Field::Draw(const Vector2D& screen_offset){
    __super::Draw(screen_offset);
    DrawMap(screen_offset);
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
    screen_info->SetMapSize(map_data.at(map_data.size() - 1).size(), map_data.size());
}

//bool Field::InitializeStageObjectPosition() {
//    
//    for (auto& stage_obj : stage_object_list) {
//        BoxCollisionParams stage_object_collision = stage_obj->GetBodyCollision();
//        switch (stage_object_collision.object_type) {
//
//        case kPLAYER_TYPE:
//            SetInitialPosition(*stage_obj, kPLAYER_START);
//            break;
//        case kENEMY_TYPE:
//            SetInitialPosition(*stage_obj, kBASE_ENEMY);
//            break;
//        case kITEM_TYPE:
//            SetInitialPosition(*stage_obj, kCOIN);
//            break;
//        }
//    }
//    return false;
//}

void Field::AddStageObject(StageObject& stage_object) {
    stage_object_list.push_back(&stage_object);
}

void Field::DeleteStageObject(StageObject* stage_object) {
    auto remove_start = std::remove(stage_object_list.begin(), stage_object_list.end(), stage_object);
    stage_object_list.erase(remove_start, stage_object_list.end());
}

bool Field::CheckMoveToX(const Vector2D& move_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) {

    //X方向にだけ動いた移動先を求める
    float opponent_center_x = move_to_position.x + move_amount.x + collision.center_position.x ;
    float opponent_center_y = move_to_position.y + collision.center_position.y ;
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

    //現在表示中の左上座標を足す
    float opponent_center_x = move_to_position.x + collision.center_position.x;
    float opponent_center_y = move_to_position.y + move_amount.y + collision.center_position.y ;
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

    int x_position = opponent_check_position.x / MAP_CHIP_SIZE;
    int y_position = opponent_check_position.y / MAP_CHIP_SIZE;
    int object_in_destination = map_data.at(y_position).at(x_position);

    if (object_in_destination == kGROUND || object_in_destination == kWALL || object_in_destination == kBOX) {
        ScreenInfo* screen_info = ScreenInfo::GetInstance();
        //マップチップの左上座標を算出
        int x_left = screen_info->GetLeftX() + MAP_CHIP_SIZE * int(x_position);
        int y_down = screen_info->GetLeftY() + MAP_CHIP_SIZE * int(y_position);

        //マップチップの中心座標を算出
        float ground_center_pos_x = (screen_info->GetLeftX() + MAP_CHIP_SIZE * x_position)  + (MAP_CHIP_SIZE / 2);
        float ground_center_pos_y = (screen_info->GetLeftY() + MAP_CHIP_SIZE * y_position)  + (MAP_CHIP_SIZE / 2);

        float distance_x = abs(oppnent_center.x - ground_center_pos_x);
        float distance_y = abs(oppnent_center.y - ground_center_pos_y);
        float size_x = collision.box_extent.x + (MAP_CHIP_SIZE / 2);
        float size_y = collision.box_extent.y + (MAP_CHIP_SIZE / 2);

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

void Field::DrawMap(const Vector2D& screen_offset) {
    ScreenInfo* screen_info = ScreenInfo::GetInstance();

    //描画開始マップチップ
    int draw_x_chip = static_cast<int>(screen_offset.x / MAP_CHIP_SIZE);
    int draw_y_chip = static_cast<int>(screen_offset.y / MAP_CHIP_SIZE);

    //描画するマップチップの最大値
    int draw_limit_x = draw_x_chip + screen_info->GetResolutionX() / MAP_CHIP_SIZE + 2;
    int draw_limit_y = draw_y_chip + screen_info->GetResolutionY() / MAP_CHIP_SIZE + 2;

    //全体マップのマップチップの最大値
    int limit_size_x = screen_info->GetMapSize().x / MAP_CHIP_SIZE;
    int limit_size_y = screen_info->GetMapSize().y / MAP_CHIP_SIZE;

    //描画するマップチップの最大値が、全体マップを超えていないか確認
    if (draw_limit_x >= limit_size_x) {
        draw_limit_x = limit_size_x;
    }

    if (draw_limit_y >= limit_size_y) {
        draw_limit_y = limit_size_y;
    }

    //自身から上に向かって、同じ地面のチップがどれくらいあるか調べる。
    //存在した数が分かれば、自身がどの層か分かるので、その層にあったチップを渡す。
    for (unsigned y = draw_y_chip; y < draw_limit_y; y++) {
        
        std::vector<int> one_line_ground;
        for (unsigned x = draw_x_chip; x < draw_limit_x; x++) {

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
            int display_x_top = static_cast<int>(screen_info->GetLeftX()) + MAP_CHIP_SIZE * x;
            int display_y_top = static_cast<int>(screen_info->GetLeftY()) + MAP_CHIP_SIZE * y;
            //マップ全体におけるマップチップの座標から、スクリーン座標の左上座標を引く
            DrawGraph(display_x_top - screen_offset.x, display_y_top - screen_offset.y, graphic_handle, true);
            //デバック用
            unsigned int color = GetColor(255, 255, 255);
            DrawBox(display_x_top - screen_offset.x, display_y_top - screen_offset.y, display_x_top - screen_offset.x + x_graphic_size, display_y_top - screen_offset.y + y_graphic_size, color, false);
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

//void Field::SetInitialPosition(StageObject& stage_obj, const MapChipType chip_type) {
//   
//    ScreenInfo* screen_info = ScreenInfo::GetInstance();
//   
//    for (unsigned y = 0; y < map_data.size(); y++) {
//        for (unsigned x = 0; x < map_data.at(y).size(); x++) {
//
//            if (map_data.at(y).at(x) == chip_type) {
//
//                const BoxCollisionParams collison = stage_obj.GetBodyCollision();
//                //キャラクターの画像サイズが、キャラが描かれている範囲より大きいので、左上座標をそのままセットすると、
//                //透過されている部分を含めた左上座標の位置に描画される。
//                //それを避けるため、センターポジションまでのオフセット分だけ引いて、キャラが描かれている左上座標を、
//                //指定したマップの座標位置まで持っていく必要がある。
//                int x_left = (screen_info->GetLeftX() + x * MAP_CHIP_SIZE) - collison.center_position.x;
//                int y_top = (screen_info->GetLeftY() + y * MAP_CHIP_SIZE) - collison.center_position.y;
//                stage_obj.SetPosition(Vector2D(x_left, y_top));
//
//                float center_pos_x = stage_obj.GetPosition().x + collison.center_position.x;
//                float center_pos_y = stage_obj.GetPosition().y + collison.center_position.y;
//                stage_obj.SetCenterPosition(Vector2D(center_pos_x, center_pos_y));
//
//                return;
//            }
//        }
//    }
//}

void Field::SetInitialPosition(StageObject& stage_obj)
{
    ScreenInfo* screen_info = ScreenInfo::GetInstance();
    const BoxCollisionParams collison = stage_obj.GetBodyCollision();
    //キャラクターの画像サイズが、キャラが描かれている範囲より大きいので、左上座標をそのままセットすると、
    //透過されている部分を含めた左上座標の位置に描画される。
    //それを避けるため、センターポジションまでのオフセット分だけ引いて、キャラが描かれている左上座標を、
    //指定したマップの座標位置まで持っていく必要がある。
    if (stage_obj.GetBodyCollision().object_type != kITEM_TYPE) {
        stage_obj.SetPosition(Vector2D(stage_obj.GetPosition() - collison.center_position));
    }
    stage_obj.SetCenterPosition(Vector2D(stage_obj.GetPosition() + collison.center_position));
}

std::vector<Vector2D> Field::GetCheckPointList() {

    ScreenInfo* screen_info = ScreenInfo::GetInstance();
    std::vector<Vector2D> check_point_list;

    for (unsigned y = 0; y < map_data.size(); y++) {
        for (unsigned x = 0; x < map_data.at(y).size(); x++) {

            if (map_data.at(y).at(x) == kPLAYER_START) {

                int x_left = (screen_info->GetLeftX() + x * MAP_CHIP_SIZE);
                int y_top = (screen_info->GetLeftY() + y * MAP_CHIP_SIZE);
                check_point_list.push_back(Vector2D(x_left, y_top));
            }
        }
    }
    return check_point_list;
}

std::vector<CreateObjectInfo> Field::GetCreateObjectInfo() {
    std::vector<CreateObjectInfo> return_info;
    ScreenInfo* screen_info = ScreenInfo::GetInstance();

    for (unsigned y = 0; y < map_data.size(); y++) {
        for (unsigned x = 0; x < map_data.at(y).size(); x++) {
            CreateObjectInfo create_object_info;

            int x_left = screen_info->GetLeftX() + x * MAP_CHIP_SIZE;
            int y_top = screen_info->GetLeftY() + y * MAP_CHIP_SIZE;
            create_object_info.initiali_position = Vector2D(x_left, y_top);

            switch(map_data.at(y).at(x)) {
            
            case kPLAYER_START:
                create_object_info.object_type = kPLAYER_START;
                break;
            case kBASE_ENEMY:
                create_object_info.object_type = kBASE_ENEMY;
                break;
            case kATTACK_ENEMY:
                create_object_info.object_type = kATTACK_ENEMY;
                break;
            case kCOIN:
                create_object_info.object_type = kCOIN;
                break;
            case kINVINCIBLE_CAN:
                create_object_info.object_type = kINVINCIBLE_CAN;
                break;
            case kKILL_POINT:
                create_object_info.object_type = kKILL_POINT;
                break;
            case kGOAL:
                create_object_info.object_type = kGOAL;
                break;
            default:
                create_object_info.object_type = kNONE;
                break;
            }

            if (create_object_info.object_type != kNONE) {
                return_info.push_back(create_object_info);
            }

        }
    }
    return return_info;
}
