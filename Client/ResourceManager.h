#pragma once


class Resources;

class ResourceManager : public Manager
{
	DECLARE_SINGLE(ResourceManager);

public:
	void Init() override;
	void Update() override;

public:
	shared_ptr<Resources> LoadTexture(const wstring& key, const wstring& path);
	shared_ptr<Resources> CheckResource(const wstring& key);

private:
	map<wstring, shared_ptr<Resources>> _resources;
};

