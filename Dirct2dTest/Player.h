#pragma once
#include"HitBox.h"
#include"Animation.h"
#include"UserInput.h"
#include "Entity.h"
#include "GameData.h"
class Player:  public Entity
{

public:
	Player(std::vector<Entity*>& p);
	virtual bool Init();

	virtual void Updata(float dt) override;

	virtual void Draw() override;

	virtual void OnEvent(Event event) override;

	HitBox& getHitbox();

	void setPlayerStatus(Player_Status s);
	

private:

	void UpdataAnimation(float dt);
	void UpdataMove(UserInput::Key& key);
	void UpdataCollide(float dt);
	void UpdataSpeed(float dt);
	void Update33(float dt);

	HitBox m_hitbox;//管理玩家的速度，加速度，碰撞，坐标等
	HitBox m_hitbox2;
	Player_Status currentStatus;//玩家当前状态
	status_33  m_33status= status_33::None;


	D2dRender* render; //绘图

	Animation m_Animation; //22娘的动画管理


	Animation  m_Animation2 ; //33娘的动画管理

	ID2D1Bitmap1* m_33bitmap = nullptr;

	vec2<float> m_33pos = { 0.0f, 0.0f };

	std::vector<Entity*>& m_leaves;
};

