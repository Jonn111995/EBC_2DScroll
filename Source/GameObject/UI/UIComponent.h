#pragma once
#include "../GameObject.h"
#include "../Source/Utility/Vector2D.h"

class IUIEvent;

namespace {
	const float DISPLAY_TIME = 2.f;
}

enum class EUIState : unsigned short {
	kSHOW,
	kHIDE
};

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
	void SetUIState(EUIState ui_state) { this->ui_state = ui_state; }
protected:
	int ui_graphic;
	int font_handle;
	float display_count_time;

	/// <summary>
	/// UIイベント
	/// </summary>
	IUIEvent* ui_event;
	EUIState ui_state;

private:
	void SetUIGraphic(const int new_graphic) { ui_graphic = new_graphic; }
	int GetUIGraphic() const { return ui_graphic; }
};