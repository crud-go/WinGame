#pragma once
#include"Entity.h"
#include"Animation.h"
class LuckyShamrock:public Leaf
{
	// 这个枚举记录玩家是踩着叶子还是抓着叶子
	enum class Status { None, Step, Grab };

	virtual bool Init()override;

	virtual void Updata(float dt) override;

	virtual void Draw() override;

	virtual void OnEvent(Event event) override;

	Animation m_Animation;
	bool isUsed = false;
	float BeginMoveTime = 0.0f;
	Status m_player_status = Status::None;
	Lucky_Status m_status = Lucky_Status::Idle;
	Lucky_Status m_last_status = Lucky_Status::Idle;

};

