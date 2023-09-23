#include "LuckyShamrock.h"
#include "GameData.h"
#include "Player.h"

bool LuckyShamrock::Init()
{
	Leaf::Init();
	auto re=m_Animation.CreateAnimation(L"res/img/shamrock_lucky.png", L"res/json/shamrock_lucky.json", 0.1f);
	assert(re);
	m_Animation.SetCurrentAnimation("idle");
	return true;
}

void LuckyShamrock::Updata(float dt)
{
	auto player = dynamic_cast<Player*>(m_player);
	m_all_time += dt;

	m_Animation.Updata(dt);

	switch (m_status)
	{
	case Lucky_Status::Idle:
	{
		if (m_player_status == Status::Grab)
		{
	        
			dynamic_cast<Player*>(m_player)->getHitbox().pos = vec2<float>(m_hitbox2.pos.x - 30.0f, m_hitbox2.pos.y - 20.0f);
		}

		break;
	}
	case Lucky_Status::Move:
	{
		isUsed = true;
	

		// 延时停止叶子
		if ((m_all_time - BeginMoveTime) >= 20.0f)
		{
			m_hitbox.speed.x = 0.0f;
			m_status=(Lucky_Status::Idle);

			if (m_player_status == Status::Step)
			{
				
				player->setPlayerStatus(Player_Status::Air);
				player->getHitbox().pos.y =
					m_hitbox.pos.y - player->getHitbox().size.y - 0.1f;
				m_player->OnEvent(Event::EndPlay33Animation);
			}
			if (m_player_status == Status::Grab)
			{
				player->OnEvent(Event::EndPlay33Animation);
			}
			return;
		}

		if (m_player_status == Status::Step)
		{
			player->getHitbox().pos = vec2<float>(
				m_hitbox.pos.x + (m_hitbox.size.x - player->getHitbox().size.x) * 0.5f,
				m_hitbox.pos.y - player->getHitbox().size.y
			);
		}
		if (m_player_status == Status::Grab)
		{
			player->getHitbox().pos = vec2<float>(m_hitbox2.pos.x - 30.0f, m_hitbox2.pos.y - 20.0f);
		}
		if (m_hitbox.pos.x >= GameData::camera.x + 1600)
		{
			m_hitbox.speed.x = GameData::camera_speed;
		}

		player->getHitbox().speed = vec2<float>(0.0f, 0.0f);
		player->getHitbox().acceleration = vec2<float>(0.0f, 0.0f);
		break;
	}
	default:
		break;
	}

	// 更新位置
	m_hitbox.pos += m_hitbox.speed * dt;
	m_hitbox2.pos = vec2<float>(m_hitbox.pos.x + 25.0f, m_hitbox.pos.y + 85.0f);

	//m_hitbox.speed.y = sin(m_all_time + rand_num) * rand_num * 0.5f;
}

void LuckyShamrock::Draw()
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

void LuckyShamrock::OnEvent(Event event)
{
	auto player = dynamic_cast<Player*>(m_player);

	switch (event)
	{
	case Event::StepOn:
	{
		if (isUsed == true) break;
		isUsed = true;

		m_player_status = Status::Step;

		BeginMoveTime = m_all_time;
		m_hitbox.speed.x = GameData::camera_speed + 50.0f;
		player->setPlayerStatus(Player_Status::Lock);
		player->OnEvent(Event::BeginPlay33Animation);
		m_status=(Lucky_Status::Move);

		break;
	}
	case Event::Grab:
	{
		if (isUsed == false)
		{
			// 只在第一次被抓住时执行一次
			isUsed = true;
			m_player_status = Status::Grab;
			BeginMoveTime = m_all_time;
			m_hitbox.speed.x = GameData::camera_speed + 50.0f;
			m_status=(Lucky_Status::Move);
			player->setPlayerStatus(Player_Status::Climb);
			player->getHitbox().acceleration = vec2<float>(0.0f, 0.0f);
			player->getHitbox().speed = vec2<float>(0.0f, 0.0f);
			m_player->OnEvent(Event::BeginPlay33Animation);
		}
		else
		{
			m_player_status = Status::Grab;
			player->setPlayerStatus(Player_Status::Climb);
			player->getHitbox().acceleration = vec2<float>(0.0f, 0.0f);
			player->getHitbox().speed = vec2<float>(0.0f, 0.0f);
		}

		break;
	}
	case Event::Jump:
	{
		m_player_status = Status::None;
		m_status=(Lucky_Status::Idle);
		m_hitbox.speed.x = 0.0f;
		m_player->OnEvent(Event::EndPlay33Animation);

		break;
	}
	default:
		break;
	}

}
