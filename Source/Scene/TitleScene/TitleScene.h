#pragma once
#include "../SceneBase.h"


class TitleScene : public SceneBase {
public:
	TitleScene();
	virtual ~TitleScene();
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
	virtual SceneType GetSceneType() const override { return SceneType::TITLE_SCENE; };

	/// <summary>
	/// 削除予定のオブジェクトを予約
	/// </summary>
	/// <param name="delete_object">削除対象オブジェクト</param>
	virtual void BookDeleteObject(GameObject* delete_object) { delete_objects_list.push_back(delete_object); }

	/// <summary>
	/// 削除予定のオブジェクトを削除
	/// </summary>
	virtual void DestroyBookDeleteObject();
private:
	int title_graphic;
};