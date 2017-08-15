#include "stdafx.h"
#include "MeshData.h"

static const DWORD dwFVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2;

CMeshData::CMeshData()
{
	m_nVertexCount = 0;
	m_nPrimitiveCount = 0;
	m_nSubsetCount = 0;
}

CMeshData::~CMeshData()
{
}
BOOL CMeshData::CreateMeshData(IDirect3DDevice9* pDevice, void *pParam, MESH_TYPE nType)
{
	ASSERT(pDevice);
	ASSERT(pParam);

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
BOOL CMeshData::CreateMeshData(IDirect3DDevice9* pDevice, SNxVertex* pVertex, int nVertexNum)
{
	HRESULT hr = S_OK;
	ASSERT(pDevice);
	hr = pDevice->CreateVertexBuffer(nVertexNum*sizeof(SNxVertex),
		D3DUSAGE_WRITEONLY, dwFVF, D3DPOOL_DEFAULT, &m_pJVertexBuffer, NULL);
	ASSERT(FAILED(hr));
	VOID* ptr = NULL;
	m_pJVertexBuffer->Lock(0, 0, &ptr, 0);
	memcpy_s(ptr, nVertexNum*sizeof(SNxVertex), 
		pVertex, sizeof(SNxVertex)*nVertexNum);
	m_pJVertexBuffer->Unlock();
	// 更新顶点数
	m_nVertexCount = nVertexNum;
	return TRUE;
}
BOOL CMeshData::CreateMeshIndex(IDirect3DDevice9* pDevice, DWORD* pIndex, int nIndexNum, int nPrimtiveCount)
{
	HRESULT hr = S_OK;
	ASSERT(pDevice);
	hr = pDevice->CreateIndexBuffer(sizeof(UINT)*nIndexNum, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
		D3DPOOL_DEFAULT, &m_pJIndexBuffer, NULL);
	ASSERT(FAILED(hr));
	VOID* ptr = NULL;
	ASSERT(FAILED(m_pJIndexBuffer->Lock(0, 0, &ptr, 0)));
	memcpy_s(ptr, sizeof(UINT)*nIndexNum, pIndex, sizeof(UINT)*nIndexNum);
	ASSERT(FAILED(m_pJIndexBuffer->Unlock()));
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
	hr = pDevice->SetStreamSource(0, m_pJVertexBuffer, 0, sizeof(SNxVertex)); // When using FVF code, only 1 stream can be set
	ASSERT(SUCCEEDED(hr));
	hr = pDevice->SetFVF(dwFVF);
	ASSERT(SUCCEEDED(hr));
	hr = pDevice->SetIndices(m_pJIndexBuffer);
	ASSERT(SUCCEEDED(hr));
	pDevice->SetMaterial(&m_mtrl);
	ASSERT(SUCCEEDED(hr));
	if (m_pJIndexBuffer != NULL)	// Draw with indexing
		hr = pDevice->DrawIndexedPrimitive(m_ePrimitiveType, 0, 0, m_nVertexCount, 
			nPrimitiveStart * 3, nPrimitiveCount);
	else // Draw withOUT indexing
		hr = pDevice->DrawPrimitive(m_ePrimitiveType, nPrimitiveStart * 3, nPrimitiveCount);
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