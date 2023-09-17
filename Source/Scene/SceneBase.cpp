#include "SceneBase.h"
#include "Camera.h"
#include <algorithm>

SceneBase::SceneBase()
	: screen_offset(Vector2D())
	, camera(nullptr)
{
}

SceneBase::~SceneBase() {
}

void SceneBase::Initialize() {
	camera = new Camera();
}

SceneType SceneBase::Update(float delta_seconds) {

	for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator) {
		(*iterator)->Update(delta_seconds);
	}
	return GetSceneType();
}

void SceneBase::Draw() {

	screen_offset =  camera->GetScreenOffset();

	//�`�揇�Ƀ\�[�g
	std::sort(objects.begin(), objects.end(),
		[](const GameObject* a, const GameObject* b) {return a->GetDrawSortPriority() < b->GetDrawSortPriority(); });

	for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator) {
		if ((*iterator)->GetActivation() == EActivation::kNONE_ACTIVE) {
			continue;
		}
		(*iterator)->Draw(screen_offset);
	}
}

void SceneBase::Finalize() {
	delete camera;
	camera = nullptr;
	DestroyAllObjects();
}

void SceneBase::DestroyObject(const GameObject* object) {
	if (object == nullptr) {
		return;
	}

	// �폜�Ώۂ̌���
	auto iterator = objects.begin();
	for (; iterator != objects.end(); ++iterator) {
		if ((*iterator) == object){
			break;
		}
	}

	// ������Ȃ������ꍇ�͔�����
	if (iterator == objects.end()) {
		return;
	}

	// �폜
	(*iterator)->Finalize();
	objects.erase(std::remove(objects.begin(), objects.end(), *iterator),objects.end());
	delete object;
}

void SceneBase::DestroyAllObjects() {
	for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator) {
		(*iterator)->Finalize();
		delete (*iterator);
	}
	objects.clear();
}

bool SceneBase::CheckBoxCollision(StageObject* target, const BoxCollisionParams& collision_params, BoxCollisionParams& hit_collision_params) {
	
	if(target->GetBodyCollision().IsHitCheckTarget(hit_collision_params.object_type)) {
	
		float distance_x = abs(collision_params.center_position2.x - hit_collision_params.center_position2.x);
		float distance_y = abs(collision_params.center_position2.y - hit_collision_params.center_position2.y);
		float size_x = collision_params.box_extent.x + hit_collision_params.box_extent.x;
		float size_y = collision_params.box_extent.y + hit_collision_params.box_extent.y;

		//distance_�����}�C�i�X�ł���΁A��̃I�u�W�F�N�g�����������E�ɂ���B
		//distance_y���}�C�i�X�ł���΁B��̃I�u�W�F�N�g������������ɂ���
	
		//���������̏ꍇ�͓��������ƌ��Ȃ����߂̏���
		if (abs(distance_x - size_x) <= 0.1f) {
			distance_x = size_x;
		}
		if (abs(distance_y - size_y) <= 0.1f) {
			distance_y = size_y;
		}

		if (distance_x <= size_x && distance_y <= size_y) {

			float check = collision_params.center_position2.x - hit_collision_params.center_position2.x;
			if (check <= 0) {
				hit_collision_params.SetHittdSruface(EHitSurface::kLEFT);
			}
			else {
				hit_collision_params.SetHittdSruface(EHitSurface::kRIGHT);
			}
			return true;
		}
	}
	return false;
}

void SceneBase::DestroyBookDeleteObject() {

	for (auto& object : delete_objects_list) {
		DestroyObject(object);
	}

	delete_objects_list.clear();
}
