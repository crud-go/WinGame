#include "HitBox.h"
bool HitBox::isShowHitbox = false;
void HitBox::Init(HitBox hitbox)
{
}

void HitBox::Draw()
{
}


// （这些碰撞检测的代码都参考了 @javidx9 的视频，非常感谢！ https://www.youtube.com/watch?v=8JJ-4JgR7Dg&t=2828s）
bool HitBox::CollideRectVsLine(HitBox& rect, vec2<float>& lineBegin, vec2<float>& lineEnd, vec2<float>& collPos, vec2<float>& normal, float& coll_time)
{
	collPos = { 0.0f, 0.0f };
	normal = { 0.0f, 0.0f };
	coll_time = 0.0f;

	vec2<float> dir_ = lineEnd - lineBegin;
	vec2<float> invdir = 1.0f / dir_;
	vec2<float> t_near_ = (rect.pos - lineBegin) * invdir;
	vec2<float> t_far_ = (rect.pos + rect.size - lineBegin) * invdir;

	if (std::isnan(t_far_.y) || std::isnan(t_far_.x)) return false;
	if (std::isnan(t_near_.y) || std::isnan(t_near_.x)) return false;

	if (t_near_.x > t_far_.x) std::swap(t_near_.x, t_far_.x);
	if (t_near_.y > t_far_.y) std::swap(t_near_.y, t_far_.y);

	float t_coll_near = max(t_near_.x, t_near_.y);
	float t_coll_far = min(t_far_.x, t_far_.y);

	if (t_near_.x > t_far_.y || t_near_.y > t_far_.x) return false;
	if (t_coll_far < 0.0f) return false;
	if (t_near_.x > 1.0f || t_near_.y > 1.0f) return false;

	collPos = t_coll_near * dir_ + lineBegin;
	coll_time = t_coll_near;

	if (t_near_.x < t_near_.y)
	{
		if (invdir.y < 0)
			normal = { 0, 1 };
		else
			normal = { 0, -1 };
	}
	if (t_near_.x > t_near_.y)
	{
		if (invdir.x < 0)
			normal = { 1, 0 };
		else
			normal = { -1, 0 };
	}
	return true;
}

// （这些碰撞检测的代码都参考了 @javidx9 的视频，非常感谢！ https://www.youtube.com/watch?v=8JJ-4JgR7Dg&t=2828s）
bool HitBox::CollideRectVsRect(const HitBox& in, const HitBox& target, vec2<float>& collPos, vec2<float>& normal, float& coll_time, const float dt)
{
	if (in.speed.x == 0.0f && in.speed.y == 0.0f) return false;

	// 膨胀矩形
	HitBox expansiveRect;
	expansiveRect.pos = target.pos - in.size / 2.0f;
	expansiveRect.size = target.size + in.size;
	expansiveRect.speed = target.speed;

	// 输入矩形的中点
	vec2<float> in_center = { in.pos + in.size / 2.0f };
	// 下一帧矩形的位置
	vec2<float> next_center = in_center + in.speed * dt;

	if (CollideRectVsLine(expansiveRect, in_center, next_center, collPos, normal, coll_time))
	{
		return (coll_time >= 0.0f && coll_time < 1.0f);
	}
	else
	{
		return false;
	}
}

// （这些碰撞检测的代码都参考了 @javidx9 的视频，非常感谢！ https://www.youtube.com/watch?v=8JJ-4JgR7Dg&t=2828s）
bool HitBox::CollideRectVsMoveRect(HitBox& in, HitBox& target, vec2<float>& collPos, vec2<float>& normal, float& collTime, const float dt)
{
	if (target.isWorks == false) return false;

	// 以target的视角看，它自己是不动的，其它的物体都在相对与它运动

	// 新定义一个以target.pos为原点的坐标系的输入矩形
	HitBox newInRect;
	newInRect.pos = in.pos - target.pos;
	newInRect.size = in.size;
	newInRect.speed = in.speed - target.speed;

	if (newInRect.speed.x == 0.0f && newInRect.speed.y == 0.0f) return false;

	// 新定义速度为0的目标矩形
	HitBox newTargetRect;
	newTargetRect.pos = { 0.0f, 0.0f };
	newTargetRect.size = target.size;
	newTargetRect.speed = { 0.0f, 0.0f };

	vec2<float> coll_pos, coll_normal;
	float coll_time;

	if (CollideRectVsRect(newInRect, newTargetRect, coll_pos, coll_normal, coll_time, dt))
	{
		newInRect.speed += coll_normal * vec2<float>(std::abs(newInRect.speed.x), std::abs(newInRect.speed.y)) * (1 - coll_time);

		in.speed = newInRect.speed + target.speed;

		collPos = coll_pos + target.pos;
		normal = coll_normal;
		collTime = coll_time;

		// 由于浮点数的精度问题，导致穿模，这里加上一个偏移量
		in.speed += (vec2<float>(0.1f, 0.1f) * coll_normal);
		return true;
	}
	else
	{
		return false;
	}
}

bool HitBox::RectVsRect(HitBox& b1, HitBox& b2)
{
	if (b1.isWorks == false) return false;
	if (b2.isWorks == false) return false;

	return (
		(abs((b1.pos.x + b1.size.x * 0.5f) - (b2.pos.x + b2.size.x * 0.5f)) < (b1.size.x * 0.5f + b2.size.x * 0.5f))
		&&
		(abs((b1.pos.y + b1.size.y * 0.5f) - (b2.pos.y + b2.size.y * 0.5f)) < (b1.size.y * 0.5f + b2.size.y * 0.5f))
		);
}

