#include "pch.h"
#include "ResourceManager.h"
#include "Resources.h"
#include "Texture.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	for_each
	(
		_resources.begin(), _resources.end(),
		[&](std::pair<wstring, Resources*>pair)
		{
			if (pair.second != nullptr)
			{
				delete pair.second;
				pair.second = nullptr;
			}
		}
	);
}

void ResourceManager::Init()
{

}

void ResourceManager::Update()
{

}

Resources* ResourceManager::LoadTexture(const wstring& key, const wstring& path)
{
	auto tex = CheckResource(key);
	if (tex) return tex;
	
	wstring filePath = PATH->GetContentDirPath();
	filePath += path;

	tex = static_cast<Resources*>(new Texture());

	tex->LoadResource(FILE_TYPE::BITMAP ,RESOURCE_TYPE::TEXTURE, filePath);

	tex->SetResKey(key);
	tex->SetResRelativePath(filePath);

	_resources.insert(make_pair(key, tex));

	return tex;
}

Resources* ResourceManager::CheckResource(const wstring& key)
{
	auto iter = _resources.find(key);
	if (iter == _resources.end())
	{
		return nullptr;
	}
	else 
	{
		return iter->second;
	}
}
