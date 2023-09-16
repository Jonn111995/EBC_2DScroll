#include "UIComponent.h"

UIComponent::UIComponent()
	: ui_state(EUIState::kHIDE)
	, ui_event(nullptr)
	, ui_graphic(0)
	, display_count_time(0.f)
{
	draw_sort_priority = 1;
	active_state = EActivation::kNONE_ACTIVE;
}

UIComponent::~UIComponent()
{
}

void UIComponent::Initialize() {
	__super::Initialize();
}

void UIComponent::Finalize() {
	__super::Finalize();
}

void UIComponent::Update(float delta_seconds) {
	__super::Update(delta_seconds);
}

void UIComponent::Draw(const Vector2D& screen_offset) {
	__super::Draw(screen_offset);
}
