#pragma once
#include "defines.h"
#include "structs.h"

struct SNxMeshSubset
{
	SNxMeshSubset(int nStart = 0, int nCount = 0){ nPrimitiveStart = nStart; nPrimitiveCount = nCount; }
	int nPrimitiveStart;
	int nPrimitiveCount;
	//SNxBoundBox bbox;
};

class CMeshData
{
public:
	CMeshData();
	~CMeshData();
	// ʹ��D3D���õ�������(��Բ����)
	BOOL CreateMeshData(IDirect3DDevice9* pDevice, void* pParam, MESH_TYPE nTye);
	BOOL DrawMeshSystem(IDirect3DDevice9* pDevice);
	// ͨ���Զ��嶥�㴴������
	BOOL CreateMeshData(IDirect3DDevice9* pDevice, void* pVertex, int nVertexNum, int nType);	// ������������
	BOOL CreateMeshIndex(IDirect3DDevice9* pDevice, DWORD* pIndex, int nIndexNum, int nPrimtiveCount = -1);			// ������������
	//BOOL CreateAttriBute(DWORD* dwAttribute, int nAttributeNum);// ������������
	// ����2Dͼ��

	BOOL CreateTextureFromFile(IDirect3DDevice9* pDevice, TCHAR* pFileName);
	// �Զ���
	BOOL DrawMesh(IDirect3DDevice9* pDevice, int nPrimitiveStart = 0, int nPrimitiveCount = -1);
	BOOL DrawSubset(IDirect3DDevice9* pDevice, int nSubsetIdx);
	//void GetSubsetBoundBox(IN CArray<int> & aSubsetIdxs, OUT SNxBoundBox & bbox);
	VOID ClearMesh();
	BOOL IsSystem() { return m_bSystem; };

	void SetMaterial(D3DMATERIAL9 mtrl) { m_mtrl = mtrl; };

private:
	IDirect3DVertexBuffer9*	m_pJVertexBuffer;
	IDirect3DIndexBuffer9*	m_pJIndexBuffer;	// ����ΪNULL, ��m_pJIndexBuffer==NULLʱ, ʹ��DrawPrimitive������Ⱦ

	IDirect3DTexture9* m_pTextrue;				// ����

	UINT				m_nVertexCount;
	UINT				m_nPrimitiveCount;	// ����Ƭ������, ��m_pJIndexBuffer==NULLʱ, Ϊm_nVertexCount/3;
	D3DPRIMITIVETYPE	m_ePrimitiveType;	// Ŀǰֻ֧��D3DPT_TRIANGLELIST��һ��ģʽ
	D3DCULL				m_eCull;

	SNxMeshSubset*		m_paMeshSubset;
	UINT				m_nSubsetCount;

	ID3DXMesh*          m_pMesh;
	BOOL				m_bSystem;

	D3DMATERIAL9		m_mtrl;

	int m_nVertexType;

	float m_fX;
	float m_fY;
	float m_fZ;
	//CArray<SNxMeshSubset> m_aSubsets;
};

