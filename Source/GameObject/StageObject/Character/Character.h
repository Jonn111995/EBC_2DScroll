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
    /// <summary>
    /// �d�͉�����
    /// </summary>
    const float GRAVITY_ACCELARATION = 1.0f;
    /// <summary>
    /// �W�����v�̍ۂ̏���ւ̏����x
    /// </summary>
    const int INITIAL_JUMP_VELOCITY = -25;
    /// <summary>
    /// ���S���̃��[�V�����̕b��
    /// </summary>
    const float DEAD_MOVE_TIME = 1.5f;
}

class Character :public StageObject {

public:
    Character();
    virtual ~Character();

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

public:

    /// <summary>
    /// HP���Z�b�g����
    /// </summary>
    /// <param name="new_hp"></param>
    void SetHp(const int new_hp) { hp = new_hp; }
    /// <summary>
    /// HP���擾
    /// </summary>
    /// <returns>HP</returns>
    int GetHp() const { return hp; }
    int GetMaxHp() const { return MAX_HP; }

    /// <summary>
    /// �U���͂��Z�b�g����
    /// </summary>
    /// <param name="attack"></param>
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
    void SetIsMove(const bool is_move) { this->is_move = is_move; }

    /// <summary>
    /// �ړ����Ă��邩�ǂ������擾
    /// </summary>
    bool GetIsMove() const { return is_move; }

    /// <summary>
    /// �L�����̈ړ�������ݒ�
    /// </summary>
    /// <param name="new_direction">�ړ�����</param>
    void SetDirection(CharacterDirection new_direction) { direction = new_direction; }

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

    /// <summary>
    /// �_���[�W��^����C�x���g���Ă�
    /// </summary>
    /// <param name="give_gamage_chara"></param>
    /// <param name="opponent_chara"></param>
    /// <param name="damage"></param>
    void CallGiveDamageEvent(StageObject& give_gamage_chara, const StageObject& opponent_chara, const int damage);

    /// <summary>
    /// HPUI���X�V����
    /// </summary>
    /// <param name="new_hp">�V����HP</param>
    void UpdateHpUI(const int new_hp);

    /// <summary>
   /// �L�����N�^�[�C�x���g�C���^�[�t�F�[�X��ݒ�
   /// </summary>
    void SetICharacterEvent(CharacterEventInterface* character_interface) { character_event = character_interface; };

    /// <summary>
    /// HPUI���Z�b�g����
    /// </summary>
    /// <param name="hp_ui"></param>
    void SetHpUi(HpUI& hp_ui);

    bool GetIsNoDamage() const { return is_no_damage; }

protected:
   
    /// <summary>
    /// �L�����N�^�[�C�x���g�C���^�[�t�F�[�X
    /// </summary>
    CharacterEventInterface* character_event;

    /// <summary>
    /// HPUI
    /// </summary>
    HpUI* hp_ui;

    /// <summary>
    /// �_���[�W���󂯂Ȃ����H
    /// </summary>
    bool is_no_damage;
    /// <summary>
    /// �ړ��x�N�g��
    /// </summary>
    Vector2D input_direction;

    /// <summary>
    /// �����x
    /// </summary>
    float initial_velocity;

    /// <summary>
    /// ���t���[�����Ԃ̌v������
    /// </summary>
    float count_time;

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

    /// <summary>
    /// �m�b�N�o�b�N�̃x�N�g��
    /// </summary>
    Vector2D knock_back_dir;

    int get_damage_sound;

protected:
    /// <summary>
    /// �ړ�����
    /// </summary>
    /// <param name="delta_time">���t���[������</param>
    virtual void Move(float delta_time);

    virtual float UpdateXPosition(const bool is_can_move_to_x, const float update_x_amount);
    virtual float UpdateYPosition(const bool is_can_move_to_y, const float update_y_amount);

    /// <summary>
    /// �L�����̌����𔽑΂ɕύX�B
    /// </summary>
    void ReverseDirection();

    /// <summary>
    /// ���S��ԂɕύX����B�I�[�o�[���C�h�O��
    /// </summary>
    virtual void SetDeadState();

    /// <summary>
    /// ���S���̈ړ����[�V����
    /// </summary>
    /// <param name="delta_time">���t���[������</param>
    /// <returns>true: ���[�V�������� false: ������</returns>
    virtual bool DeadMove(const float delta_time);

    /// <summary>
    /// ���g���폜
    /// </summary>
    virtual void CallDestroy();

private:
    /// <summary>
    /// HP
    /// </summary>
    int hp;

    /// <summary>
    /// �ő�HP
    /// </summary>
    const int MAX_HP;

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
    bool is_move;

    /// <summary>
    /// �ړ�����
    /// </summary>
    CharacterDirection direction;
};

