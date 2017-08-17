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
	// �����ļ���
	m_paTexture[nIndex]._pFileName = new TCHAR[nLength+1];
	memset(m_paTexture[nIndex]._pFileName, 0, sizeof(TCHAR)*(nLength + 1));
	memcpy(m_paTexture[nIndex]._pFileName, pFileName, nLength*sizeof(TCHAR));
	// ���ļ���������
	D3DCOLOR colorkey = 0xff000000;
	D3DXIMAGE_INFO info;

	// ���ļ���������ͼ��
	if (D3DXCreateTextureFromFileEx(pDevice, pFileName, 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT,
		D3DX_DEFAULT, colorkey, &info, NULL,
		&m_paTexture[nIndex]._pTexture) != D3D_OK) return FALSE;

	m_paTexture[nIndex]._pTexture->SetAutoGenFilterType(D3DTEXF_LINEAR);
	m_paTexture[nIndex]._pTexture->GenerateMipSubLevels();   // ����mipmaps

	m_paTexture[nIndex]._Width = info.Width;    // �ڶ����б�������ͼ��Ŀ��
	m_paTexture[nIndex]._Height = info.Height;  // �ڶ����б�������ͼ��ĸ߶�


	nID = m_nTextCount;  // ��������ID
	m_nTextCount++;         // ������������

	return TRUE;
}