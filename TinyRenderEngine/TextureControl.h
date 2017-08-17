/************************************************************************/
/* ����һ�����������
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

	// ͨ���ļ���������
	BOOL CreateTextureFromFile(int &nID, IDirect3DDevice9* pDevice, TCHAR* pFileName);
	// �Զ��崴������
	BOOL CreateTexture(IDirect3DDevice9* pDevice) { return TRUE; }
	// �����������
	void SetTextureFilter(int nID, DWORD dwSampler, D3DSAMPLERSTATETYPE nType, DWORD dwValue){};
private:
	// ����һ������
	TextureInfo* m_paTexture;
	// ��������
	int m_nTextCount;
};

