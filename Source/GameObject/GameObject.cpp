#include "GameObject.h"
#include "../Scene/SceneBase.h"

GameObject::GameObject()
	: draw_sort_priority(0)
{
}

void GameObject::SetDrawSortPriority(int new_priority) {
	draw_sort_priority = new_priority;
}