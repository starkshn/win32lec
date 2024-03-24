#pragma once


class Resources;

class ResourceManager : public Manager
{
	DECLARE_SINGLE(ResourceManager);

public:
	void Init() override;
	void Update() override;

public:
	Resources* LoadTexture(const wstring& key, const wstring& path);
	Resources* CheckResource(const wstring& key);

private:
	map<wstring, Resources*> _resources;
};

