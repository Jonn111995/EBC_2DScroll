#include "SceneBase.h"
#include "Camera.h"
#include <algorithm>

SceneBase::SceneBase()
	: screen_offset()
	, now_scene_type(SceneType::NONE)
	, camera(nullptr)
{
}

SceneBase::~SceneBase() {
}

void SceneBase::Initialize() {
	camera = new Camera();
}

SceneType SceneBase::Update(const float delta_time) {

	for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator) {
		(*iterator)->Update(delta_time);
	}

	return GetSceneType();
}

void SceneBase::Draw() {

	screen_offset =  camera->GetScreenOffset();

	//描画順にソート
	std::sort(objects.begin(), objects.end(),
		[](const GameObject* a, const GameObject* b) {return a->GetDrawSortPriority() < b->GetDrawSortPriority(); });

	//描画
	for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator) {

		//Updateで、kNONE_ACTIVEに設定されていれば、描画しない
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

	// 削除対象の検索
	auto iterator = objects.begin();
	for (; iterator != objects.end(); ++iterator) {
		if ((*iterator) == object){
			break;
		}
	}

	// 見つからなかった場合は抜ける
	if (iterator == objects.end()) {
		return;
	}

	// 削除
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
	
		//衝突チェックをする両オブジェクトの中心座標から距離を算出
		//distance_ｘがマイナスであれば、基準のオブジェクトが他方よりも右にある。
		//distance_yがマイナスであれば。基準のオブジェクトが他方よりも上にある
		float distance_x = abs(collision_params.center_position2.x - hit_collision_params.center_position2.x);
		float distance_y = abs(collision_params.center_position2.y - hit_collision_params.center_position2.y);

		//両オブジェクトの中心点から辺の端までの距離を足したサイズ
		//このサイズより、距離が小さければ衝突
		float size_x = collision_params.box_extent.x + hit_collision_params.box_extent.x;
		float size_y = collision_params.box_extent.y + hit_collision_params.box_extent.y;

	
		//差が微小の場合は当たったと見なすための処理
		if (abs(distance_x - size_x) <= 0.1f) {
			distance_x = size_x;
		}
		if (abs(distance_y - size_y) <= 0.1f) {
			distance_y = size_y;
		}

		//以下衝突判定
		if (distance_x <= size_x && distance_y <= size_y) {

			float check = collision_params.center_position2.x - hit_collision_params.center_position2.x;

			//左右どちらの辺に衝突したかを保持
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
