#pragma once

#include "CSVFile.h"
#include <vector>

/// <summary>
/// CSVファイルの読み込み機能
/// </summary>
class CSVFile {

public:
	CSVFile();
	virtual ~CSVFile();

	/// <summary>
	/// CSVファイルを読み込む
	/// </summary>
	/// <param name="file_name">読み込むファイル名</param>
	/// <returns>true: 読み込み成功 false:読み込み失敗</returns>
	bool Read(const char* file_name);

	/// <summary>
	/// 読み込んだファイルデータを取得
	/// </summary>
	/// <returns>ファイルデータ</returns>
	const std::vector<std::vector<int>>& GetData() const { return map_data; }

private:

	/// <summary>
	/// 読み込んだステージデータ
	/// </summary>
	std::vector<std::vector<int>> map_data;
};