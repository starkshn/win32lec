#pragma once
#include "Manager.h"
class PathManager : public Manager
{
	DECLARE_SINGLE(PathManager);

public:
	virtual void Init() override;
	virtual void Update() override;

	const WCHAR* GetContentDirPath()
	{
		return _contentDirPath;
	}

	wstring GetRelativePathFromAbsolutePath(const WCHAR* path);

public:
	WCHAR _contentDirPath[256];
	WCHAR _ralativePath[256];
};

//