#pragma once
#include "../Source/GameObject/StageObject/StageObject.h"
#include "CharacterDirection.h"
#include <vector>

class CharacterEventInterface;
class HpUI;

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
    float move_speed;

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
    CharacterEventInterface* character_event;

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

    bool is_get_damaged;
    HpUI* hp_ui;
protected:
    /// <summary>
    /// �ړ�����
    /// </summary>
    /// <param name="delta_time">���t���[������</param>
    virtual void Move(float delta_time);

    /// <summary>
    /// �m�b�N�o�b�N����
    /// </summary>
    /// <param name="delta_time">���t���[������</param>
    /// <param name="knock_back_dir">�m�b�N�o�b�N�������</param>
    virtual void KnockBack(const float delta_time, const Vector2D& knock_back_dir);

    /// <summary>
    /// �L�����̌����𔽑΂ɕύX�B
    /// </summary>
    void ReverseDirection();

    virtual void CallDeadEvent();

protected:
    /// <summary>
    /// �m�b�N�o�b�N�̃x�N�g��
    /// </summary>
    Vector2D knock_back_dir;

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
    virtual void OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) override;

    /// <summary>
    /// �L�����N�^�[�C�x���g�C���^�[�t�F�[�X��ݒ�
    /// </summary>
    void SetICharacterEvent(CharacterEventInterface* character_interface) { character_event = character_interface; };
    void SetHpUi(HpUI& hp_ui);

public:
    const int MAX_HP;
    void SetHp(const int new_hp) { hp = new_hp; }
    /// <summary>
    /// HP���擾
    /// </summary>
    /// <returns>HP</returns>
    int GetHp() const { return hp; }

    void SetAttack(const int attack) { this->attack = attack; }
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
    float GetSpeed() const { return move_speed; }

    /// <summary>
    /// �ړ��X�s�[�h���Z�b�g
    /// </summary>
    /// <param name="speed">�ړ��X�s�[�h</param>
    void SetSpeed(const float speed) { move_speed = speed; };

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
    void GiveDamage(Character& target, int damage);

    /// <summary>
    /// �_���[�W���󂯂�
    /// </summary>
    /// <param name="opponent">�U�����Ă����L����</param>
    /// <param name="damage">�_���[�W</param>
    void GetDamage(Character& opponent, const int damage);

    void CallGiveDamageEvent(StageObject& give_gamage_chara, const StageObject& opponent_chara, const int damage);

    bool GetIsGetDmaged() { return is_get_damaged; }

    void UpdateHpUI(const int new_hp);
};

