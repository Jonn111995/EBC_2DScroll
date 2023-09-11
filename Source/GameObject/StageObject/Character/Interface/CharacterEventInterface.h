#pragma once

class BaseWeapon;
class StageObject;
/// <summary>
/// �L�����N�^�[���ʃC�x���g
/// </summary>
class CharacterEventInterface {

public:
	virtual bool CheckCanMove(const Vector2D& move_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) = 0;
	virtual bool CheckCanMoveToX(const Vector2D& move_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) = 0;
	virtual bool CheckCanMoveToY(const Vector2D& move_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) = 0;
	virtual void AddWeapon(BaseWeapon& weapon) = 0;
	virtual void RemoveWeapon(BaseWeapon* weapon) = 0;
	virtual void GiveDamageEvent(StageObject& give_gamage_chara, const StageObject& opponent_chara, const int damage) = 0;


	virtual bool CheckCanStand(Vector2D& move_to_position, const BoxCollisionParams& collision) = 0;
};