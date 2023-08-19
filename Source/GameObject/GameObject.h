#pragma once

class Vector2D;

/**
 * �Q�[�����ɕ\�������I�u�W�F�N�g�̊��N���X
 */
class GameObject
{
public:
	GameObject();
	virtual ~GameObject() {}

public:
	/**
	 * ������
	 */
	virtual void Initialize() {}

	/**
	 * �X�V
	 * @param	delta_seconds	�O�t���[���Ƃ̍�������(s)
	 */
	virtual void Update(float delta_seconds) {}

	/**
	 * �`��
	 */
	virtual void Draw(const Vector2D& screen_offset) {}

	/**
	 * ���
	 */
	virtual void Finalize() {}

	/**
	 * �V�[���̎擾
	 * @return owner_scene
	 */
	//class SceneBase* GetOwnerScene() const { return owner_scene; }

	/**
	 * �V�[���̃Z�b�g
	 * @param	new_owner_scene	�Z�b�g����Position
	 */
	//void SetOwnerScene(class SceneBase* new_owner_scene);

	/**
	 * �`�揇�̎擾
	 * @return	draw_sort_priority
	 */
	int GetDrawSortPriority() const { return draw_sort_priority; }

	/**
	 * �`�揇�̃Z�b�g
	 * @param	new_priority	�Z�b�g����`�揇
	 */
	void SetDrawSortPriority(const int new_priority);

private:
	// �I�[�i�[�ƂȂ�V�[��
	//class SceneBase* owner_scene;

	// �`�揇�B���l��������������`����s��
	int draw_sort_priority;
};