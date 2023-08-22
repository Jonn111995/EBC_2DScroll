#pragma once
#include "../Source/GameObject/StageObject/StageObject.h"
#include "CharacterDirection.h"

class Character :public StageObject {

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

    CharacterDirection direction;

public:
    /// <inheritdoc/>
    virtual void Initialize() override {}
    /// <inheritdoc/>
    virtual void Finalize() override {}
    virtual void Update(float delta_time) override {};
    virtual void Draw(const Vector2D& screen_offset) override {};
    virtual void OnHitBoxCollision(const GameObject& hit_object, const BoxCollisionParams& hit_collision) override {};

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

    void SetDirection(CharacterDirection new_direction) { direction = new_direction; }
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

