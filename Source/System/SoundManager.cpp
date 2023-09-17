#include "SoundManager.h"
#include "DxLib.h"

SoundManager* SoundManager::sound_manager = nullptr;

SoundManager::SoundManager()
	: loaded_sounds()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::CreateInstance() {
	if (sound_manager == nullptr) {
		sound_manager = new SoundManager();
	}
}

SoundManager* SoundManager::GetInstance() {
	return sound_manager;
}

void SoundManager::DeleteInstance() {
	delete sound_manager;
	sound_manager = nullptr;
}

void SoundManager::Initialize() {

}

int SoundManager::LoadSoundResource(const char* file_name) {
	int sound_handle = LoadSoundMem(file_name);
	loaded_sounds.emplace(file_name, sound_handle);

	return sound_handle;
}

void SoundManager::UnLoadSoundResource(int sound_handle) {
	for (auto it = loaded_sounds.begin(); it != loaded_sounds.end();) {
		
		if (it->second == sound_handle) {
			
			it = loaded_sounds.erase(it);
			DeleteSoundMem(sound_handle);
		}
		else {
			++it;
		}
	}
}

void SoundManager::UnLoadAllSoundResource() {
	loaded_sounds.clear();
	InitSoundMem();
}

void SoundManager::PlayLoadSound(int sound_handle, bool is_loop) {

	if (is_loop) {
		PlaySoundMem(sound_handle, DX_PLAYTYPE_LOOP);
	}
	else {
		PlaySoundMem(sound_handle, DX_PLAYTYPE_BACK);
	}
}

void SoundManager::StopSound(int sound_handle) {
	StopSoundMem(sound_handle);
}
