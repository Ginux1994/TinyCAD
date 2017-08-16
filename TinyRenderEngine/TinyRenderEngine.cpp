// TinyRenderEngine.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "TinyRenderEngine.h"


D3DMULTISAMPLE_TYPE GetD3DMultiSampleType(LPDIRECT3D9 d3d,
	UGP_MS_TYPE ms, D3DDEVTYPE type, D3DFORMAT format, bool fullscreen)
{
	D3DMULTISAMPLE_TYPE t = D3DMULTISAMPLE_NONE;

	if (d3d)
	{
		switch (ms)
		{
		case UGP_MS_NONE:
			t = D3DMULTISAMPLE_NONE;
			break;

		case UGP_MS_SAMPLES_2:
			if (d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
				type, format, !fullscreen, D3DMULTISAMPLE_2_SAMPLES,
				NULL) == D3D_OK) t = D3DMULTISAMPLE_2_SAMPLES;
			break;

		case UGP_MS_SAMPLES_4:
			if (d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
				type, format, !fullscreen, D3DMULTISAMPLE_2_SAMPLES,
				NULL) == D3D_OK) t = D3DMULTISAMPLE_4_SAMPLES;
			break;

		case UGP_MS_SAMPLES_8:
			if (d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
				type, format, !fullscreen, D3DMULTISAMPLE_8_SAMPLES,
				NULL) == D3D_OK) t = D3DMULTISAMPLE_8_SAMPLES;
			break;

		case UGP_MS_SAMPLES_16:
			if (d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
				type, format, !fullscreen, D3DMULTISAMPLE_16_SAMPLES,
				NULL) == D3D_OK) t = D3DMULTISAMPLE_16_SAMPLES;
			break;

		default:
			break;
		}
	}

	return t;
}

CTinyRenderEngine::CTinyRenderEngine()
{
	return;
}

BOOL CTinyRenderEngine::InitialRenderEngine(int w, int h, HWND mainWin, UGP_MS_TYPE ms)
{
	UnitialRenderEngine();

	m_screenWidth = w;
	m_screenHeight = h;

	m_hMainWnd = mainWin;
	if (!m_hMainWnd)
	{
		return FALSE;
	}

	//m_fullScreen = fullScreen;

	D3DDISPLAYMODE mode;
	D3DCAPS9 caps;
	D3DPRESENT_PARAMETERS Params;

	ZeroMemory(&Params, sizeof(Params));

	m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_pDirect3D)
	{
		return FALSE;
	}

	if (FAILED(m_pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode)))
	{
		return FALSE;
	}

	if (FAILED(m_pDirect3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		return FALSE;
	}

	DWORD processing = 0;
	if (caps.VertexProcessingCaps != 0)
	{
		processing = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE;
	}
	else
	{
		processing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	Params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	Params.Windowed = TRUE;
	Params.BackBufferWidth = w;
	Params.BackBufferHeight = h;
	Params.hDeviceWindow = m_hMainWnd;
	Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Params.BackBufferFormat = mode.Format;
	Params.BackBufferCount = 1;
	Params.EnableAutoDepthStencil = TRUE;
	Params.AutoDepthStencilFormat = D3DFMT_D16;
	Params.MultiSampleType = GetD3DMultiSampleType(m_pDirect3D, ms,
		D3DDEVTYPE_HAL, mode.Format, FALSE);

	m_screenWidth = w;
	m_screenHeight = h;

	if (FAILED(m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hMainWnd,
		processing, &Params, &m_pDevice)))
	{
		return FALSE;
	}

	//OneTimeInit();
	// set camera

	SetCamera(0, 0, -(float)h);
	SetProjMatrix((float)w, (float)h);
	//m_pDevice->SetViewport();
	

	return TRUE;
}
BOOL CTinyRenderEngine::UnitialRenderEngine()
{
	STRAND_SAFE_RELEASE(m_pDevice);
	STRAND_SAFE_RELEASE(m_pDirect3D);
	return TRUE;
}

void CTinyRenderEngine::SetClearColor(float r, float g, float b)
{
	m_Color = D3DCOLOR_COLORVALUE(r, g, b, 1.0f);
}

void CTinyRenderEngine::StartRender(BOOL bColor, BOOL bDepth, BOOL bStencil)
{
	if (!m_pDevice) return;

	unsigned int buffers = 0;

	if (bColor)
	{
		buffers |= D3DCLEAR_TARGET;
	}

	if (bDepth)
	{
		buffers |= D3DCLEAR_ZBUFFER;
	}

	if (bStencil)
	{
		buffers |= D3DCLEAR_STENCIL;
	}

	if (FAILED(m_pDevice->Clear(0, NULL, buffers, m_Color, 1, 0)))
	{
		return;
	}

	if (FAILED(m_pDevice->BeginScene()))
	{
		return;
	}

	m_bRenderingScene = TRUE;
}

void CTinyRenderEngine::Render(int nID)
{
	//ASSERT((nID >= m_nMeshCount || nID < -1));
	// 渲染所有Mesh
	if (nID == -1)
	{
		for (int i = 0; i < m_nMeshCount; i++)
		{
			if (m_MeshData[i].IsSystem())
			{
				m_MeshData[i].DrawMeshSystem(m_pDevice);
			}
			else
			{
				m_MeshData[i].DrawMesh(m_pDevice);
			}
			
		}
	}
	else
	{
		ASSERT( (nID < m_nMeshCount) );
		if (m_MeshData[nID].IsSystem())
		{
			m_MeshData[nID].DrawMeshSystem(m_pDevice);
		}
		else
		{
			m_MeshData[nID].DrawMesh(m_pDevice);
		}
		
	}
}

void CTinyRenderEngine::ClearBuffers(BOOL bColor, BOOL bDepth, BOOL bStencil)
{
	if (!m_pDevice)
	{
		return;
	}

	unsigned int buffers = 0;
	if (bColor)
	{
		buffers |= D3DCLEAR_TARGET;
	}
	if (bDepth)
	{
		buffers |= D3DCLEAR_ZBUFFER;
	}
	if (bStencil)
	{
		buffers |= D3DCLEAR_STENCIL;
	}

	if (m_bRenderingScene)
	{
		m_pDevice->EndScene();
	}

	if (FAILED(m_pDevice->Clear(0, NULL, buffers, m_Color, 1, 0)))
	{
		return;
	}

	if (m_bRenderingScene)
	{
		if (FAILED(m_pDevice->BeginScene()))
		{
			return;
		}
	}
}

void CTinyRenderEngine::EndRendering()
{
	if (!m_pDevice)
	{
		return;
	}

	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, NULL, NULL);

	m_bRenderingScene = FALSE;
}

void CTinyRenderEngine::CreateMesh(int &nID)
{
	static int sID = -1;
	if (m_nMeshCount == 0)
	{
		m_MeshData = new CMeshData[1];
	}
	else
	{
		CMeshData *pTmp = NULL;
		pTmp = new CMeshData[m_nMeshCount+1];
		memcpy_s(pTmp, sizeof(CMeshData)*m_nMeshCount, 
			m_MeshData, sizeof(CMeshData)*m_nMeshCount);
		delete[] m_MeshData;
		m_MeshData = pTmp;
	}
	nID = ++sID;
	m_nMeshCount++;
}
void CTinyRenderEngine::CreateVertex(int nID, SNxVertex* pVertex, int nCount)
{
	ASSERT((nID < m_nMeshCount && nID >= 0));
	// 创建指定的网格模型
	ASSERT(m_MeshData[nID].CreateMeshData(m_pDevice, pVertex, nCount));
}

void CTinyRenderEngine::CreateIndice(int nID, DWORD* pIndice, int nCount)
{
	ASSERT((nID < m_nMeshCount && nID >= 0));
	// 创建指定网格索引
	ASSERT(m_MeshData[nID].CreateMeshIndex(m_pDevice, pIndice, nCount));
}

void CTinyRenderEngine::CreateModuleFromSystem(int nID, void* pParam, MESH_TYPE nType)
{
	ASSERT(pParam);
	ASSERT((nID < m_nMeshCount && nID >= 0));

	m_MeshData[nID].CreateMeshData(m_pDevice, pParam, nType);
}

void CTinyRenderEngine::SetLight(SNxVEC3 dir, LIGHT_TYPE nType, int r, int g, int b)
{
	ASSERT(m_pDevice);
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));
	D3DXVECTOR3 direction(dir._x, dir._y, dir._z);
	D3DXCOLOR d3dcolor = D3DCOLOR_XRGB(r, g, b);
	// 设置光源类型
	switch (nType)
	{
		case LIGHT_POINT:
		{
			light.Type = D3DLIGHT_POINT;
			light.Position = direction;
			break;
		}
		case LIGHT_SPOT:
		{
			light.Type = D3DLIGHT_SPOT;
			break;
		}
		case LIGHT_DIRECTIONAL:
		{
			light.Type = D3DLIGHT_DIRECTIONAL;
			light.Direction = direction;
			break;
		}
		default:
			ASSERT(FALSE);
			break;
	}
	
	light.Ambient = d3dcolor * 0.4f;
	light.Diffuse = d3dcolor;
	light.Specular = d3dcolor * 0.6f;

	m_pDevice->SetLight(0, &light);
	m_pDevice->LightEnable(0, true);

	//
	// Set lighting related render states.
	//

	m_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	m_pDevice->SetRenderState(D3DRS_SPECULARENABLE, false);
}
void CTinyRenderEngine::SetMaterial(int nID, int r, int g, int b)
{
	ASSERT((nID<m_nMeshCount && nID > -1));
	D3DXCOLOR mcolor = D3DCOLOR_XRGB(r, g, b);
	D3DXCOLOR BLACK(D3DCOLOR_XRGB(0, 0, 0));

	D3DMATERIAL9 mtrl;
	mtrl.Ambient = mcolor;
	mtrl.Diffuse = mcolor;
	mtrl.Specular = mcolor;
	mtrl.Emissive = BLACK;
	mtrl.Power = 2.0f;

	m_MeshData[nID].SetMaterial(mtrl);
}
void CTinyRenderEngine::GetCamera(float &x, float &y, float &z)
{
	D3DXVECTOR3 pos;
	m_camera.getPosition(&pos);
	x = pos.x;
	y = pos.y;
	z = pos.z;
}
void CTinyRenderEngine::SetCamera(float x, float y, float z)
{
	if (m_pDevice)
	{
		D3DXVECTOR3 pos(x, y, z);
		m_camera.setPosition(&pos);

		D3DXMATRIX V;
		m_camera.getViewMatrix(&V);

		m_pDevice->SetTransform(D3DTS_VIEW, &V);
	}
	
}

void CTinyRenderEngine::SetProjMatrix(float w, float h)
{
	if (m_pDevice)
	{
		D3DXMATRIX proj;
		D3DXMatrixPerspectiveFovLH(
			&proj,
			D3DX_PI * 0.5f, // 90 - degree
			(float)w / (float)h,
			0.0f,
			1000.0f);
		m_pDevice->SetTransform(D3DTS_PROJECTION, &proj);
	}
	
}