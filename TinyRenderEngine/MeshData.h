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
	// 使用D3D内置的网格功能(球，圆柱等)
	BOOL CreateMeshData(IDirect3DDevice9* pDevice, void* pParam, MESH_TYPE nTye);
	BOOL DrawMeshSystem(IDirect3DDevice9* pDevice);
	// 通过自定义顶点创建网格
	BOOL CreateMeshData(IDirect3DDevice9* pDevice, SNxVertex* pVertex, int nVertexNum);	// 创建顶点数据
	BOOL CreateMeshIndex(IDirect3DDevice9* pDevice, DWORD* pIndex, int nIndexNum, int nPrimtiveCount = -1);			// 创建索引数据
	//BOOL CreateAttriBute(DWORD* dwAttribute, int nAttributeNum);// 创建网格属性
	// 自定义
	BOOL DrawMesh(IDirect3DDevice9* pDevice, int nPrimitiveStart = 0, int nPrimitiveCount = -1);
	BOOL DrawSubset(IDirect3DDevice9* pDevice, int nSubsetIdx);
	//void GetSubsetBoundBox(IN CArray<int> & aSubsetIdxs, OUT SNxBoundBox & bbox);
	VOID ClearMesh();
	BOOL IsSystem() { return m_bSystem; };

	void SetMaterial(D3DMATERIAL9 mtrl) { m_mtrl = mtrl; };
private:
	IDirect3DVertexBuffer9*	m_pJVertexBuffer;
	IDirect3DIndexBuffer9*	m_pJIndexBuffer;	// 可以为NULL, 当m_pJIndexBuffer==NULL时, 使用DrawPrimitive进行渲染

	UINT				m_nVertexCount;
	UINT				m_nPrimitiveCount;	// 三角片的数量, 当m_pJIndexBuffer==NULL时, 为m_nVertexCount/3;
	D3DPRIMITIVETYPE	m_ePrimitiveType;	// 目前只支持D3DPT_TRIANGLELIST这一种模式
	D3DCULL				m_eCull;

	SNxMeshSubset*		m_paMeshSubset;
	UINT				m_nSubsetCount;

	ID3DXMesh*          m_pMesh;
	BOOL				m_bSystem;

	D3DMATERIAL9		m_mtrl;

	float m_fX;
	float m_fY;
	float m_fZ;
	//CArray<SNxMeshSubset> m_aSubsets;
};

