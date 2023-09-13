#pragma once
#include "../UIComponent.h"

/// <summary>
/// HP��Ԃ�UIT�Ƃ��ĕ\������
/// </summary>
class HpUI : public UIComponent {

public:
	HpUI();
	virtual ~HpUI();

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
	/// HP������������
	/// </summary>
	/// <param name="initial_hp">����������l</param>
	void InitializeHP(const int initial_hp);
	/// <summary>
	/// HP���X�V����
	/// </summary>
	/// <param name="new_hp"></param>
	void SetHP(const int new_hp);

private:
	/// <summary>
	/// ���݂�HP
	/// </summary>
	int display_hp;
	/// <summary>
	/// HP�̍ő�l
	/// </summary>
	int max_hp;
	/// <summary>
	/// HP�Q�[�W�̉���
	/// </summary>
	int hp_guage_width;
	/// <summary>
	/// ���݂�HP�Q�[�W�̒l
	/// </summary>
	int hp_guage;
};