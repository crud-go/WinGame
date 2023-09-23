#include "Particle.h"
Particle::Particle()
	: m_all_time(0.0f)
{
}

Particle::~Particle()
{
}

void Particle::Updata(float dt)
{
	static float last_time = 0.0f;
	m_all_time += dt;

	if (m_all_time - last_time >= 0.5f)
	{
		last_time = m_all_time;

		lizi li;
		li.life = 10.0f;
		li.pos =  vec2<float>(GameData::camera.x + (rand() % 2000 + 1000), -50.0f);
		li.speed =vec2<float>(((rand() % 80) + 50) * -1, rand() % 80 + 50);
		int a = rand() % 4;
		if (a == 0) li.bitmap =Resource::Instance().GetBitmap(L"res\\img\\leave.png");
		if (a == 1) li.bitmap =Resource::Instance().GetBitmap(L"res\\img\\leave2.png");
		if (a == 2) li.bitmap =Resource::Instance().GetBitmap(L"res\\img\\leave3.png");
		if (a == 3) li.bitmap =Resource::Instance().GetBitmap(L"res\\img\\leave4.png");

		m_lizi.push_back(li);
	}

	for (auto& it : m_lizi)
	{
		it.pos += it.speed * dt;
		it.life -= dt;
	}
	for (auto it = m_lizi.begin(); it != m_lizi.end();)
	{
		if (it->life <= 0.0f) it = m_lizi.erase(it);
		else it++;
	}
}

void Particle::Draw()
{
	for (auto& it : m_lizi)
	{
		D2dRender::Instance()->DrawBitmap(it.bitmap, it.pos, vec2<float>(it.bitmap->GetSize().width * 2.0f, it.bitmap->GetSize().height * 2.0f));
	}
}