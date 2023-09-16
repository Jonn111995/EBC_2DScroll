#pragma once
#include "../UIComponent.h"

class FinishUI : public UIComponent {
public:
	FinishUI();
	virtual ~FinishUI();
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
	void SetDisplayString(const char* display_string) { this->display_string = display_string; };
private:
	const char* display_string;
};
