#include "Shamrock.h"

NormalShamrock::NormalShamrock(ShamrockType tp)
{

	type = tp;
}

bool NormalShamrock::Init()
{
	Leaf::Init();

	switch (type)
	{
	case 1:
		m_Animation.CreateAnimation(L"res/img/shamrock1.png", L"res/json/shamrock1.json", 0.1f);
		break;
	case 2:
		m_Animation.CreateAnimation(L"res/img/shamrock2.png", L"res/json/shamrock2.json", 0.1f);
	
		break;
	case 3:
		m_Animation.CreateAnimation(L"res/img/shamrock3.png", L"res/json/shamrock3.json", 0.1f);
	    break;
	case 4:
		m_Animation.CreateAnimation(L"res/img/shamrock4.png", L"res/json/shamrock4.json", 0.1f);
		break;

	default:
		assert(0);
	}
	
	m_Animation.SetCurrentAnimation("idle");

	return true;
	//rand_num = rand() % 50 + 30;
	

}

void NormalShamrock::Updata(float dt)
{
	m_all_time += dt;

	m_hitbox.speed += m_hitbox.acceleration * dt;


	m_Animation.Updata(dt);

	if (isGrab == true)
	{
		Player* player = ((Player*)m_player);

		player->getHitbox().pos = vec2<float>(m_hitbox2.pos.x - 30.0f, m_hitbox2.pos.y - 20.0f);
	}

	// ¸üÐÂÎ»ÖÃ
	m_hitbox.pos += m_hitbox.speed * dt;
	m_hitbox2.pos =vec2<float>(m_hitbox.pos.x + 40.0f, m_hitbox.pos.y + 85.0f);

	//m_hitbox.speed.y = sin(m_all_time + rand_num) * rand_num * 0.5f;



}

void NormalShamrock::Draw()
{
	auto CurrnentAnimation = m_Animation.GetCurrentAnimationFrame();
	m_render->DrawBitmap(
		CurrnentAnimation,
		vec2<float>(m_hitbox.pos.x - 13.0f, m_hitbox.pos.y - 30.0f),
		vec2<float>(CurrnentAnimation->GetSize().width * 2.0f, CurrnentAnimation->GetSize().height * 2.0f)
	);

	//m_hitbox.(rt);
	//m_hitbox2->Render(rt);
}

void NormalShamrock::OnEvent(Event event)
{
	switch (event)
	{
	case Event::StepOn:
	{

		break;
	}
	case Event::Grab:
	{
		auto player = dynamic_cast<Player*>(m_player);
		isGrab = true;
		player->setPlayerStatus(Player_Status::Climb);

		player->getHitbox().acceleration = vec2<float>(0.0f, 0.0f);
		player->getHitbox().speed = vec2<float>(0.0f, 0.0f);

		break;
	}
	case Event::Jump:
	{
		isGrab = false;
		break;
	}
	default:
		break;
	}


}
