#pragma once
#include "../../../GameObject/StageObject/Character/Interface/CharacterEventInterface.h"
#include "../Source/GameObject/StageObject/Character/Enemy/Interface/IEnemyEvent.h"
#include "../Source//GameObject/StageObject/Character/Player/Interface/IPlayerEvent.h"
#include "../Source/GameObject/GameState/Interface/IGameStateEvent.h"
#include "../Source/GameObject/StageObject/Item/Interface/IItemEvent.h"
#include "../Source/GameObject/UI/Interface/IUIEvent.h"
#include "../Source/GameObject/StageObject/KillObject/Interface/IKillEvent.h"
#include "../Source/GameObject/StageObject/Goal/Interface/IGoalEvent.h"

class TitleSceneInterface 
	: public CharacterEventInterface, public IPlayerEvent, public IEnemyEvent, public IGameStateEvent, public IItemEvent, public IUIEvent, public IKillEvent, public IGoalEvent {

};