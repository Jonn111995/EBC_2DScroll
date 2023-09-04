#pragma once

#include "../SceneBase.h"
#include "../Source/Scene/TitleScene/Interface/TitleSceneInterface.h"

class Field;
class Player;

/**
 * サンプルシーン
 * サンプル用に簡易的に実装
 */
class SampleScene : public SceneBase, public TitleSceneInterface
{
public:
	SampleScene();
	virtual ~SampleScene() {}

public:
	//~ Begin CSceneBase interface
	virtual void Initialize() override;	
	virtual SceneType Update(float delta_seconds) override;
	virtual void Draw() override;
	virtual void Finalize() override;
	virtual SceneType GetSceneType() const override { return SceneType::SAMPLE_SCENE; }
	bool CheckCanMove(const Vector2D& move_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) override;
	bool CheckCanStand(Vector2D& move_to_position, const BoxCollisionParams& collision) override;
	virtual bool CheckCanMoveToX(const Vector2D& move_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) override;
	virtual bool CheckCanMoveToY(const Vector2D& move_to_position, const Vector2D& move_amount, const BoxCollisionParams& collision) override;
	virtual void AddWeapon(BaseWeapon& weapon) override;
	virtual void RemoveWeapon(BaseWeapon* weapon) override;

	//~ End SceneBase interface

private:
	/// <summary>
	/// マップデータの管理
	/// </summary>
	Field* field;

	/// <summary>
	/// プレイヤー
	/// </summary>
	Player* player;

};