#pragma once

class Enemy;

/// <summary>
/// �G�L�����̃C�x���g
/// </summary>
class IEnemyEvent {

public:
	/// <summary>
	/// �v���C���[�����G����
	/// </summary>
	/// <param name="enemy">���G����G</param>
	/// <returns>true: �v���C���[�𔭌� false:�����o���Ȃ�����</returns>
	virtual bool SerchPlayer(Enemy* enemy) = 0;
};