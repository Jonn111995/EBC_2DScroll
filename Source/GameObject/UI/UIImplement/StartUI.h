#pragma once
#include "../UIComponent.h"

class StartUI : public UIComponent {
public:
	StartUI();
	virtual ~StartUI();
public:
	/// <inheritdoc/>
	virtual void Initialize() override;
	/// <inheritdoc/>
	virtual void Finalize() override;
	/// <inheritdoc/>
	virtual void Update(float delta_seconds) override;
	///  <inheritdoc/>
	virtual void Draw(const Vector2D& screen_offset) override;
};