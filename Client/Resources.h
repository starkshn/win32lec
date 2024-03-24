#pragma once

class Resources
{
public:
	Resources();
	virtual ~Resources();

	friend class ReousceManager;

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

	HDC GetDC()
	{
		return _dc;
	}

	HBITMAP GetBitMap()
	{
		return 	_bitMap;
	}
	
	void LoadResource(const FILE_TYPE ftype, const RES type, const wstring& path);
	void LoadFile(const RES type, const wstring& path);

	const uint32 GetTexWidth() 
	{
		return _bitMapInfo.bmWidth;
	}

	const uint32 GetTexHeight()
	{
		return _bitMapInfo.bmHeight;
	}

private:
	wstring _resKey;			// res key
	wstring _resRelativePath;	// 상대 경로

private:
	HDC		_dc = 0;			// DC
	HBITMAP _bitMap = 0;		// 비트맵

private:
	BITMAP _bitMapInfo;
};

