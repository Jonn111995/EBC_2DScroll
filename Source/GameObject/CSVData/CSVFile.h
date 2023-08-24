#pragma once

#include "CSVFile.h"
#include <vector>

/// <summary>
/// CSV�t�@�C���̓ǂݍ��݋@�\
/// </summary>
class CSVFile {

public:
	CSVFile();
	virtual ~CSVFile();

	/// <summary>
	/// CSV�t�@�C����ǂݍ���
	/// </summary>
	/// <param name="file_name">�ǂݍ��ރt�@�C����</param>
	/// <returns>true: �ǂݍ��ݐ��� false:�ǂݍ��ݎ��s</returns>
	bool Read(const char* file_name);

	/// <summary>
	/// �ǂݍ��񂾃t�@�C���f�[�^���擾
	/// </summary>
	/// <returns>�t�@�C���f�[�^</returns>
	const std::vector<std::vector<int>>& GetData() const { return map_data; }

private:

	/// <summary>
	/// �ǂݍ��񂾃X�e�[�W�f�[�^
	/// </summary>
	std::vector<std::vector<int>> map_data;
};