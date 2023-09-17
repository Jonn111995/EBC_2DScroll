#pragma once

#include <vector>
#include <string>
#include "InheritInfo.h"
#include "../Utility/Vector2D.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/StageObject/StageObject.h"

class Camera;

/// <summary>
/// シーンタイプ
/// </summary>
enum class SceneType : unsigned short
{
	NONE,
	BOOT_SCENE,
	TITLE_SCENE,
	IN_GAME_SCENE,
	NEXT_STAGE
};

/// <summary>
/// シーンのステート
/// </summary>
enum class SceneState : unsigned short {
	kPRESTART,
	kPLAYING,
	kEND
};

/// <summary>
/// シーンの基底クラス
/// </summary>
class SceneBase {
public:
	SceneBase();
	virtual ~SceneBase();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="delta_seconds">毎フレーム時間</param>
	/// <returns>次に遷移するシーンタイプ</returns>
	virtual SceneType Update(float delta_seconds);

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// 解放
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// シーンタイプの取得
	/// </summary>
	/// <returns>シーンタイプ</returns>
	virtual SceneType GetSceneType() const = 0;

	/// <summary>
	/// 削除予定のオブジェクトを予約
	/// </summary>
	/// <param name="delete_object">削除対象オブジェクト</param>
	virtual void BookDeleteObject(GameObject* delete_object) { delete_objects_list.push_back(delete_object); }

	/// <summary>
	/// 削除予定のオブジェクトを削除
	/// </summary>
	virtual void DestroyBookDeleteObject();

	/**
	 * GameObjectの生成
	 * Templateで指定したGameObjectクラスを派生したクラスのインスタンス生成する
	 * @param	Position	初期位置
	 * @return	生成したGameObject
	 */
	template <class T>
	T* CreateObject(const Vector2D& position = Vector2D(0.0f,0.0f))
	{
		// GameObjectの生成
		T* new_instance = new T();
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		// GameObjectを派生していない場合は、破棄して終了する
		if (new_object == nullptr)
		{
			//派生していないクラスのため、生成しない
			delete new_instance;
			return nullptr;
		}

		// GameObjectの初期化
		StageObject* stage_object = nullptr;
		if (stage_object = dynamic_cast<StageObject*>(new_object)) {
			stage_object->SetPosition(position);
	    }
		new_object->Initialize();
		objects.push_back(new_object);

		return new_instance;
	}

	/**
	 * GameObjectの破棄
	 * GameObjectを破棄し、配列から削除する
	 * @param	object	破棄するオブジェクト
	 */
	void DestroyObject(const class GameObject* object);

	/**
	 * 全てのGameObjectの破棄
	 * シーンに生成されている全てのオブジェクトを破棄する
	 */
	void DestroyAllObjects();

	/// <summary>
	/// ステージオブジェクトの衝突判定を行う。
	/// </summary>
	/// <param name="target">衝突判定を行うオブジェクト</param>
	/// <param name="collision_params">衝突判定を行うオブジェクトのコリジョン</param>
	/// <param name="hit_collision_params">衝突されたオブジェクトのコリジョン</param>
	/// <returns>true: 衝突した false:衝突してない</returns>
	bool CheckBoxCollision(StageObject* target, const BoxCollisionParams& collision_params, BoxCollisionParams& hit_collision_params);

	/// <summary>
	/// 引継ぎ情報をセット
	/// </summary>
	/// <param name="inherit_info">引き継ぐ情報</param>
	void SetInheritInfo(InheritInfo inherit_info) { this->inherit_info = inherit_info; }

	/// <summary>
	/// 引継ぎ情報を取得
	/// </summary>
	/// <returns>引き継がれた情報</returns>
	InheritInfo GetInheritInfo() const { return inherit_info; }

protected:
	/// <summary>
	/// 引継ぎ情報
	/// スコア、残機数、ステージ名、ステージIDを保持する
	/// </summary>
	InheritInfo inherit_info;

	/// <summary>
	/// スクロール用オフセット
	/// </summary>
	Vector2D screen_offset;

	/// <summary>
	/// 現在のシーンタイプ
	/// </summary>
	SceneType now_scene_type;

	/// <summary>
	/// カメラ
	/// </summary>
	Camera* camera;

	/// <summary>
	/// シーンで生成したオブジェクト群
	/// </summary>
	std::vector<class GameObject*> objects;

	/// <summary>
	/// 削除予定のオブジェクトリスト
	/// </summary>
	std::vector<class GameObject*> delete_objects_list;
};