#pragma once
#include "../UIComponent.h"

/// <summary>
/// HP状態をUITとして表示する
/// </summary>
class HpUI : public UIComponent {

public:
	HpUI();
	virtual ~HpUI();

public:
	/// <inheritdoc/>
	virtual void Initialize() override;
	/// <inheritdoc/>
	virtual void Finalize() override;
	/// <inheritdoc/>
	virtual void Update(float delta_seconds) override;
	///  <inheritdoc/>
	virtual void Draw(const Vector2D& screen_offset) override;

public:
	/// <summary>
	/// HPを初期化する
	/// </summary>
	/// <param name="initial_hp">初期化する値</param>
	void InitializeHP(const int initial_hp);
	/// <summary>
	/// HPを更新する
	/// </summary>
	/// <param name="new_hp"></param>
	void SetHP(const int new_hp);

private:
	/// <summary>
	/// 現在のHP
	/// </summary>
	int display_hp;
	/// <summary>
	/// HPの最大値
	/// </summary>
	int max_hp;
	/// <summary>
	/// HPゲージの横幅
	/// </summary>
	int hp_guage_width;
	/// <summary>
	/// 現在のHPゲージの値
	/// </summary>
	int hp_guage;
};