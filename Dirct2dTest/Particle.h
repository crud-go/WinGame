#pragma once
#include"Render.h"
#include<vector>
#include"Resource.h"
#include"GameData.h"
class Particle
{

	struct lizi
	{
		float life;
		vec2<float> pos;
		vec2<float> speed;
		ID2D1Bitmap1* bitmap;
	};

public:
	Particle();
	~Particle();

	void Updata(float dt);
	void Draw();


private:
	std::vector<lizi> m_lizi;
	float m_all_time;


};

