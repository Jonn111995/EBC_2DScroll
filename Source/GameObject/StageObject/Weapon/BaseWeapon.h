#pragma once
#include "../StageObject.h"

class Character;

namespace {

	enum class EWeaponType {
		kPLAYER,
		KENEMY
	};
}
enum class EWeaponDirection {
	kLEFT,
	kRIGHT,
};

class BaseWeapon : public StageObject {

public:
	

public:

	BaseWeapon();
	virtual ~BaseWeapon();

	/// <inheritdoc/>
	virtual void Initialize() override;
	/// <inheritdoc/>
	virtual void Finalize() override;
	/// <inheritdoc/>
	virtual void Update(float delta_seconds) override {};
	///  <inheritdoc/>
	virtual void Draw(const Vector2D& screen_offset) override {};
	///  <inheritdoc/>
	virtual void OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) override;
public:
	virtual void SetAttackRange(const BoxCollisionParams& owner_collision);

	void SetOwner(Character* owner) { this->owner = owner; }
	void SetWeaponDirection();
	//void SetWeaponType(EWeaponType type);
	int GetWeaponAttack() { return attack; }

protected:
	int attack;
	int attack_sound;
	Character* owner;
	EWeaponDirection now_direction;
	EWeaponType weapon_type;
};