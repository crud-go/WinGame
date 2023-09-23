#pragma once
#include"Render.h"
#include<vector>
#include"Resource.h"
#include"GameData.h"
struct back_ground_data
{
	float speed = 0.0f;
	float pos = 0.0f;
	ID2D1Bitmap1* bitmap = nullptr;
};

class BackGround
{
public:
	BackGround();
	virtual ~BackGround();

	bool Init();

	void Updata(float dt);
	void Draw();

private:

	std::vector<back_ground_data*> m_BackGrounds;


	float m_width = 8000.0f;
	float m_height = 500.0f;
};
