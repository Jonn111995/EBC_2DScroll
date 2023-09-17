#pragma once

#include <vector>
#include <string>
#include "InheritInfo.h"
#include "../Utility/Vector2D.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/StageObject/StageObject.h"

class Camera;

/// <summary>
/// �V�[���^�C�v
/// </summary>
enum class SceneType : unsigned short
{
	NONE,
	BOOT_SCENE,
	TITLE_SCENE,
	IN_GAME_SCENE,
	NEXT_STAGE
};

/// <summary>
/// �V�[���̃X�e�[�g
/// </summary>
enum class SceneState : unsigned short {
	kPRESTART,
	kPLAYING,
	kEND
};

/// <summary>
/// �V�[���̊��N���X
/// </summary>
class SceneBase {
public:
	SceneBase();
	virtual ~SceneBase();

public:
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="delta_seconds">���t���[������</param>
	/// <returns>���ɑJ�ڂ���V�[���^�C�v</returns>
	virtual SceneType Update(float delta_seconds);

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// ���
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// �V�[���^�C�v�̎擾
	/// </summary>
	/// <returns>�V�[���^�C�v</returns>
	virtual SceneType GetSceneType() const = 0;

	/// <summary>
	/// �폜�\��̃I�u�W�F�N�g��\��
	/// </summary>
	/// <param name="delete_object">�폜�ΏۃI�u�W�F�N�g</param>
	virtual void BookDeleteObject(GameObject* delete_object) { delete_objects_list.push_back(delete_object); }

	/// <summary>
	/// �폜�\��̃I�u�W�F�N�g���폜
	/// </summary>
	virtual void DestroyBookDeleteObject();

	/**
	 * GameObject�̐���
	 * Template�Ŏw�肵��GameObject�N���X��h�������N���X�̃C���X�^���X��������
	 * @param	Position	�����ʒu
	 * @return	��������GameObject
	 */
	template <class T>
	T* CreateObject(const Vector2D& position = Vector2D(0.0f,0.0f))
	{
		// GameObject�̐���
		T* new_instance = new T();
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		// GameObject��h�����Ă��Ȃ��ꍇ�́A�j�����ďI������
		if (new_object == nullptr)
		{
			//�h�����Ă��Ȃ��N���X�̂��߁A�������Ȃ�
			delete new_instance;
			return nullptr;
		}

		// GameObject�̏�����
		StageObject* stage_object = nullptr;
		if (stage_object = dynamic_cast<StageObject*>(new_object)) {
			stage_object->SetPosition(position);
	    }
		new_object->Initialize();
		objects.push_back(new_object);

		return new_instance;
	}

	/**
	 * GameObject�̔j��
	 * GameObject��j�����A�z�񂩂�폜����
	 * @param	object	�j������I�u�W�F�N�g
	 */
	void DestroyObject(const class GameObject* object);

	/**
	 * �S�Ă�GameObject�̔j��
	 * �V�[���ɐ�������Ă���S�ẴI�u�W�F�N�g��j������
	 */
	void DestroyAllObjects();

	/// <summary>
	/// �X�e�[�W�I�u�W�F�N�g�̏Փ˔�����s���B
	/// </summary>
	/// <param name="target">�Փ˔�����s���I�u�W�F�N�g</param>
	/// <param name="collision_params">�Փ˔�����s���I�u�W�F�N�g�̃R���W����</param>
	/// <param name="hit_collision_params">�Փ˂��ꂽ�I�u�W�F�N�g�̃R���W����</param>
	/// <returns>true: �Փ˂��� false:�Փ˂��ĂȂ�</returns>
	bool CheckBoxCollision(StageObject* target, const BoxCollisionParams& collision_params, BoxCollisionParams& hit_collision_params);

	/// <summary>
	/// ���p�������Z�b�g
	/// </summary>
	/// <param name="inherit_info">�����p�����</param>
	void SetInheritInfo(InheritInfo inherit_info) { this->inherit_info = inherit_info; }

	/// <summary>
	/// ���p�������擾
	/// </summary>
	/// <returns>�����p���ꂽ���</returns>
	InheritInfo GetInheritInfo() const { return inherit_info; }

protected:
	/// <summary>
	/// ���p�����
	/// �X�R�A�A�c�@���A�X�e�[�W���A�X�e�[�WID��ێ�����
	/// </summary>
	InheritInfo inherit_info;

	/// <summary>
	/// �X�N���[���p�I�t�Z�b�g
	/// </summary>
	Vector2D screen_offset;

	/// <summary>
	/// ���݂̃V�[���^�C�v
	/// </summary>
	SceneType now_scene_type;

	/// <summary>
	/// �J����
	/// </summary>
	Camera* camera;

	/// <summary>
	/// �V�[���Ő��������I�u�W�F�N�g�Q
	/// </summary>
	std::vector<class GameObject*> objects;

	/// <summary>
	/// �폜�\��̃I�u�W�F�N�g���X�g
	/// </summary>
	std::vector<class GameObject*> delete_objects_list;
};