#pragma once
#include"HitBox.h"
enum class Event { StepOn/*被踩到*/, Grab/*被抓住*/, Jump/*跳跃*/, BeginPlay33Animation, EndPlay33Animation };


enum class Type { Normal/*正常*/, Trap/*陷阱*/, Lucky/*幸运*/ };


enum class Player_Status { Ground/*在地面*/, Air/*空中*/, Lock/*锁住*/, Climb/*抓攀*/ };

enum class Lucky_Status { Idle/*静态*/, Move/*移动*/ };


enum class Trap_Status { Idle/*静态*/, Timeing/*计时*/, Goneing/*消失中*/, Gone/*彻底消失*/ };

enum class status_33 { None, Fly, Blow, Into_dizzy, Dizzy };

/////////////////////////////////////////////////////////////////////////////////////////

// 基础类
class Entity
{
public:
	Entity() {};
	virtual ~Entity() {};

	virtual bool Init() { return true; }; //初始化 
	virtual void Updata(float dt) = 0;//更新状态
	virtual void Draw() = 0; //绘制实体
	virtual void OnEvent(Event event) = 0;// 

	bool isDie = false;	// 是否销毁
	float m_all_time = 0.0f;
};


class Leaf :public Entity
{
public:

	virtual bool Init()override {

		m_hitbox = { {0.0f, 0.0f}, {65.0f, 40.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} };
		m_hitbox2 = { {0.0f, 0.0f}, {5.0f, 5.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} };
		m_render = D2dRender::Instance();
		return 1;
	
	};

	virtual void Updata(float dt) override {};

	virtual void Draw() override {};

	virtual void OnEvent(Event event) override {};


	HitBox m_hitbox;//叶片顶部

	HitBox m_hitbox2;//叶片尾部

	Entity* m_player;

	D2dRender* m_render;

};