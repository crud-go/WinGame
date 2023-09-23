#include "Animation.h"

Animation::Animation():
    m_frame(0),
	IsInfinity(true),
	m_animation(NULL),
	is_end(false)
{

}
bool Animation::CreateAnimation(const std::wstring& bitmapFile, const std::wstring& jsonFile, float duration)
{
	m_animation = AnimationLoader::GetAnimation(bitmapFile, jsonFile, duration);
	if (m_animation != nullptr)
	{
		m_CurrentAnimation = m_animation->begin();
		return true;
	}

	return false;
}



void Animation::Updata(float dt)

{
	if (timer.GetTime() > m_CurrentAnimation->second.second)//判断这一帧的持续时间，如果当前帧的时间用完了就更新下一帧
	{
		is_end = false;
		m_frame++;
		timer.Update();
		if (m_frame >= m_CurrentAnimation->second.first.size())
		{
			if (IsInfinity)//判断动画是否循环播放。
			{
				m_frame = 0;
				is_end = true;
			}
			else
			{
				m_frame = m_CurrentAnimation->second.first.size() - 1;
				is_end = true;
			}
		}
	}


}

ID2D1Bitmap1* Animation::GetCurrentAnimationFrame()
{
	return m_CurrentAnimation->second.first.at(m_frame);//获取当前动画的某一帧
}

bool Animation::SetCurrentAnimation(const std::string& name)
{
	if (name == m_CurrentAnimation->first) return false;
	is_end = false;
	m_frame = 0;               //将动画帧清零
	auto it = m_animation->find(name);
	if (it == m_animation->end())
		return false;
	m_CurrentAnimation = it; //设置新的动画帧
	return true;
}

std::vector<std::string> Animation::GetAllAnimationName()
{
	std::vector<std::string> temp;

	for (auto it = m_animation->begin(); it != m_animation->end(); it++)
	{
		temp.push_back(it->first);
	}

	return temp;//获取所有动画的名字
}

void Animation::SetAnimationInfinity(bool flag)
{


}

std::string Animation::GetCurrentAnimationName()
{
	return m_CurrentAnimation->first;
}

bool Animation::isEnd()
{
    return is_end;
}

void Animation::SetFrame(size_t frame)
{

	m_frame = frame;
}

uint32_t Animation::GetCurrentFrame()
{
	return m_frame;
}
