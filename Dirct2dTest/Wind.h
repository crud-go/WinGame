#pragma once
#include"Animation.h"
#include"GameData.h"
class Wind
{
public:
	Wind();
	~Wind();

	bool Init();
	void Updata(float dt);
	void Draw();

private:
	Animation m_animation1;
	Animation m_animation2;
	Animation m_animation3;
	Animation m_animation4;

	Animation* m_now_animation;

	float m_all_time;


};

