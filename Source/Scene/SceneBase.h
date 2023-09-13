#pragma once

#include <vector>
#include <string>
#include "../Utility/Vector2D.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/StageObject/StageObject.h"

/**
 * �V�[���^�C�v
 */
enum class SceneType : unsigned short
{
	SAMPLE_SCENE,
};

enum class SceneState : unsigned short {
	kPRESTART,
	kPLAYING,
	kEND
};

/**
 * �V�[���̊��N���X
 */
class SceneBase {
public:
	SceneBase();
	virtual ~SceneBase();

public:
	/**
	 * ������
	 */
	virtual void Initialize();

	/**
	 * �X�V
	 * @param	delta_seconds	�O�t���[���Ƃ̍�������(s)
	 * @return	���ɑJ�ڂ���V�[���^�C�v
	 */
	virtual SceneType Update(float delta_seconds);

	/** 
	 * �`��
	 */
	virtual void Draw();

	/**
	 * ���
	 */
	virtual void Finalize();

	/**
	 * �V�[���^�C�v�̎擾
	 * @return �V�[���^�C�v
	 */
	virtual SceneType GetSceneType() const = 0;

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
	void DestroyObject(class GameObject* object);

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

	virtual void BookDeleteObject(GameObject* object) { delete_objects_list.push_back(object); }
	virtual void DestroyBookDeleteObject();

protected:
	// �V�[���Ő��������I�u�W�F�N�g
	std::vector<class GameObject*> objects;
	std::vector<class GameObject*> delete_objects_list;
	// �X�N���[���p�X�N���[���I�t�Z�b�g
	Vector2D screen_offset;
};