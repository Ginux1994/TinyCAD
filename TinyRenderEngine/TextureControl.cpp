#include "stdafx.h"
#include "defines.h"
#include "TextureControl.h"


CTextureControl::CTextureControl()
{
	m_paTexture = NULL;
}


CTextureControl::~CTextureControl()
{
}

BOOL CTextureControl::CreateTextureFromFile(int &nID, IDirect3DDevice9* pDevice, TCHAR* pFileName)
{
	ASSERT(pFileName);
	int nIndex = m_nTextCount;
	if (!m_paTexture)
	{
		m_paTexture = new TextureInfo[1];
	}
	else
	{
		TextureInfo *temp;
		temp = new TextureInfo[m_nTextCount + 1];

		memcpy(temp, m_paTexture,
			sizeof(TextureInfo) * m_nTextCount);

		delete[] m_paTexture;
		m_paTexture = temp;
	}
	SIZE_T nLength = 0;
	StringCchLength(pFileName, STRSAFE_MAX_CCH, &nLength);
	// 保存文件名
	m_paTexture[nIndex]._pFileName = new TCHAR[nLength+1];
	memset(m_paTexture[nIndex]._pFileName, 0, sizeof(TCHAR)*(nLength + 1));
	memcpy(m_paTexture[nIndex]._pFileName, pFileName, nLength*sizeof(TCHAR));
	// 从文件加载纹理
	D3DCOLOR colorkey = 0xff000000;
	D3DXIMAGE_INFO info;

	// 从文件加载纹理图像
	if (D3DXCreateTextureFromFileEx(pDevice, pFileName, 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT,
		D3DX_DEFAULT, colorkey, &info, NULL,
		&m_paTexture[nIndex]._pTexture) != D3D_OK) return FALSE;

	m_paTexture[nIndex]._pTexture->SetAutoGenFilterType(D3DTEXF_LINEAR);
	m_paTexture[nIndex]._pTexture->GenerateMipSubLevels();   // 生成mipmaps

	m_paTexture[nIndex]._Width = info.Width;    // 在对象中保存纹理图像的宽度
	m_paTexture[nIndex]._Height = info.Height;  // 在对象中保存纹理图像的高度


	nID = m_nTextCount;  // 保存纹理ID
	m_nTextCount++;         // 增加纹理总数

	return TRUE;
}