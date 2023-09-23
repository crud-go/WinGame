#include "TrapShamrock.h"

bool TrapShamrock::Init()
{
	Leaf::Init();
	auto re = m_Animation.CreateAnimation(L"res/img/shamrock_trap.png", L"res/json/shamrock_trap.json", 0.1f);
	assert(re);	
	m_Animation.SetCurrentAnimation("idle");
	return true;
}

void TrapShamrock::Updata(float dt)
{
	m_all_time += dt;
	auto player = dynamic_cast<Player*>(m_player);
	switch (m_status)
	{
	case Trap_Status::Idle:
	{
		m_Animation.Updata(dt);
		if (isGrep == true)
		{
	
			player->getHitbox().pos = vec2<float>(m_hitbox2.pos.x - 30.0f, m_hitbox2.pos.y - 20.0f);
		}
		break;
	}
	case Trap_Status::Timeing:
	{
		m_Animation.Updata(dt);
		if (isGrep == true)
		{
	
			player->getHitbox().pos = vec2<float>(m_hitbox2.pos.x - 30.0f, m_hitbox2.pos.y - 20.0f);
		}
		if ((m_all_time - BeginTime) >= 0.3f)
		{
			m_status=(Trap_Status::Goneing);
			m_Animation.SetCurrentAnimation("vanish");
			m_hitbox.isWorks = false;
			m_hitbox2.isWorks = false;
		}
		break;
	}
	case Trap_Status::Goneing:
	{
		m_Animation.Updata(dt);
		if (isGrep == true)
		{
			
			player->setPlayerStatus(Player_Status::Air);
			isGrep = false;
		}
		if (m_Animation.isEnd())
		{
			m_status=(Trap_Status::Gone);
		}
		break;
	}
	case Trap_Status::Gone:
	{

		break;
	}
	default:
		break;
	}

	// ¸üÐÂÎ»ÖÃ
	m_hitbox.pos += m_hitbox.speed * dt;
	m_hitbox2.pos = vec2<float>(m_hitbox.pos.x + 40.0f, m_hitbox.pos.y + 85.0f);

	///m_hitbox.speed.y = sin(m_all_time + rand_num) * rand_num * 0.5f;


}

void TrapShamrock::Draw()
{
	if (m_status != Trap_Status::Gone)
	{
		auto CurrnentAnimation = m_Animation.GetCurrentAnimationFrame();
		m_render->DrawBitmap(
			CurrnentAnimation,
			vec2<float>(m_hitbox.pos.x - 170.0f, m_hitbox.pos.y - 180.0f),
			vec2<float>(CurrnentAnimation->GetSize().width * 2.0f, CurrnentAnimation->GetSize().height * 2.0f)
		);
	}
}

void TrapShamrock::OnEvent(Event event)
{

	switch (event)
	{
	case Event::StepOn:
	{
		if (isUsed == true) break;
		isUsed = true;
		BeginTime = m_all_time;
		m_status=(Trap_Status::Timeing);

		break;
	}
	case Event::Grab:
	{
		if (isUsed == false) BeginTime = m_all_time;
		if (isUsed == false) m_status=(Trap_Status::Timeing);
		isUsed = true;
		isGrep = true;
		auto player = dynamic_cast<Player*>(m_player);
		player->setPlayerStatus(Player_Status::Climb);
		player->getHitbox().acceleration =vec2<float>(0.0f, 0.0f);
		player->getHitbox().speed = vec2<float>(0.0f, 0.0f);

		break;
	}
	case Event::Jump:
	{
		isGrep = false;
		break;
	}
	default:
		break;
	}


}
