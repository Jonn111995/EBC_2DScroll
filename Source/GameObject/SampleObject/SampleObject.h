#pragma once

#include "../StageObject/StageObject.h"
#include <vector>

class Vector2D;

/**
 * サンプルオブジェクト
 * サンプル用に簡易的に実装
 */
class SampleObject : public StageObject
{
public:
	SampleObject();
	virtual ~SampleObject();
	float count = 0.0f;
public:
	//~ Begin GameObject interface
	virtual void Initialize() override;
	virtual void Update(float delta_seconds) override;
	virtual void Draw(const Vector2D& screen_offset) override;
	virtual void Finalize() override;
	//~ End GameObject interface

private:
	int loaded_sprite_handle;
	int loaded_sprits[4];
};