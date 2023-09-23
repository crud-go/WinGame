#include "Wind.h"

Wind::Wind()
{
}

Wind::~Wind()
{
}

bool Wind::Init()
{
	if (!m_animation1.CreateAnimation(L"res\\img\\wind1.png", L"res\\json\\wind1.json", 0.1f)) return false;
	if (!m_animation2.CreateAnimation(L"res\\img\\wind2.png", L"res\\json\\wind2.json", 0.1f)) return false;
	if (!m_animation3.CreateAnimation(L"res\\img\\wind3.png", L"res\\json\\wind3.json", 0.1f)) return false;
	if (!m_animation4.CreateAnimation(L"res\\img\\wind4.png", L"res\\json\\wind4.json", 0.1f)) return false;

	m_animation1.SetAnimationInfinity(false);
	m_animation2.SetAnimationInfinity(false);
	m_animation3.SetAnimationInfinity(false);
	m_animation4.SetAnimationInfinity(false);

	m_animation1.SetCurrentAnimation("idle");
	m_animation2.SetCurrentAnimation("idle");
	m_animation3.SetCurrentAnimation("idle");
	m_animation4.SetCurrentAnimation("idle");

	return true;
}

void Wind::Updata(float dt)
{

	static float last_time = 0.0f;
	m_all_time += dt;

	if (m_all_time - last_time >= 5.0f)
	{
		last_time = m_all_time;
		int r = rand() % 4;
		if (r == 0) m_now_animation = &m_animation1;
		if (r == 1) m_now_animation = &m_animation2;
		if (r == 2) m_now_animation = &m_animation3;
		if (r == 3) m_now_animation = &m_animation4;
		m_now_animation->SetFrame(0);
	}
	if (m_now_animation != nullptr)
	{
		m_now_animation->Updata(dt);
		
	}
}

void Wind::Draw()
{
	if (m_now_animation != nullptr)
	{
		auto f=m_now_animation->GetCurrentAnimationFrame();
		if (!m_now_animation->isEnd())
			D2dRender::Instance()->DrawBitmap(f, vec2<float>(GameData::camera.x, 0.0f), vec2<float>{f->GetSize().width,f->GetSize().height});
	}
}
