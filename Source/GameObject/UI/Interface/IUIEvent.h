#pragma once

class UIComponent;

class IUIEvent {
public:
	virtual void FInishUI(UIComponent* ui_component) = 0;
};