#pragma once
#include "../../../GameObject/StageObject/Character/Interface/CharacterEventInterface.h"
#include "../Source/GameObject/StageObject/Character/Enemy/Interface/IEnemyEvent.h"

class TitleSceneInterface : public CharacterEventInterface, public IEnemyEvent {

};