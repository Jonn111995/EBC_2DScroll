#pragma once
#include "../../../GameObject/StageObject/Character/Interface/CharacterEventInterface.h"
#include "../Source/GameObject/StageObject/Character/Enemy/Interface/IEnemyEvent.h"
#include "../Source//GameObject/StageObject/Character/Player/Interface/IPlayerEvent.h"
#include "../Source/GameObject/GameState/Interface/IGameStateEvent.h"
#include "../Source/GameObject/StageObject/Item/Interface/IItemEvent.h"
#include "../Source/GameObject/UI/Interface/IUIEvent.h"

class TitleSceneInterface 
	: public CharacterEventInterface, public IPlayerEvent, public IEnemyEvent, public IGameStateEvent, public IItemEvent, public IUIEvent {

};