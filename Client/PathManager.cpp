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
	// ���� ��� ����ش�.
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
		else if (cnt == 1 && _contentDirPath[i] == '\\')
		{												
			_contentDirPath[i] = '\0';					
			break;										
		}												
	}													
#endif

	wcscat_s(_contentDirPath, 255, L"\\Output\\bin\\content\\");
}

void PathManager::Update()
{
	
}

wstring PathManager::GetRelativePathFromAbsolutePath(const WCHAR* path)
{
	wstring tempPath = path;

	// content ���� ������ ���
	size_t contentDirPathLen = wcslen(GetContentDirPath());

	// ���ڷ� �޾ƿ� ���� ���
	size_t fullPathLen = tempPath.length();

	// �߶� ���� ��ġ, �߶� ũ��(����)
	wstring relativePath = tempPath.substr(contentDirPathLen, fullPathLen - contentDirPathLen);

	return relativePath;
}
