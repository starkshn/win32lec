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
	Resources* LoadTexture(const wstring& key, const wstring& path);
	Resources* CheckResource(const wstring& key);

public:
	Texture* GetTexture(const wstring& key, const wstring& fileName);

private:
	map<wstring, Resources*> _resources;
};

