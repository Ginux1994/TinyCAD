/************************************************************************/
/* 定义一个纹理管理器
/************************************************************************/
#pragma once

struct TextureInfo
{
	TextureInfo(){ _pFileName = NULL, _pTexture = NULL,
		_Width = 0, _Height = 0; }
	TCHAR* _pFileName;
	int _Width, _Height;
	IDirect3DTexture9* _pTexture;
};
class CTextureControl
{
public:
	CTextureControl();
	~CTextureControl();

	// 通过文件创建纹理
	BOOL CreateTextureFromFile(int &nID, IDirect3DDevice9* pDevice, TCHAR* pFileName);
	// 自定义创建纹理
	BOOL CreateTexture(IDirect3DDevice9* pDevice) { return TRUE; }
	// 设置纹理过滤
	void SetTextureFilter(int nID, DWORD dwSampler, D3DSAMPLERSTATETYPE nType, DWORD dwValue){};
private:
	// 保存一组纹理
	TextureInfo* m_paTexture;
	// 纹理数量
	int m_nTextCount;
};

