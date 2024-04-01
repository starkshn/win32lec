#pragma once
#include "Component.h"

class Object;

class Collider : public Component
{
public:
	Collider();
	virtual ~Collider() override;

	Collider(const Collider& other);

public:
	virtual void Update() override;
	virtual void Render() override;
	virtual void Init() override;

public:
	// ������ ID ����
	const uint32 GetID() { return _id; }
	void SetID(uint32 id) { _id = id; }

public:
	// �浹 �߻� ����
	void OnCollision(Collider* other);		// �浹 ������
	void OnCollisionEnter(Collider* other); // �浹 ���ʷ� ����
	void OnCollisionExit(Collider* other);  // �浹 �������

private:
	static UINT g_nextID;

private:
	UINT		_id				= 0;
	INT			_isCollision	= 0;
};

