#pragma once
#include "Object.h"

// Create Object Event 등록 함수
void CreateObject(Object* obj, OBJECT_TYPE objType);

// Delete Object Event 등록 함수
void DeleteObject(Object* obj);

// Scene Chagne Event 등록 함수
void ChnageScene_EV(SCENE_TYPE destType);

template <typename T>
void DeleteObjectsSafe(vector<T>& vec)
{
	for (uint32 i = 0; i < vec.size(); ++i)
	{
		if (nullptr != vec[i])
			delete vec[i];
	}
	vec.clear();
}

template <typename T1, typename T2>
void DeleteResourcesSafe(map<T1, T2>& _reMap)
{
	// template 내에서 inner class 사용하려면 typename 명시
	/*typename map<T1, T2>::iterator iter = _reMap.begin();
	for (; iter < _reMap.end(); ++iter)
	{
		if (nullptr != iter->second)
		{
			delete iter->second;
		}
	}
	_rsMap.clear();*/
	
	for_each
	(
		_reMap.begin(), _reMap.end(),
		[&](std::pair<T1, T2>pair)
		{
			if (pair.second != nullptr)
			{
				delete pair.second;
				pair.second = nullptr;
			}
		}
	);
	_reMap.clear();
}