#include "pch.h"
#include "Monster.h"

Monster::Monster()
{

}

Monster::~Monster()
{

}

const double PI = 3.141592;
const double _amp = 100; // ����
const double _sp = 50.f; // ���ǵ�
double angle = 0;
#define RAD(a) a * PI / 180

void Monster::Update()
{
	// x axis patrol
	auto pos = GetPos();
	pos.x += GetSpeed() * GetDir().x * DT;
	float dis = abs(GetPatrolCenterPos().x - pos.x) - GetPatrolDistance();

	// y axis -> sin
	angle += DT * _sp;
	double val = sin(RAD(angle)) * _amp;
	pos.y = (-1 * val) + GetPatrolCenterPos().y;

	// x�� ������ȯ��
	if (0.f < dis)
	{
		SetDir(GetDir() * -1);
		pos.x += dis * GetDir().x;
	}

	// 60�й� ������ 360���� �Ѵ°��
	if (angle > 360)
	{
		angle -= (angle -= 360);
		angle = 0;
	}

	SetPos(pos);
}

void Monster::Render()
{
	Rectangle(GET_MEMDC(), GetLeft(), GetTop(), GetRight(), GetBottom());
}

void Monster::Init()
{
	/*SetSpeed(150.f);
	SetPatrolCenterPos(GetPos());
	SetPatrolDistance(50.f);
	SetDir(Vec2(1, 0));*/
}
