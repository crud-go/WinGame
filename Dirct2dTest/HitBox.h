#pragma once
#include"Render.h"
class HitBox  //�����Ϸ���������ײ
{
public:
	vec2<float> pos;		// λ��
	vec2<float> size;		// ��С
	vec2<float> speed;		// �ٶ�
	vec2<float> acceleration;// ���ٶ�
	bool isWorks = true;	// �Ƿ���Ч

	void Init(HitBox hitbox);

	void Draw();//


	/**
	 * @brief �����κ��߶ε���ײ
	 * @param[in] rect Ҫ���ľ���
	 * @param[in] lineBegin �߶ε����
	 * @param[in] lineEnd �߶ε��յ�
	 * @param[out] collPos �����߶��������ײ��λ��
	 * @param[out] normal �����߶��������ײλ�õķ���
	 * @param[out] coll_time �����߶��������ײ��λ�ã�ռ�����߶γ��ȵİٷֱ�
	 * @return ��ײtrue������ײfalse����Щ��ײ���Ĵ��붼�ο��� @javidx9 ����Ƶ���ǳ���л�� https://www.youtube.com/watch?v=8JJ-4JgR7Dg&t=2828s��
	*/
	static bool CollideRectVsLine(HitBox& rect, vec2<float>& lineBegin, vec2<float>& lineEnd, vec2<float>& collPos, vec2<float>& normal, float& coll_time);

	/**
	 * @brief ����������ε���ײ
	 * @param[in] in �������
	 * @param[in] target Ŀ�����
	 * @param[out] collPos ������ײλ��
	 * @param[out] normal ������ײλ�õķ���
	 * @param[out] coll_time ������ײ��λ�ã�ռ�����߶γ��ȵİٷֱ�
	 * @param[in] dt ֡ʱ����
	 * @return ��ײtrue������ײfalse����Щ��ײ���Ĵ��붼�ο��� @javidx9 ����Ƶ���ǳ���л�� https://www.youtube.com/watch?v=8JJ-4JgR7Dg&t=2828s��
	*/
	static bool CollideRectVsRect(const HitBox& in, const HitBox& target, vec2<float>& collPos, vec2<float>& normal, float& coll_time, const float dt);

	/**
	 * @brief ��������ƶ����ε���ײ
	 * @param in ������Σ��þ���������ײ���Ǹ�
	 * @param target Ŀ����Σ��þ���Ӧ�ò��ܵ���ײ�����˶�
	 * @param collPos ������ײλ��
	 * @param normal ������ײ�ķ�����
	 * @param collTime ������ײ��ʱ��
	 * @param dt ����֡���ʱ��
	 * @return ��ײtrue������ײfalse����Щ��ײ���Ĵ��붼�ο��� @javidx9 ����Ƶ���ǳ���л�� https://www.youtube.com/watch?v=8JJ-4JgR7Dg&t=2828s��
	*/
	static bool CollideRectVsMoveRect(HitBox& in, HitBox& target, vec2<float>& collPos, vec2<float>& normal, float& collTime, const float dt);

	static bool RectVsRect(HitBox& b1, HitBox& b2);

	static bool isShowHitbox;




};

