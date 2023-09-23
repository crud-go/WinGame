#include "D2dApp.h"
#include "Particle.h"
#include "Shamrock.h"
#include "Player.h"
#include "TrapShamrock.h"
#include "LuckyShamrock.h"
#include "Swallow.h"
#include "Wind.h"
#include "BackGround.h"
enum class Game_Status { GetReady, Play, GameOver };
class Game :public D2dApp {
    float x, y ;
    ID2D1Bitmap1* m_pbit;
public:
    virtual bool OnUserInit()override {

        m_player = new Player(m_leaves);
		m_player->Init();
        if (!m_bg.Init()) return false;
        if (!m_wind.Init()) return false;

        if (!m_count_animation.CreateAnimation(L"res\\img\\count.png", L"res\\json\\count.json", 1.0f)) return false;
        if (!m_swallow.Init()) return false;

        if (!Reset()) return false;
        return true;
     }
   virtual void OnUserUpdate(float dt)override {

	   m_all_time += dt;
	   GameData::score = m_all_time;
	   // 碰撞箱显示
	   if (UserInput::GetKeyStatus(UserInput::Key::H)->isPress) HitBox::isShowHitbox = !HitBox::isShowHitbox;

	   switch (m_status)
	   {
	   case Game_Status::GetReady:
	   {
		   m_player->Updata(0.0f);
		   for (auto& it : m_leaves) it->Updata(0.0f);
		   m_bg.Updata(0.0f);
		   m_particle.Updata(0.0f);
		   m_wind.Updata(0.0f);
		   m_count_animation.Updata(dt);

		   m_render->BeginDraw();
		   m_render->Clear({ 159.0f / 255.0f, 225.0f / 255.0f, 221.0f / 255.0f, 1.0f });
		   m_bg.Draw();
		   m_particle.Draw();
		   for (auto& it : m_leaves) it->Draw();
		   m_player->Draw();
		   m_wind.Draw();
		   m_render->DrawBitmap(m_count_animation.GetCurrentAnimationFrame(), vec2<float>(700.0f, 0.0f), vec2<float>(100.0f, 100.0f));
		   m_render->EndDraw();

		   if (m_count_animation.isEnd()) m_status = Game_Status::Play;

		   break;
	   }
	   case Game_Status::Play:
	   {
		   // 删掉出窗口的叶子
		   for (auto it = m_leaves.begin(); it != m_leaves.end();)
		   {
			   if (((Leaf*)(*it))->m_hitbox.pos.x <= GameData::camera.x - 200.0f)
			   {
				   it = m_leaves.erase(it);
			   }
			   else
			   {
				   it++;
			   }
		   }

		   // 更新
		   m_player->Updata(dt);
		   for (auto& it : m_leaves) it->Updata(dt);
		   m_bg.Updata(dt);
		   m_particle.Updata(dt);
		   m_wind.Updata(dt);
		   m_swallow.Updata(dt);

		   // 渲染
		   m_render->BeginDraw();
		   m_render->Clear({ 159.0f / 255.0f, 225.0f / 255.0f, 221.0f / 255.0f, 1.0f });

		   m_bg.Draw();
		   m_particle.Draw();
		   m_swallow.Draw();
		   for (auto& it : m_leaves) it->Draw();
		   m_player->Draw();
		   m_wind.Draw();

		   GameData::camera.x += GameData::camera_speed * dt;
		   if (m_player->getHitbox().pos.y < 0.0f) GameData::camera.y = m_player->getHitbox().pos.y;
		   else GameData::camera.y = 0.0f;
		   if (m_player->getHitbox().pos.y > 600.0f) m_status = Game_Status::GameOver;//玩家掉落

		   if (m_player->getHitbox().pos.x + m_player->getHitbox().size.x < GameData::camera.x) m_status = Game_Status::GameOver;//玩家靠左游戏结束

		   m_render->getD2dDeviceContext()->SetTransform(D2D1::Matrix3x2F::Translation(GameData::camera.x * -1, GameData::camera.y * -1));//移动镜头

		   m_render->EndDraw();

		   // 每隔一段时间生成叶子
		   if (m_all_time - m_last_time >= 1.0f)
		   {
			   m_last_time = m_all_time;
			   CreateLeaves();
		   }

		   break;
	   }
	   case Game_Status::GameOver:
	   {
		   m_player->Updata(0.0f);
		   for (auto& it : m_leaves) it->Updata(0.0f);
		   m_bg.Updata(0.0f);
		   m_particle.Updata(dt);
		   m_wind.Updata(dt);

		   m_render->BeginDraw();
		   m_render->Clear({ 159.0f / 255.0f, 225.0f / 255.0f, 221.0f / 255.0f, 1.0f });
		   m_bg.Draw();
		   m_particle.Draw();
		   for (auto& it : m_leaves) it->Draw();
		   m_player->Draw();
		   m_wind.Draw();
		   m_render->DrawTextCenter(L"按“Z”键重试", vec2<float>(GameData::camera.x, 0.0f), vec2<float>(1920.0f, 500.0f), { 0.0f, 0.0f, 0.0f, 1.0f }, 50.0f);
		   m_render->EndDraw();

		   if (UserInput::GetKeyStatus(UserInput::Key::Z)->isPress) this->Reset();

		   break;
	   }
	   default:
		   break;
	   }



    }

	bool Reset()
	{
		m_all_time = 0.0f;
		m_last_time = 0.0f;
		GameData::camera = vec2<float>(0.0f, 0.0f);
		GameData::camera_speed = 150.0f;

		for (auto& it : m_leaves) delete it;
		m_leaves.clear();

		m_leaves.push_back(new NormalShamrock(shamrock1));
		m_leaves.push_back(new NormalShamrock(shamrock2));
		m_leaves.push_back(new TrapShamrock());
		m_leaves.push_back(new NormalShamrock(shamrock3));
		m_leaves.push_back(new NormalShamrock(shamrock4));
		m_leaves.push_back(new NormalShamrock(shamrock3));
		m_leaves.push_back(new NormalShamrock(shamrock1));
		m_leaves.push_back(new NormalShamrock(shamrock4));
		m_leaves.push_back(new NormalShamrock(shamrock1));
		m_leaves.push_back(new NormalShamrock(shamrock3));
		m_leaves.push_back(new NormalShamrock(shamrock2));

		for (auto& it : m_leaves)
		{
			((Leaf*)it)->m_player=m_player;
			if (!it->Init()) return false;
		}

		float b = 700.0f;
		for (size_t i = 0; i != m_leaves.size(); ++i)
		{
			((Leaf*)m_leaves[i])->m_hitbox.pos=vec2<float>(b, 200.0f);
			b += 150.0f;
		}

		m_player->getHitbox().pos=vec2<float>(700.0f, 0.0f);
		m_player->getHitbox().speed = vec2<float>(0.0f, 0.0f);
		m_player->getHitbox().acceleration = vec2<float>(0.0f, 0.0f);
	
		m_render->getD2dDeviceContext()->SetTransform(D2D1::Matrix3x2F::Translation(0.0f, 0.0f));
		m_swallow.Reset();

		m_count_animation.SetFrame(0);

		m_status = Game_Status::GetReady;

		return true;
	}

	bool CreateLeaves()
	{
		int num = rand() % 101;

		Leaf* entity = nullptr;

		if (num >= 0 && num <= 5)
			entity = new LuckyShamrock();
		if (num >= 6 && num <= 20)
			entity = new TrapShamrock();
		if (num >= 21 && num <= 40)
			entity = new NormalShamrock(shamrock1);
		if (num >= 41 && num <= 60)
			entity = new NormalShamrock(shamrock2);
		if (num >= 61 && num <= 80)
			entity = new NormalShamrock(shamrock3);
		if (num >= 81 && num <= 100)
			entity = new  NormalShamrock(shamrock4);

		if (!entity->Init()) return false;
		entity->m_player=m_player;

		entity->m_hitbox.pos=vec2<float>(
			GameData::camera.x + GameData::screen_size.x + 200.0f + (rand() % 100) - 50,
			(float)(rand() % 200 + 100));

		m_leaves.push_back(entity);
		return true;
	}

	// 玩家
	Player* m_player;
	// 叶子
	std::vector<Entity*> m_leaves;
	// 背景
	BackGround m_bg;
	// 下落树叶
	Particle m_particle;
	// 风
	Wind m_wind;
	// 燕子
	Swallow m_swallow;

	Animation m_count_animation;

	Game_Status m_status = Game_Status::GetReady;

	float m_all_time = 0.0f;
	float m_last_time = 0.0f;
};

int WINAPI wWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PWSTR lpCmdLine,
    int nCmdShow)
{

    Game app;
    if (SUCCEEDED(app.init()))
    {
        app.Run();
        app.MessageLoop();
    }

}