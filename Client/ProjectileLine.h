#pragma once
#include "Object.h"
class ProjectileLine : public Object
{
public:
	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;
	virtual void Begin() override;
	virtual void End() override;

	virtual ProjectileLine* Clone() override;

public:
	const Vec2 GetEndPos() { return _endPos; }
	void SetEndPos(Vec2 pos) { _endPos = pos;}

	const Vec2 GetCenterEndPos() { return _centerEndPos; }
	void SetCenterEndPos(Vec2 pos) { _centerEndPos = pos; }

	const float GetLenght() { return _length;}
	void SetLength(const float length) { _length = length; }

private:
	Vec2 _centerEndPos;
	Vec2 _endPos;
	float _length = 20.f;
};

