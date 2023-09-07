#pragma once
#include "../../../GameObject/StageObject/Character/Interface/CharacterEventInterface.h"
#include "../Source/GameObject/StageObject/Character/Enemy/Interface/IEnemyEvent.h"
#include "../Source/GameObject/GameState/Interface/IGameStateEvent.h"

class TitleSceneInterface : public CharacterEventInterface, public IEnemyEvent, public IGameStateEvent {

};