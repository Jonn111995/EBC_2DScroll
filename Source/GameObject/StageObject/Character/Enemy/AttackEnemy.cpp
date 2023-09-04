#include "AttackEnemy.h"

AttackEnemy::AttackEnemy()
{
}

AttackEnemy::~AttackEnemy()
{
}

void AttackEnemy::Initialize() {
	__super::Initialize();
}

void AttackEnemy::Finalize() {
	__super::Finalize();
}

void AttackEnemy::Update(float delta_time) {

	switch (enemy_state) {
	case EEnemyState::kATTACK:

		break;
	default:
		break;
	}
	__super::Update(delta_time);
}

void AttackEnemy::Draw(const Vector2D& screen_offset) {
	__super::Draw(screen_offset);
}

void AttackEnemy::OnHitBoxCollision(const StageObject* hit_object, const BoxCollisionParams& hit_collision) {
	__super::OnHitBoxCollision(hit_object, hit_collision);
}
