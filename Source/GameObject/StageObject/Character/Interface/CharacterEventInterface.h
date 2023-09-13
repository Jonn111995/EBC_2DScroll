#pragma once

class BaseWeapon;
class StageObject;
class Character;

/// <summary>
/// キャラクター共通イベント
/// </summary>
class CharacterEventInterface {

public:
	
	virtual bool CheckCanMoveToX(const Vector2D& move_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) = 0;
	virtual bool CheckCanMoveToY(const Vector2D& move_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) = 0;
	virtual void AddWeapon(BaseWeapon& weapon) = 0;
	virtual void RemoveWeapon(BaseWeapon* weapon) = 0;
	virtual void GiveDamageEvent(StageObject& give_gamage_chara, const StageObject& opponent_chara, const int damage) = 0;
	virtual void UpdateHpUI(const int now_hp) = 0;
	virtual void DeadEvent(Character* dead_object) = 0;

	virtual bool CheckCanMove(const Vector2D& move_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) = 0;
	virtual bool CheckCanStand(Vector2D& move_to_position, const BoxCollisionParams& collision) = 0;
};