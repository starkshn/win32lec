#pragma once

class Resources;
class Texture;

class ResourceManager : public Manager
{
	DECLARE_SINGLE(ResourceManager);

public:
	void Init() override;
	void Update() override;

public:
	Texture* CreateTexture(const wstring& key, uint32 width, uint32 height);
	Resources* LoadTexture(const wstring& key, const wstring& path);
	Resources* CheckResource(const wstring& key);

public:
	Texture* GetTexture(const wstring& key, const wstring& fileName);
	Texture* FindTexture(const wstring& key);

private:
	map<wstring, Resources*> _mapResources;
};

