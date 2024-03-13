#include "pch.h"
#include "Object.h"

Object::Object()
{

}

Object::~Object()
{

}

void Object::Rotate(double radius)
{
	auto pos = GetPos();
	SetAngle(GetAngle() + GetSpeed() * DT);
	if (GetAngle() > 360)
	{
		SetAngle(GetAngle() - 360);
		SetAngle(0);
	}

	double cosVal = cos(RAD(GetAngle())) * radius;
	double sinVal = sin(RAD(GetAngle())) * radius;
	
	pos.x = GetPatrolCenterPos().x + cosVal;
	pos.y = GetPatrolCenterPos().y + sinVal;
	
	SetPos(pos);
}

const double _amp = 150; // 진폭
const double _sp = 300; // 스피드

void Object::Patrol_Vetical_Horizaon_Sin()
{
	auto pos = GetPos();
	pos.x += GetSpeed() * GetDir().x * DT;
	float dis = abs(GetPatrolCenterPos().x - pos.x) - GetPatrolDistance();

	// y axis -> sin
	SetAngle(GetAngle() + DT * _sp);
	pos.y = (-1 * sin(RAD(GetAngle())) * _amp) + GetPatrolCenterPos().y;

	// x축 방향전환시
	if (0.f < dis)
	{
		SetDir(GetDir() * -1);
		pos.x += dis * GetDir().x;
	}

	// 60분법 각도가 360도를 넘는경우
	if (GetAngle() > 360)
	{
		auto dis = GetAngle() - 360;
		SetAngle(GetAngle() - dis);
		SetAngle(0);
	}

	SetPos(pos);
}
