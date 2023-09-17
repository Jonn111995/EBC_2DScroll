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

    // �ǂݍ���csv�t�@�C�����J��(std::ifstream�̃R���X�g���N�^�ŊJ��)
    std::ifstream IfsCsvFile(file_name, std::ios::in);

    if (!IfsCsvFile) {
        std::cout << u8"�t�@�C�����J���܂���ł����B" << std::endl;
        return false;
    }

    // getline�֐���1�s���ǂݍ���
    while (std::getline(IfsCsvFile, Data)) {
        // �u,�v��؂育�ƂɃf�[�^��ǂݍ��ނ��߂�istringstream�^�ɂ���
        std::istringstream IStream(Data);

        // �u,�v��؂育�ƂɃf�[�^��ǂݍ���
        while (std::getline(IStream, ConmmaData, ',')) {

            //�z��ɏ���ǉ�
            MapInfo.push_back(ConmmaData);
        }

        //��s���̔z�������
        std::vector<int> OneLineMapData;
        //��s���̔z��̃T�C�Y���z�����
        for (int i = 0; i < MapInfo.size(); i++) {

            //string�Ȃ̂�int�ɕϊ����Ĕz��ɒǉ�
            OneLineMapData.push_back(atoi(MapInfo[i].c_str()));
        }

        //�ǉ����I�������A�񎟌��z��̕��ֈ�s���̔z�������
        map_data.push_back(OneLineMapData);

        //�������Z�b�g���Ȃ��Ǝ��̃��[�v�őO�̏�񂪎c���Ă��܂�
        MapInfo.clear();

    }
    IfsCsvFile.close();
	return true;
}
