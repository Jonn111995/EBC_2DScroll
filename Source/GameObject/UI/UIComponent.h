#pragma once
#include "../GameObject.h"

class UIComponent : public GameObject {
public:
	UIComponent();
	virtual ~UIComponent();

public:
	/// <inheritdoc/>
	virtual void Initialize() override;
	/// <inheritdoc/>
	virtual void Finalize() override;
	/// <inheritdoc/>
	virtual void Update(float delta_seconds) override;
	///  <inheritdoc/>
	virtual void Draw(const Vector2D& screen_offset) override;

protected:
	int ui_graphic;
private:
	void SetUIGraphic(const int new_graphic) { ui_graphic = new_graphic; }
	int GetUIGraphic() const { return ui_graphic; }
};