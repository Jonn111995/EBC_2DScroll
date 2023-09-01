#pragma once
#include "../Source/GameObject/StageObject/StageObject.h"
#include "CharacterDirection.h"
#include <vector>

class CharacterEventInterface;

namespace {
    /// <summary>
    /// �ړ��X�s�[�h
    /// </summary>
    const float MOVEMENT_SPEED = 300.f;
}

class Character :public StageObject {

public:
    Character();
    virtual ~Character();
private:
    /// <summary>
    /// HP
    /// </summary>
    int hp;

    /// <summary>
    /// �U����
    /// </summary>
    int attack;

    /// <summary>
    /// �h���
    /// </summary>
    int deffence;

    /// <summary>
    /// �ړ��X�s�[�h
    /// </summary>
    float speed;

    /// <summary>
    /// �����Ă��邩�ǂ���
    /// </summary>
    bool bIsMove;

    /// <summary>
    /// �ړ�����
    /// </summary>
    CharacterDirection direction;

protected:
    /// <summary>
    /// �L�����N�^�[�C�x���g�C���^�[�t�F�[�X
    /// </summary>
    CharacterEventInterface* ICharacterEvent;

    /// <summary>
    /// �ړ��x�N�g��
    /// </summary>
    Vector2D input_direction;

    /// <summary>
    /// ���݂̃A�j���[�V����
    /// </summary>
    std::vector<int> now_animations;

    /// <summary>
    /// �A�j���[�V������ω�������l
    /// </summary>
    float animation_frame;

    /// <summary>
    /// �A�j���[�V�����X�s�[�h
    /// </summary>
    float anim_speed;

    /// <summary>
    /// �A�j���[�V�����t���[���̍ŏ��l
    /// </summary>
    float min_anim_frame;

    /// <summary>
    /// �A�j���[�V�����t���[���̍ő�l
    /// </summary>
    float max_anim_frame;
protected:

public:
    /// <inheritdoc/>
    virtual void Initialize() override;
    /// <inheritdoc/>
    virtual void Finalize() override;
    /// <inheritdoc/>
    virtual void Update(float delta_time) override;
    /// <inheritdoc/>
    virtual void Draw(const Vector2D& screen_offset) override;
    /// <inheritdoc/>
    virtual void OnHitBoxCollision(const GameObject& hit_object, const BoxCollisionParams& hit_collision) override {};

    /// <summary>
    /// �L�����N�^�[�C�x���g�C���^�[�t�F�[�X��ݒ�
    /// </summary>
    void SetICharacterEvent(CharacterEventInterface* interface) { ICharacterEvent = interface; };

public:
    /// <summary>
    /// HP���擾
    /// </summary>
    /// <returns>HP</returns>
    int GetHp() const { return hp; }

    /// <summary>
    /// �U���͂��擾
    /// </summary>
    /// <returns>�U����</returns>
    int GetAttack() const { return attack; }

    /// <summary>
    /// �h��͂��擾
    /// </summary>
    /// <returns>�h���</returns>
    int GetDeffence() const { return deffence; }

    /// <summary>
    /// �ړ��X�s�[�h���擾
    /// </summary>
    /// <returns>�ړ��X�s�[�h</returns>
    float GetSpeed() const { return speed; }

    /// <summary>
    /// �ړ����Ă��邩�ǂ����̃t���O���Z�b�g
    /// </summary>
    /// <param name="bIs_move">
    ///   true:�ړ����Ă���
    ///   false:�ړ����Ă��Ȃ�
    /// </param>
    void SetbIsMove(const bool bIs_move) { bIsMove = bIs_move; }

    /// <summary>
    /// �ړ����Ă��邩�ǂ������擾
    /// </summary>
    bool GetbIsMove() const { return bIsMove; }

    /// <summary>
    /// �L�����̈ړ�������ݒ�
    /// </summary>
    /// <param name="new_direction">�ړ�����</param>
    void SetDirection(CharacterDirection new_direction) { direction = new_direction;}

    /// <summary>
    /// �L�����̈ړ��������擾
    /// </summary>
    /// <returns>�ړ�����</returns>
    CharacterDirection GetDirection() { return direction; }

    /// <summary>
    /// �_���[�W��^����
    /// </summary>
    /// <param name="target">�_���[�W��^����L����</param>
    void GiveDamage(Character& target);

    /// <summary>
    /// �_���[�W���󂯂�
    /// </summary>
    /// <param name="opponent">�U�����Ă����L����</param>
    /// <param name="damage">�_���[�W</param>
    void GetDamage(Character& opponent, const int damage);
};

