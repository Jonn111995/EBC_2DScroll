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
	virtual SceneType Update(const float delta_time);

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
	/// 削除予定のオブジェクトを破棄
	/// </summary>
	virtual void DestroyBookDeleteObject();

	/// <summary>
	/// GameObjectの生成
	/// Templateで指定したGameObjectクラスを派生したクラスのインスタンス生成する
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="position">初期位置</param>
	/// <returns>生成したGameObject</returns>
	template <class T>
	T* CreateObject(const Vector2D& position = Vector2D(0.0f,0.0f))
	{
		T* new_instance = new T();
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		// GameObjectを派生していない場合は、破棄して終了する
		if (new_object == nullptr)
		{
			//派生していないクラスのため、生成しない
			delete new_instance;
			return nullptr;
		}

		/* GameObjectは座標情報を持たないので、
		座標情報を持つStageObjectを継承している時のみ座標をセットする*/
		StageObject* stage_object = nullptr;
		if (stage_object = dynamic_cast<StageObject*>(new_object)) {
			stage_object->SetPosition(position);
	    }

		new_object->Initialize();
		//objectsに入れることで、各オブジェクトのUpdateとDraw関数を呼べるようにしている。
		objects.push_back(new_object);

		return new_instance;
	}

	/// <summary>
	/// GameObjectの破棄
	/// GameObjectを破棄し、配列から削除する
	/// </summary>
	/// <param name="object">破棄するオブジェクト</param>
	void DestroyObject(const class GameObject* object);

	/// <summary>
	/// 全てのGameObjectの破棄
	// シーンに生成されている全てのオブジェクトを破棄する
	/// </summary>
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
	/// Cameraオブジェクトの座標から現在描画する左上座標を算出し、その値を入れる。
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