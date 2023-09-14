#pragma once
#include "../GameObject.h"

class IUIEvent;

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
public:
	/// <summary>
	/// UIEventをセットする
	/// </summary>
	/// <param name="ui_event"></param>
	void SetIUIEvent(IUIEvent* ui_event) { this->ui_event = ui_event; }

protected:
	int ui_graphic;
	/// <summary>
	/// UIイベント
	/// </summary>
	IUIEvent* ui_event;

private:
	void SetUIGraphic(const int new_graphic) { ui_graphic = new_graphic; }
	int GetUIGraphic() const { return ui_graphic; }
};