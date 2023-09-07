#pragma once

class Enemy;

/// <summary>
/// 敵キャラのイベント
/// </summary>
class IEnemyEvent {

public:
	/// <summary>
	/// プレイヤーを索敵する
	/// </summary>
	/// <param name="enemy">索敵する敵</param>
	/// <returns>true: プレイヤーを発見 false:発見出来なかった</returns>
	virtual bool SerchPlayer(Enemy* enemy) = 0;
};