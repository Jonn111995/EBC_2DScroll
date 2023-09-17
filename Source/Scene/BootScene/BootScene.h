#pragma once
#include <string>
#include "../SceneBase.h"

/// <summary>
/// BootScene�̃X�e�[�g
/// </summary>
enum class EBootSceneState {
	kPLAYING,
	kEND,
};

/// <summary>
/// �N�����
/// ���݂́A�����̉��o�p�r
/// </summary>
class BootScene : public SceneBase {
public:
	BootScene();
	virtual ~BootScene();
public:
	/// <inheritdoc />
	virtual void Initialize();
	/// <inheritdoc />
	virtual SceneType Update(float delta_seconds);
	/// <inheritdoc />
	virtual void Draw();
	/// <inheritdoc />
	virtual void Finalize();
	/// <inheritdoc />
	virtual SceneType GetSceneType()const override { return SceneType::BOOT_SCENE; };
public:
	/// <summary>
	/// Boot�����̃A�j���[�V�������X�V
	/// </summary>
	/// <param name="delta_time"></param>
	void UpdateBootAnimation(const float delta_time);
private:

	/// <summary>
	/// Boot�X�e�[�g
	/// </summary>
	EBootSceneState boot_scene_state;

	/// <summary>
	/// boot�̕������i�[����
	/// </summary>
	std::string boot_array[4];

	/// <summary>
	/// boot_array_�����I�΂ꂽ������������
	/// </summary>
	std::string use_boot;

	/// <summary>
	/// �z��̗v�f�ԍ����w�肷��C���f�N�X�ԍ�
	/// </summary>
	float boot_array_num;

	/// <summary>
	/// �J�E���g����
	/// </summary>
	float boot_count_time;
};