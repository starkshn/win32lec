#include "pch.h"
#include "PathManager.h"

PathManager::PathManager()
{

}

PathManager::~PathManager()
{

}

void PathManager::Init()
{
	// 현재 경로 띄워준다.
	GetCurrentDirectory(255, _contentDirPath);
	
	size_t len = wcslen(_contentDirPath);

#ifdef _DEBUG												
	for (size_t i = len - 1; i >= 0; --i)	
	{
		if (_contentDirPath[i] == '\\')					
		{												
			_contentDirPath[i] = '\0';					
			break;										
		}												
	}													
#else														
	int cnt = 0;										
	for (size_t i = len - 1; i >= 0; --i)
	{													
		if (cnt == 0 && _contentDirPath[i] == '\\')		
		{												
			++cnt;										
		}												
		else if (cnt == 1 && _contentDirPath[i] == '\\'	
		{												
			_contentDirPath[i] = '\0';					
			break;										
		}												
	}													
#endif

	wcscat_s(_contentDirPath, 255, L"\\bin\\content\\");
}

void PathManager::Update()
{
	// temp
	/*wchar_t buffer[255] = {};
	swprintf_s(buffer, L"Path : %s", _contentDirPath);
	SetWindowText(GET_WINDOW_HANDLE(), buffer);*/
}
