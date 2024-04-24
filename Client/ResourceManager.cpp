#include "pch.h"
#include "ResourceManager.h"
#include "Resources.h"
#include "Texture.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	DeleteResourcesSafe(_mapResources);
}

void ResourceManager::Init()
{

}

void ResourceManager::Update()
{

}

Texture* ResourceManager::CreateTexture(const wstring& key, uint32 width, uint32 height)
{
	Texture* tex = FindTexture(key);
	if (tex) return tex;

	tex = new Texture();
	tex->CreateBitmap(width, height);
	tex->SetResKey(key);
	_mapResources.insert(make_pair(key, tex));
	NULL_PTR_CHECK(tex);
	return tex;
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

	_mapResources.insert(make_pair(key, tex));

	return tex;
}

Resources* ResourceManager::CheckResource(const wstring& key)
{
	auto iter = _mapResources.find(key);
	if (iter == _mapResources.end())
	{
		return nullptr;
	}
	else 
	{
		return iter->second;
	}
}

Texture* ResourceManager::GetTexture(const wstring& key, const wstring& fileName)
{
	return static_cast<Texture*>(LoadTexture(key, L"texture\\" + fileName));
}

Texture* ResourceManager::FindTexture(const wstring& key)
{
	auto iter = _mapResources.find(key);
	if (iter == _mapResources.end()) return nullptr;
	else return static_cast<Texture*>((iter->second));
}
