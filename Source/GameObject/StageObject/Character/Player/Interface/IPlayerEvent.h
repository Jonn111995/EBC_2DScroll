#pragma once

class IPlayerEvent {

	virtual void UpdateHpUI(const int now_hp) = 0;
};