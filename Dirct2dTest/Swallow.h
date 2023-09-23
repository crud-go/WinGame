#pragma once
#include"Animation.h"
#include"GameData.h"
class Swallow
{
public:
	Swallow();
	~Swallow();

	bool Init();
	void Updata(float dt);
	void Draw();
	void Reset();

private:
	Animation m_animation;
	
	vec2<float> m_pos = { -500.0f, 0.0f };

	int score = 0;


};

