#include "CSVFile.h"
#include <Stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

CSVFile::CSVFile()
{
}

CSVFile::~CSVFile()
{
}

bool CSVFile::Read(const char* file_name){

    std::string Data;
    std::string ConmmaData;
    std::vector<std::string> MapInfo;

    // 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
    std::ifstream IfsCsvFile(file_name, std::ios::in);

    if (!IfsCsvFile) {
        std::cout << u8"ファイルが開けませんでした。" << std::endl;
        return false;
    }

    // getline関数で1行ずつ読み込む
    while (std::getline(IfsCsvFile, Data)) {
        // 「,」区切りごとにデータを読み込むためにistringstream型にする
        std::istringstream IStream(Data);

        // 「,」区切りごとにデータを読み込む
        while (std::getline(IStream, ConmmaData, ',')) {

            //配列に情報を追加
            MapInfo.push_back(ConmmaData);
        }

        //一行分の配列を入れる
        std::vector<int> OneLineMapData;
        //一行分の配列のサイズ分配列を回す
        for (int i = 0; i < MapInfo.size(); i++) {

            //stringなのでintに変換して配列に追加
            OneLineMapData.push_back(atoi(MapInfo[i].c_str()));
        }

        //追加し終わったら、二次元配列の方へ一行分の配列を入れる
        map_data.push_back(OneLineMapData);

        //情報をリセットしないと次のループで前の情報が残ってしまう
        MapInfo.clear();

    }
    IfsCsvFile.close();
	return true;
}
