#include "Swallow.h"
Swallow::Swallow()
{
}

Swallow::~Swallow()
{
}

bool Swallow::Init()
{
	if (!m_animation.CreateAnimation(L"res\\img\\swallow.png", L"res\\json\\swallow.json", 0.1f)) return false;
	return true;
}

void Swallow::Updata(float dt)
{
	if (int(GameData::score) % 30 == 0)
	{
		m_pos = vec2<float>(GameData::camera.x + GameData::screen_size.x, 0.0f);
		score = int(GameData::score);
	}
	m_animation.Updata(dt);
	
	m_pos.x -= 100.0f * dt;

}

void Swallow::Draw()
{
	auto f = m_animation.GetCurrentAnimationFrame();
	D2dRender::Instance()->DrawBitmap(f, m_pos, vec2<float>(f->GetSize().width * 2.0f, f->GetSize().height * 2.0f));
	D2dRender::Instance()->DrawTextCenter(
		std::to_wstring(score),
		vec2<float>(m_pos.x, m_pos.y + 20.0f),
		vec2<float>(f->GetSize().width * 2.0f, f->GetSize().height * 2.0f),
		{ 0.0f, 0.0f, 0.0f, 1.0f }, 40.0f);
}

void Swallow::Reset()
{
	m_pos = vec2<float>(-500.0f, 0.0f);
	score = 0;
}
