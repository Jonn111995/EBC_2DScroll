#pragma once
#include "Vector2D.h"
#include "ColliiosnObjectType.h"
#include "CollisionType.h"

enum class EHitSurface {
	kTOP = 0,
	kBOTTOM,
	kRIGHT,
	kLEFT
};

namespace {
	EHitSurface surface_type[4] = { EHitSurface::kTOP, EHitSurface::kBOTTOM, EHitSurface::kRIGHT, EHitSurface::kLEFT };
}

/// <summary>
/// コリジョン
/// </summary>
struct BoxCollisionParams {

public:
	/// <summary>
	/// 中心座標までの
	/// </summary>
	Vector2D center_position2;
	/// <summary>
	/// コリジョンの中心座標
	/// </summary>
	Vector2D center_position;

	/// <summary>
	/// コリジョンの左上座標
	/// </summary>
	Vector2D left_up_position;

	/// <summary>
	/// オブジェクトタイプ
	/// </summary>
	CollisionObjectType object_type;

	/// <summary>
	/// ヒットしたオブジェクトのタイプ
	/// </summary>
	unsigned int hit_object_types;

	/// <summary>
	/// コリジョンのセンターからの範囲？
	/// </summary>
	Vector2D box_extent;

	/// <summary>
	/// コリジョンのタイプ
	/// </summary>
	CollisionType collision_type;

	bool is_hit_surfaces[4] = { false };

	/// <summary>
	/// ヒットしたオブジェクトとのコリジョンチェック
	/// </summary>
	/// <param name="target">ヒットしたオブジェクトのオブジェクトタイプ</param>
	/// <returns></returns>
	bool IsHitCheckTarget(CollisionObjectType target);

	void SetHittdSruface(EHitSurface hitted_surface);
	
	bool* GetHittedSurface() { return is_hit_surfaces; }

	void SetCenterPosition(Vector2D position);

	Vector2D GetLeftTopPosition();
	Vector2D GetRightTopPosition();
	Vector2D GetLeftDownPosition();
	Vector2D GetRightDownPosition();
};

