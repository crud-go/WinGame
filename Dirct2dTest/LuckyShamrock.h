#pragma once
#include"Entity.h"
#include"Animation.h"
class LuckyShamrock:public Leaf
{
	// ���ö�ټ�¼����ǲ���Ҷ�ӻ���ץ��Ҷ��
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

