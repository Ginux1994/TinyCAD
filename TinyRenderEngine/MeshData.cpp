#include "stdafx.h"
#include "MeshData.h"

static const DWORD dwFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
static const DWORD dwFVF2D = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;

CMeshData::CMeshData()
{
	m_nVertexCount = 0;
	m_nPrimitiveCount = 0;
	m_nSubsetCount = 0;

	m_pJVertexBuffer = NULL;
	m_pJIndexBuffer = NULL;
	m_pTextrue = NULL;
}

CMeshData::~CMeshData()
{
}
BOOL CMeshData::CreateMeshData(IDirect3DDevice9* pDevice, void *pParam, MESH_TYPE nType)
{
	ASSERT(pDevice);
	ASSERT(pParam);

	m_nVertexType = VERTEX_3D;

	switch (nType)
	{
		case MeshBuild_Sphere:
		{
			STMeshBuild_Sphere* pSphere = (STMeshBuild_Sphere*)pParam;
			HRESULT hr = D3DXCreateSphere(pDevice, pSphere->_Radius,
				(int)pSphere->_Radius, (int)pSphere->_Radius, &m_pMesh, NULL);
			//ASSERT(FAILED());
			// 确定位置
			m_fX = pSphere->_x;
			m_fY = pSphere->_y;
			m_fZ = pSphere->_z;

			m_bSystem = TRUE;
			break;
		}
		case MeshBuild_Cube:
		{
			break;
		}
		case MeshBuild_Torus:
		{
			break;
		}
		case MeshBuild_Cylinder:
		{
			break;
		}
		default:
			break;
	}
	return TRUE;
}
BOOL CMeshData::CreateMeshData(IDirect3DDevice9* pDevice, void* pVertex, int nVertexNum, int nType)
{
	HRESULT hr = S_OK;
	ASSERT(pDevice);
	VOID* ptr = NULL;
	if (nType == VERTEX_2D)
	{
		hr = pDevice->CreateVertexBuffer(nVertexNum*sizeof(SNxVertex2D),
			D3DUSAGE_WRITEONLY, dwFVF2D, D3DPOOL_DEFAULT, &m_pJVertexBuffer, NULL);

		m_pJVertexBuffer->Lock(0, 0, &ptr, 0);
		memcpy_s(ptr, nVertexNum*sizeof(SNxVertex2D),
			pVertex, sizeof(SNxVertex2D)*nVertexNum);
		m_pJVertexBuffer->Unlock();

		m_nVertexType = VERTEX_2D;
	}
	else if (nType == VERTEX_3D)
	{
		hr = pDevice->CreateVertexBuffer(nVertexNum*sizeof(SNxVertex),
			D3DUSAGE_WRITEONLY, dwFVF, D3DPOOL_DEFAULT, &m_pJVertexBuffer, NULL);

		m_pJVertexBuffer->Lock(0, 0, &ptr, 0);
		memcpy_s(ptr, nVertexNum*sizeof(SNxVertex),
			pVertex, sizeof(SNxVertex)*nVertexNum);
		m_pJVertexBuffer->Unlock();

		m_nVertexType = VERTEX_2D;
	}
	else
	{
		ASSERT(FALSE);
	}
	ASSERT(SUCCEEDED(hr));

	// 更新顶点数
	m_nVertexCount = nVertexNum;
	m_nPrimitiveCount = m_nVertexCount / 3;
	m_bSystem = FALSE;
	return TRUE;
}
BOOL CMeshData::CreateMeshIndex(IDirect3DDevice9* pDevice, DWORD* pIndex, int nIndexNum, int nPrimtiveCount)
{
	HRESULT hr = S_OK;
	ASSERT(pDevice);
	hr = pDevice->CreateIndexBuffer(sizeof(UINT)*nIndexNum, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
		D3DPOOL_DEFAULT, &m_pJIndexBuffer, NULL);
	ASSERT(SUCCEEDED(hr));
	VOID* ptr = NULL;
	hr = m_pJIndexBuffer->Lock(0, 0, &ptr, 0);
	ASSERT(SUCCEEDED(hr)); 
	memcpy_s(ptr, sizeof(UINT)*nIndexNum, pIndex, sizeof(UINT)*nIndexNum);
	hr = m_pJIndexBuffer->Unlock();
	ASSERT(SUCCEEDED(hr));
	// 设置三角片的数量
	m_nPrimitiveCount = nPrimtiveCount;
	return TRUE;
}

BOOL CMeshData::DrawMeshSystem(IDirect3DDevice9* pDevice)
{
	ASSERT(pDevice);
	ASSERT(m_pMesh);
	HRESULT hr = S_OK;
	// 空间变换
	//pDevice->SetFVF(dwFVF);
	D3DXMATRIX ObjWorldMatrices;
	D3DXMatrixTranslation(&ObjWorldMatrices, m_fX, m_fY, m_fZ);
	hr = pDevice->SetTransform(D3DTS_WORLD, &ObjWorldMatrices);
	ASSERT(SUCCEEDED(hr));
	hr = pDevice->SetMaterial(&m_mtrl);
	ASSERT(SUCCEEDED(hr));
	hr = m_pMesh->DrawSubset(0);
	ASSERT(SUCCEEDED(hr));
	return TRUE;
}
BOOL CMeshData::DrawMesh(IDirect3DDevice9* pDevice, int nPrimitiveStart /* = 0 */, int nPrimitiveCount /* = -1 */)
{
	if (m_pJVertexBuffer == NULL) return TRUE;

	// 当nPrimitiveCount为-1时, 绘制从nPrimitiveStart到m_nPrimitiveCount的所有3三角片
	if (nPrimitiveCount == -1)
		nPrimitiveCount = m_nPrimitiveCount - nPrimitiveStart;

	//
	HRESULT hr = S_OK;
	
	if (m_nVertexType == VERTEX_2D)
	{
		hr = pDevice->SetStreamSource(0, m_pJVertexBuffer, 0, sizeof(SNxVertex2D)); // When using FVF code, only 1 stream can be set
		ASSERT(SUCCEEDED(hr));
		hr = pDevice->SetFVF(dwFVF2D);
	}
	else
	{
		hr = pDevice->SetStreamSource(0, m_pJVertexBuffer, 0, sizeof(SNxVertex)); // When using FVF code, only 1 stream can be set
		ASSERT(SUCCEEDED(hr));
		hr = pDevice->SetFVF(dwFVF);
	}
	ASSERT(SUCCEEDED(hr));
	pDevice->SetMaterial(&m_mtrl);
	ASSERT(SUCCEEDED(hr));
	if (m_pTextrue)
	{
		ASSERT(SUCCEEDED(pDevice->SetTexture(0, m_pTextrue)));
	}
	if (m_pJIndexBuffer != NULL)	// Draw with indexing
	{
		hr = pDevice->SetIndices(m_pJIndexBuffer);
		ASSERT(SUCCEEDED(hr));
		hr = pDevice->DrawIndexedPrimitive(m_ePrimitiveType, 0, 0, m_nVertexCount,
			nPrimitiveStart * 3, nPrimitiveCount);
	}
	else // Draw withOUT indexing
	{
		hr = pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, nPrimitiveStart * 3, nPrimitiveCount);
	}
	ASSERT(SUCCEEDED(hr));

	return SUCCEEDED(hr);
}
BOOL CMeshData::DrawSubset(IDirect3DDevice9* pDevice, int nSubsetIdx)
{
	if (nSubsetIdx < 0 || (UINT)nSubsetIdx >= m_nSubsetCount)
		return FALSE;

	if (m_paMeshSubset[nSubsetIdx].nPrimitiveStart + m_paMeshSubset[nSubsetIdx].nPrimitiveCount >(int)m_nPrimitiveCount)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	return DrawMesh(pDevice, m_paMeshSubset[nSubsetIdx].nPrimitiveStart, m_paMeshSubset[nSubsetIdx].nPrimitiveCount);
}

BOOL CMeshData::CreateTextureFromFile(IDirect3DDevice9* pDevice, TCHAR* pFileName)
{
	ASSERT(pDevice);
	ASSERT(pFileName);

	HRESULT hr = S_OK;
	D3DCOLOR colorkey = 0xff000000;
	D3DXIMAGE_INFO info;

	hr = D3DXCreateTextureFromFileEx(pDevice, pFileName, 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
		colorkey, &info, NULL, &m_pTextrue);

	ASSERT(SUCCEEDED(hr));
	m_pTextrue->SetAutoGenFilterType(D3DTEXF_LINEAR);
	m_pTextrue->GenerateMipSubLevels();

	return TRUE;
}