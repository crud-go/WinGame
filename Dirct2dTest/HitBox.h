#pragma once
#include"Render.h"
class HitBox  //检测游戏中物体的碰撞
{
public:
	vec2<float> pos;		// 位置
	vec2<float> size;		// 大小
	vec2<float> speed;		// 速度
	vec2<float> acceleration;// 加速度
	bool isWorks = true;	// 是否有效

	void Init(HitBox hitbox);

	void Draw();//


	/**
	 * @brief 检测矩形和线段的碰撞
	 * @param[in] rect 要检测的矩形
	 * @param[in] lineBegin 线段的起点
	 * @param[in] lineEnd 线段的终点
	 * @param[out] collPos 返回线段与矩形碰撞的位置
	 * @param[out] normal 返回线段与矩形碰撞位置的法线
	 * @param[out] coll_time 返回线段与矩形碰撞的位置，占整个线段长度的百分比
	 * @return 碰撞true，无碰撞false（这些碰撞检测的代码都参考了 @javidx9 的视频，非常感谢！ https://www.youtube.com/watch?v=8JJ-4JgR7Dg&t=2828s）
	*/
	static bool CollideRectVsLine(HitBox& rect, vec2<float>& lineBegin, vec2<float>& lineEnd, vec2<float>& collPos, vec2<float>& normal, float& coll_time);

	/**
	 * @brief 检测矩形与矩形的碰撞
	 * @param[in] in 输入矩形
	 * @param[in] target 目标矩形
	 * @param[out] collPos 返回碰撞位置
	 * @param[out] normal 返回碰撞位置的法线
	 * @param[out] coll_time 返回碰撞的位置，占整个线段长度的百分比
	 * @param[in] dt 帧时间间隔
	 * @return 碰撞true，无碰撞false（这些碰撞检测的代码都参考了 @javidx9 的视频，非常感谢！ https://www.youtube.com/watch?v=8JJ-4JgR7Dg&t=2828s）
	*/
	static bool CollideRectVsRect(const HitBox& in, const HitBox& target, vec2<float>& collPos, vec2<float>& normal, float& coll_time, const float dt);

	/**
	 * @brief 检测两个移动矩形的碰撞
	 * @param in 输入矩形，该矩形是受碰撞的那个
	 * @param target 目标矩形，该矩形应该不受到碰撞干扰运动
	 * @param collPos 返回碰撞位置
	 * @param normal 返回碰撞的法向量
	 * @param collTime 返回碰撞的时间
	 * @param dt 输入帧间隔时间
	 * @return 碰撞true，无碰撞false（这些碰撞检测的代码都参考了 @javidx9 的视频，非常感谢！ https://www.youtube.com/watch?v=8JJ-4JgR7Dg&t=2828s）
	*/
	static bool CollideRectVsMoveRect(HitBox& in, HitBox& target, vec2<float>& collPos, vec2<float>& normal, float& collTime, const float dt);

	static bool RectVsRect(HitBox& b1, HitBox& b2);

	static bool isShowHitbox;




};

