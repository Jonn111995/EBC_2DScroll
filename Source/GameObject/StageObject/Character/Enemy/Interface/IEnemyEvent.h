#pragma once

class Enemy;

class IEnemyEvent {

public:
	virtual bool SerchPlayer(Enemy* enemy) = 0;
};