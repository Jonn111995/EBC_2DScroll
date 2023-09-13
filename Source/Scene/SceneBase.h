#pragma once

#include <vector>
#include <string>
#include "../Utility/Vector2D.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/StageObject/StageObject.h"

/**
 * シーンタイプ
 */
enum class SceneType : unsigned short
{
	SAMPLE_SCENE,
};

enum class SceneState : unsigned short {
	kPRESTART,
	kPLAYING,
	kEND
};

/**
 * シーンの基底クラス
 */
class SceneBase {
public:
	SceneBase();
	virtual ~SceneBase();

public:
	/**
	 * 初期化
	 */
	virtual void Initialize();

	/**
	 * 更新
	 * @param	delta_seconds	前フレームとの差分時間(s)
	 * @return	次に遷移するシーンタイプ
	 */
	virtual SceneType Update(float delta_seconds);

	/** 
	 * 描画
	 */
	virtual void Draw();

	/**
	 * 解放
	 */
	virtual void Finalize();

	/**
	 * シーンタイプの取得
	 * @return シーンタイプ
	 */
	virtual SceneType GetSceneType() const = 0;

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
	void DestroyObject(class GameObject* object);

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

	virtual void BookDeleteObject(GameObject* object) { delete_objects_list.push_back(object); }
	virtual void DestroyBookDeleteObject();

protected:
	// シーンで生成したオブジェクト
	std::vector<class GameObject*> objects;
	std::vector<class GameObject*> delete_objects_list;
	// スクロール用スクリーンオフセット
	Vector2D screen_offset;
};