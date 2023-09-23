#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Player.h"
class TrapShamrock :
    public Leaf
{


	bool Init()override;

	void Updata(float dt) override;

	void Draw() override;

	void OnEvent(Event event) override;

	Animation m_Animation;
	bool isUsed = false;
	bool isGrep = false;
	float BeginTime = 0.0f;


	Trap_Status m_status = Trap_Status::Idle;
	Trap_Status m_last_status = Trap_Status::Idle;

};

