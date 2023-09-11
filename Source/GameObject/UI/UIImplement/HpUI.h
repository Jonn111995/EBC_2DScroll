#pragma once
#include "../UIComponent.h"

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
	void InitializeHP(const int initial_hp);
	void SetHP(const int new_hp);


private:
	int display_hp;
	int max_hp;
	int display_width;
	int hp_guage;
};