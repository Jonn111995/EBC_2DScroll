#include "Field.h"
#include "DxLib.h"
#include "../Source/System/ScreenInfo.h"
#include <iostream>
#include "../CSVData/CSVFile.h"
#include "EMapChipType.h"

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

    wall_graphic_handle = LoadGraph("Resources/Images/mapchip_000.bmp");
    box_graphic_handle = LoadGraph("Resources/Images/mapchip_017.bmp");
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
           
            int x1 = static_cast<int>(screen_info->GetLeftX()) + x_graphic_size * x;
            int y2 = static_cast<int>(screen_info->GetLeftY()) + y_graphic_size * y;
            //描画する。xとyの位置に、その位置に設定されているハンドル値による画像を描画する。
            DrawGraph(x1, y2, graph, true);
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

                        int x1 = static_cast<int>(screen_info->GetLeftX()) + 32 * x;
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
