#pragma once

class Resources
{
public:
	Resources();
	virtual ~Resources();

public:
	const wstring GetResKey()
	{
		return _resKey;
	}
	void SetResKey(const wstring key)
	{
		_resKey = key;
	}

	const wstring GetResRelativePath()
	{
		return _resRelativePath;
	}
	void SetResRelativePath(const wstring path)
	{
		_resRelativePath = path;
	}

private:
	wstring _resKey;			// res key
	wstring _resRelativePath;	// 상대 경로
	
};

