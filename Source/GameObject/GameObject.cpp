#include "GameObject.h"
#include "../Scene/SceneBase.h"

GameObject::GameObject()
	: draw_sort_priority(0)
	, game_object_state(EGameObjectState::kPAUSE)
	, active_state(EActivation::kACTIVE)
{
}

void GameObject::Initialize() {
	game_object_state = EGameObjectState::kPAUSE;
	active_state = EActivation::kACTIVE;
}

void GameObject::SetDrawSortPriority(int new_priority) {
	draw_sort_priority = new_priority;
}