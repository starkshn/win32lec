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

const double _amp = 150; // ����
const double _sp = 300; // ���ǵ�

void Object::Patrol_Vetical_Horizaon_Sin()
{
	auto pos = GetPos();
	pos.x += GetSpeed() * GetDir().x * DT;
	float dis = abs(GetPatrolCenterPos().x - pos.x) - GetPatrolDistance();

	// y axis -> sin
	SetAngle(GetAngle() + DT * _sp);
	pos.y = (-1 * sin(RAD(GetAngle())) * _amp) + GetPatrolCenterPos().y;

	// x�� ������ȯ��
	if (0.f < dis)
	{
		SetDir(GetDir() * -1);
		pos.x += dis * GetDir().x;
	}

	// 60�й� ������ 360���� �Ѵ°��
	if (GetAngle() > 360)
	{
		auto dis = GetAngle() - 360;
		SetAngle(GetAngle() - dis);
		SetAngle(0);
	}

	SetPos(pos);
}
