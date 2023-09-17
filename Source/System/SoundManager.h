#pragma once
#include <map>

class SoundManager {

private:
	SoundManager();

public:
	~SoundManager();

	/// <summary>
	/// �C���X�^���X���쐬����
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// �C���X�^���X���擾����
	/// </summary>
	/// <returns></returns>
	static SoundManager* GetInstance();

	/// <summary>
	/// �C���X�^���X���폜����
	/// </summary>
	static void DeleteInstance();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	int LoadSoundResource(const char* file_name);
	void UnLoadSoundResource(int sound_handle);
	void UnLoadAllSoundResource();
	void PlayLoadSound(int sound_handle, bool is_loop = false);
	void StopSound(int sound_handle);

public:
	/// <summary>
	/// �V���O���g���C���X�^���X
	/// </summary>
	static SoundManager* sound_manager;
private:
	std::map<const char*, int> loaded_sounds;
};