#pragma once

class UIComponent;

class IUIEvent {
public:
	virtual bool CheckCanFinishUI() = 0;
	virtual void FInishUI(UIComponent* ui_component) = 0;
};