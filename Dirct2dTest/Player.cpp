#include "Player.h"

Player::Player(std::vector<Entity*>& lfs):
	m_leaves(lfs)
{



}

bool Player::Init()
{

	render = D2dRender::Instance();

	m_hitbox = { {0.0f, 0.0f}, {40.0f, 80.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} };
	m_hitbox2 = { {0.0f, 0.0f}, {120.0f, 110.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} };
	m_Animation.CreateAnimation(L"res/img/22.png", L"res/json/22.json", 0.1f);
	m_Animation.SetCurrentAnimation("idle");
	m_Animation2.CreateAnimation(L"res/img/33.png", L"res/json/33.json", 0.1f);

	return 1;
}

void Player::Updata(float dt)
{
	Update33(dt);

	static UserInput::Key key{};

	if (UserInput::GetKeyStatus(UserInput::Key::D)->isPress)
		key = UserInput::Key::D;
	if (UserInput::GetKeyStatus(UserInput::Key::A)->isPress) //获取当前的按键状态
		key = UserInput::Key::A;

	this->UpdataAnimation(dt);

	switch (currentStatus)
	{
	case Player_Status::Ground:
	{
		m_hitbox.acceleration.y = 1000.0f;
		this->UpdataMove(key);//设置加速度
		this->UpdataSpeed(dt);
		this->UpdataCollide(dt);

		if (UserInput::GetKeyStatus(UserInput::Key::SPACE)->isHold)
		{
			m_hitbox.speed.y = -590.0f;
			  Player_Status::Air;
		}
		if (UserInput::GetKeyStatus(UserInput::Key::K)->isPress)
		{
			for (auto& it : m_leaves)
			{
				if (!HitBox::RectVsRect(m_hitbox2, ((Leaf*)it)->m_hitbox2)) continue;
				it->OnEvent(Event::Grab);
			}
		}


		break;
	}
	case Player_Status::Air:
	{
		m_hitbox.acceleration.y = 1000.0f;
		this->UpdataMove(key);
		this->UpdataSpeed(dt);
		this->UpdataCollide(dt);

		if (UserInput::GetKeyStatus(UserInput::Key::K)->isPress)
		{
			for (auto& it : m_leaves)
			{
				if (!HitBox::RectVsRect(m_hitbox2, ((Leaf*)it)->m_hitbox2)) continue;
				it->OnEvent(Event::Grab);
			}
		}

		break;
	}
	case Player_Status::Lock:
	{
		if (key == UserInput::Key::D)
		{
			m_Animation.SetCurrentAnimation("idle");
		}
		if (key == UserInput::Key::A)
		{
			m_Animation.SetCurrentAnimation("idle_left");
		}

		if (UserInput::GetKeyStatus(UserInput::Key::SPACE)->isPress)
		{
			m_hitbox.speed.y = -590.0f;
			currentStatus=Player_Status::Air;
			for (auto& it : m_leaves) it->OnEvent(Event::Jump);
		}

		break;
	}
	case Player_Status::Climb:
	{
		if (m_Animation.GetCurrentAnimationName() != "climb")
			m_Animation.SetCurrentAnimation("into_climb");
		if (m_Animation.GetCurrentAnimationName() == "into_climb" && m_Animation.isEnd())
			m_Animation.SetCurrentAnimation("climb");

		if (UserInput::GetKeyStatus(UserInput::Key::SPACE)->isHold)
		{
			m_hitbox.speed.y = -590.0f;
			currentStatus=Player_Status::Air;
			for (auto& it : m_leaves) it->OnEvent(Event::Jump);
		}

		break;
	}
	default:
		break;
	}

	// 更新位置
	m_hitbox.pos += m_hitbox.speed * dt;
	m_hitbox2.pos = vec2<float>(m_hitbox.pos.x - 40.0f, m_hitbox.pos.y - 30.0f);


}

void Player::Draw()
{
	auto CurrentAnimationBitmap= m_Animation.GetCurrentAnimationFrame();
	render->DrawBitmap(
		CurrentAnimationBitmap,
		vec2<float>(m_hitbox.pos.x - 45.0f, m_hitbox.pos.y - 23.0f),
		vec2<float>(CurrentAnimationBitmap->GetSize().width * 2.0f, CurrentAnimationBitmap->GetSize().height * 2.0f)
	);

	m_33bitmap = m_Animation2.GetCurrentAnimationFrame();
	if (m_33status != status_33::None && m_33bitmap != nullptr)
	{
		render->DrawBitmap(
			m_33bitmap,
			vec2<float>(m_33pos.x, m_33pos.y),
			vec2<float>(m_33bitmap->GetSize().width * 2.0f, m_33bitmap->GetSize().height * 2.0f)
		);
	}

}

void Player::OnEvent(Event event)
{

	switch (event)
	{
	case Event::StepOn:
		break;
	case Event::Grab:
		break;
	case Event::Jump:
		break;
	case Event::BeginPlay33Animation:
	{
		m_33status = status_33::Fly;
		break;
	}
	case Event::EndPlay33Animation:
	{
		m_33status = status_33::Into_dizzy;
		break;
	}
	default:
		break;
	}
}

HitBox& Player::getHitbox()
{
	return m_hitbox;
}

void Player::setPlayerStatus(Player_Status s)
{
	currentStatus = s;
}

void Player::UpdataAnimation(float dt)
{

	static UserInput::Key key{};

	m_Animation.Updata(dt); //推动当前的动画播放


	//根据玩家的状态改变当前动画
	if (currentStatus == Player_Status::Ground)
	{
		// 这里 key 变量其实是上一次的值，因为更新 key 值的代码在下面呢！=w=
		// 我们可以利用这个特性获得玩家正确的面向方向
		if (key == UserInput::Key::A)
		{
			if (m_hitbox.speed.x == 0.0f) m_Animation.SetCurrentAnimation("idle_left");
			if (m_hitbox.speed.x < 0.0f) m_Animation.SetCurrentAnimation("run_left");
		}
		else if (key == UserInput::Key::D)
		{
			if (m_hitbox.speed.x == 0.0f) m_Animation.SetCurrentAnimation("idle");
			if (m_hitbox.speed.x > 0.0f) m_Animation.SetCurrentAnimation("run");
		}
	}
	if (currentStatus == Player_Status::Air)
	{
		if (key == UserInput::Key::A)
		{
			if (m_hitbox.speed.y < 0.0f) m_Animation.SetCurrentAnimation("jump_left");
			if (m_hitbox.speed.y > 0.0f) m_Animation.SetCurrentAnimation("fall_left");
		}
		else if (key == UserInput::Key::D)
		{
			if (m_hitbox.speed.y < 0.0f) m_Animation.SetCurrentAnimation("jump");
			if (m_hitbox.speed.y > 0.0f) m_Animation.SetCurrentAnimation("fall");
		}
	}

	if (UserInput::GetKeyStatus(UserInput::Key::D)->isPress)
		key = UserInput::Key::D;

	if (UserInput::GetKeyStatus(UserInput::Key::A)->isPress)
		key = UserInput::Key::A;

	if (currentStatus == Player_Status::Climb)
	{
		if (m_Animation.GetCurrentAnimationName() == "into_climb" && m_Animation.GetCurrentFrame() == 8)
		{
			m_Animation.SetCurrentAnimation("climb");
		}
	}

}

void Player::UpdataMove(UserInput::Key& key)
{
	// 更新加速度
	float moveAcc = 1800.0f;	// 移动加速度
	float fricAcc = 1000.0f;	// 地面摩擦力加速度
	float airfAcc = 100.0f;		// 空气阻力加速度
	switch (key)
	{
	case UserInput::Key::D:
	{
		if (UserInput::GetKeyStatus(UserInput::Key::D)->isHold)
		{
			m_hitbox.acceleration.x = moveAcc;	// 移动加速度
		}
		else
		{
			if (m_hitbox.speed.x > 0.0f)
			{
				if (currentStatus == Player_Status::Ground)
					m_hitbox.acceleration.x = -fricAcc;	// 地面摩擦力加速度
				else
					m_hitbox.acceleration.x = -airfAcc;	// 空气阻力加速度
			}
			else
			{
				m_hitbox.acceleration.x = 0.0f;
				m_hitbox.speed.x = 0.0f;
			}
		}
		break;
	}
	case UserInput::Key::A:
	{
		if (UserInput::GetKeyStatus(UserInput::Key::A)->isHold)
		{
			m_hitbox.acceleration.x = -moveAcc;
		}
		else
		{
			if (m_hitbox.speed.x < 0.0f)
			{
				if (currentStatus == Player_Status::Ground)
					m_hitbox.acceleration.x = fricAcc;
				else if (currentStatus == Player_Status::Air)
					m_hitbox.acceleration.x = airfAcc;
			}
			else
			{
				m_hitbox.acceleration.x = 0.0f;
				m_hitbox.speed.x = 0.0f;
			}
		}
		break;
	}
	}


}

void Player::UpdataCollide(float dt)
{
	vec2<float> coll_pos, coll_normal;
	float coll_time;

	bool flag = false;
	for (auto& it : m_leaves)
	{
		if (((Leaf*)it)->m_hitbox.pos.y >= m_hitbox.pos.y + m_hitbox.size.y)
		{
			if (HitBox::CollideRectVsMoveRect(m_hitbox, ((Leaf*)it)->m_hitbox,
				coll_pos, coll_normal, coll_time, dt))
			{
				flag = true;
				currentStatus=Player_Status::Ground;
				((Leaf*)it)->OnEvent(Event::StepOn);
			}
		}
	}
	if (flag == false) currentStatus=Player_Status::Air;

}

void Player::UpdataSpeed(float dt)
{
	// 更新速度
	m_hitbox.speed += m_hitbox.acceleration * dt;
	// 限制一下玩家的速度
	if (m_hitbox.speed.x >= 250.0f) m_hitbox.speed.x = 250.0f;
	if (m_hitbox.speed.x <= -250.0f) m_hitbox.speed.x = -250.0f;


}

void Player::Update33(float dt)
{

	static vec2<float> off_33_pos = vec2<float>(0.0f, 0.0f);
	m_Animation2.Updata(dt);

	switch (m_33status)
	{
	case status_33::None:
		break;
	case status_33::Fly:
	{
		m_Animation2.SetCurrentAnimation("fly");

		if (off_33_pos.x < m_hitbox.pos.x - GameData::camera.x - 200.0f) off_33_pos.x += 200.0f * dt;
		else m_33status = status_33::Blow;
		off_33_pos.y = m_hitbox.pos.y;

		m_33pos.x = GameData::camera.x + off_33_pos.x;
		m_33pos.y = off_33_pos.y;

		break;
	}
	case status_33::Blow:
	{
		m_Animation2.SetCurrentAnimation("blow");
		m_33pos = vec2<float>(m_hitbox.pos.x - 200.0f, m_hitbox.pos.y);

		break;
	}
	case status_33::Into_dizzy:
	{
		m_Animation2.SetCurrentAnimation("into_dizzy");

		if (m_Animation2.isEnd())
			m_33status = status_33::Dizzy;

		break;
	}
	case status_33::Dizzy:
	{
		m_Animation2.SetCurrentAnimation("dizzy");

		m_33pos.x -= 200.0f * dt;

		if (m_33pos.x <= GameData::camera.x)
		{
			m_33status = status_33::None;
			off_33_pos = vec2<float>(0.0f, 0.0f);
		}

		break;
	}
	default:
		break;
	}
}
