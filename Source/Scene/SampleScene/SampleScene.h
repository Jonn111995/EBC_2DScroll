#pragma once

#include "../SceneBase.h"

class Field;

/**
 * �T���v���V�[��
 * �T���v���p�ɊȈՓI�Ɏ���
 */
class SampleScene : public SceneBase
{
public:
	SampleScene();
	virtual ~SampleScene() {}

	Field* field;

public:
	//~ Begin CSceneBase interface
	virtual void Initialize() override;	
	virtual SceneType Update(float delta_seconds) override;
	virtual void Draw() override;
	virtual void Finalize() override;
	virtual SceneType GetSceneType() const override { return SceneType::SAMPLE_SCENE; }
	//~ End SceneBase interface
};