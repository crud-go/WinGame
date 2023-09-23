#pragma once
#include "AnimationLoader.h"
#include "TimeCounter.h"
class Animation
{

public:

	Animation();
	bool CreateAnimation(const std::wstring& bitmapFile, const std::wstring& jsonFile, float duration);
	void Updata(float dt);
	ID2D1Bitmap1* GetCurrentAnimationFrame();
	bool SetCurrentAnimation(const std::string& name);
	std::vector<std::string> GetAllAnimationName();
	void SetAnimationInfinity(bool flag);
	std::string GetCurrentAnimationName();
	bool isEnd();
	void SetFrame(size_t frame);

	uint32_t GetCurrentFrame();


private:
	_Animation* m_animation;
	_Animation::iterator m_CurrentAnimation;
	TimeCounter timer;
	uint32_t m_frame;
	bool is_end;
	bool IsInfinity;//¶¯»­Ñ­»·²¥·Å




};

