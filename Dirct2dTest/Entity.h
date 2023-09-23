#pragma once
#include"HitBox.h"
enum class Event { StepOn/*���ȵ�*/, Grab/*��ץס*/, Jump/*��Ծ*/, BeginPlay33Animation, EndPlay33Animation };


enum class Type { Normal/*����*/, Trap/*����*/, Lucky/*����*/ };


enum class Player_Status { Ground/*�ڵ���*/, Air/*����*/, Lock/*��ס*/, Climb/*ץ��*/ };

enum class Lucky_Status { Idle/*��̬*/, Move/*�ƶ�*/ };


enum class Trap_Status { Idle/*��̬*/, Timeing/*��ʱ*/, Goneing/*��ʧ��*/, Gone/*������ʧ*/ };

enum class status_33 { None, Fly, Blow, Into_dizzy, Dizzy };

/////////////////////////////////////////////////////////////////////////////////////////

// ������
class Entity
{
public:
	Entity() {};
	virtual ~Entity() {};

	virtual bool Init() { return true; }; //��ʼ�� 
	virtual void Updata(float dt) = 0;//����״̬
	virtual void Draw() = 0; //����ʵ��
	virtual void OnEvent(Event event) = 0;// 

	bool isDie = false;	// �Ƿ�����
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


	HitBox m_hitbox;//ҶƬ����

	HitBox m_hitbox2;//ҶƬβ��

	Entity* m_player;

	D2dRender* m_render;

};