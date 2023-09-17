#pragma once
#include <map>

class SoundManager {

private:
	SoundManager();

public:
	~SoundManager();

	/// <summary>
	/// インスタンスを作成する
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// インスタンスを取得する
	/// </summary>
	/// <returns></returns>
	static SoundManager* GetInstance();

	/// <summary>
	/// インスタンスを削除する
	/// </summary>
	static void DeleteInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	int LoadSoundResource(const char* file_name);
	void UnLoadSoundResource(int sound_handle);
	void UnLoadAllSoundResource();
	void PlayLoadSound(int sound_handle, bool is_loop = false);
	void StopSound(int sound_handle);

public:
	/// <summary>
	/// シングルトンインスタンス
	/// </summary>
	static SoundManager* sound_manager;
private:
	std::map<const char*, int> loaded_sounds;
};