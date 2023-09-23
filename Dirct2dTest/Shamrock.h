#pragma once
#include"Animation.h"
#include"Render.h"
#include "Player.h"
enum ShamrockType {
	shamrock1=1,shamrock2,shamrock3,shamrock4
};
class NormalShamrock:public Leaf
{
public:
	NormalShamrock(ShamrockType tp);

	virtual bool Init()override;

	virtual void Updata(float dt) override;

	virtual void Draw() override;

	virtual void OnEvent(Event event) override;
private:
	Animation m_Animation;
	int type;
	bool isGrab=false;

};

