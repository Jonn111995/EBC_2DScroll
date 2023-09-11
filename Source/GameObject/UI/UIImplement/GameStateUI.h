#pragma once
#include <string>
#include "../UIComponent.h"

class IGameStateUI;

class GameStateUI : public UIComponent {

public:
	GameStateUI();
	virtual ~GameStateUI();

public:
	/// <inheritdoc/>
	virtual void Initialize() override;
	/// <inheritdoc/>
	virtual void Finalize() override;
	/// <inheritdoc/>
	virtual void Update(float delta_seconds) override;
	///  <inheritdoc/>
	virtual void Draw(const Vector2D& screen_offset) override;

public:
	/// <summary>
	/// UI�̃X�R�A���X�V
	/// </summary>
	/// <param name="new_score">���݃X�R�A</param>
	void SetScore(const int new_score) { display_score = new_score; }
	/// <summary>
	/// UI�̎c�@�����X�V
	/// </summary>
	/// <param name="new_respawn_remain">�c��̎c�@��</param>
	void SetRespawn(const int new_respawn_remain) { display_respawn_remain = new_respawn_remain; };
	/// <summary>
	/// UI�̎c�莞�Ԃ��X�V
	/// </summary>
	/// <param name="remain_time">�c�莞��</param>
	void SetTime(const int remain_time) { display_time = remain_time; }
	/// <summary>
	/// UI�̃X�e�[�W�����X�V
	/// </summary>
	/// <param name="new_stage_name">���݂̃X�e�[�W��</param>
	void SetStageName(const std::string new_stage_name) { stage_name = new_stage_name; }
		
private:
	/// <summary>
	/// UI�ɕ\�����錻�݃X�R�A
	/// </summary>
	int display_score;
	/// <summary>
	/// UI�ɕ\������c�@��
	/// </summary>
	int display_respawn_remain;
	/// <summary>
	/// UI�ɕ\������c�莞��
	/// </summary>
	int display_time;
	/// <summary>
	/// UI�ɕ\������X�e�[�W��
	/// </summary>
	std::string stage_name;
};