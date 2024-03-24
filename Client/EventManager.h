#pragma once
#include "Manager.h"

typedef struct Event
{
	EVENT_TYPE		_eventType;
	DWORD_PTR		_lParam;
	DWORD_PTR		_rParam;
} EVENT_INFO;

class EventManager : public Manager
{
	DECLARE_SINGLE(EventManager);

public:
	void Init() override;
	void Update() override;

public:
	void Execute(const EVENT_INFO& event);

	void AddEvent(const EVENT_INFO& event)
	{
		_vecEvents.push_back(event);
	}

private:
	vector<EVENT_INFO> _vecEvents;
};

