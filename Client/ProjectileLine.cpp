#include "pch.h"
#include "ProjectileLine.h"

void ProjectileLine::Update()
{
	if (GET_KEY_STATE(KEYES::W) == KEY_STATE::HOLD)
	{
		float angle = GetAngle();
		SetAngle(GetAngle() + GetRotateSpeed() * DT_F);

		/*if (GetAngle() > 360.f)
		{
			float tmp = GetAngle() - 360.f;
			SetAngle(GetAngle() - tmp);
			SetAngle(0.f);
		}

		float valX = float(cos(RAD(GetAngle()))) * GetLenght();
		float valY = float(sin(RAD(GetAngle()))) * GetLenght() * -1;

		Vec2 centerPos = GetCenterPos();
		SetEndPos(Vec2(centerPos.x + valX, centerPos.y + valY));*/

		
		float x = GetEndPos().x * float(cos(RAD(GetAngle()))) - GetEndPos().y * float(sin(RAD(GetAngle())));
		float y = GetEndPos().x * float(sin(RAD(GetAngle()))) + GetEndPos().y * float(cos(RAD(GetAngle())));
		SetEndPos(Vec2(x, y));


	}

	/*if (GET_KEY_STATE(KEYES::S) == KEY_STATE::HOLD)
	{
		SetAngle(GetAngle() + GetRotateSpeed() * DT_F * -1);
		if (GetAngle() < -360.f)
		{
			float tmp = GetAngle() + 360.f;
			SetAngle(GetAngle() + tmp);
			SetAngle(0.f);
		}

		float valX = float(cos(RAD(GetAngle()))) * GetLenght();
		float valY = float(sin(RAD(GetAngle()))) * GetLenght();

		Vec2 endPos = GetCenterPos();
		SetEndPos(Vec2(endPos.x + valX, endPos.y + valY));
	}*/
}

void ProjectileLine::Render()
{
	MoveToEx(GET_MEMDC(), GetCenterPos().x, GetCenterPos().y, NULL);
	LineTo(GET_MEMDC(), GetEndPos().x, GetEndPos().y);
}

void ProjectileLine::Init()
{
	SetCenterPos(GetOuterScene()->GetPlayer()->GetPos());
	SetLength(100.f);
	SetEndPos(Vec2(GetCenterPos().x + GetLenght(), GetCenterPos().y));
	SetCenterEndPos(GetEndPos());
	SetRotateSpeed(0.1f);
	SetDir(Vec2(1, 0));
}

void ProjectileLine::Begin()
{

}

void ProjectileLine::End()
{

}
