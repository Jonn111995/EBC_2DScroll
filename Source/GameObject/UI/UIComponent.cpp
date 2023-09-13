#include "UIComponent.h"

UIComponent::UIComponent()
{
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
