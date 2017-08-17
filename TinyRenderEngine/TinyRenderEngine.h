#ifndef TINYRENDERENGINE_H
#define TINYRENDERENGINE_H

#include "TinyRenderInterface.h"
#include "camera.h"
#include "MeshData.h"
#include "TextureControl.h"
class CTinyRenderEngine : public CRenderInterface
{
public:
	CTinyRenderEngine(void);
	
	virtual BOOL InitialRenderEngine(int w, int h, HWND mainWin, UGP_MS_TYPE ms);
	// �ر�����
	virtual BOOL UnitialRenderEngine();
	// ���ú�̨������ɫ
	virtual void SetClearColor(float r, float g, float b);
	// ������Ⱦ
	virtual void StartRender(BOOL bColor, BOOL bDepth, BOOL bStencil);
	// ��Ⱦ
	virtual void Render(int nID /* = -1 */);
	// ������
	virtual void ClearBuffers(BOOL bColor, BOOL bDepth, BOOL bStencil);
	// ������Ⱦ
	virtual void EndRendering();
	// ����ģ��
	virtual void CreateMesh(int &nID);
	// ��������3D
	virtual void CreateVertex(int nID, void* pVertex, int nCount, int nType);
	// ��������
	virtual void CreateIndice(int nID, DWORD* pIndice, int nCount);

	virtual void CreateModuleFromSystem(int nID, void* pParam, MESH_TYPE nType);
	// ���ù���
	virtual void SetLight(SNxVEC3 dir, LIGHT_TYPE nType, int r, int g, int b);

	// ��������
	virtual void CreateTexture(int nID, TCHAR* pFileName);
	// 
	virtual void SetMaterial(int nID, int r, int g, int b);
	// 
	virtual void GetCamera(float &x, float &y, float &z);

	virtual void SetCamera(float x, float y, float z);

	virtual void SetProjMatrix(float w, float h);
private:
	HWND				m_hMainWnd;
	D3DCOLOR			m_Color;
	LPDIRECT3D9			m_pDirect3D;
	LPDIRECT3DDEVICE9	m_pDevice;
	BOOL				m_bRenderingScene;
	// ���
	int					m_screenWidth;
	int					m_screenHeight;
	// ���������
	Camera				m_camera;
	// ����ģ�͹���
	CMeshData*			m_MeshData;

	int					m_nMeshCount;
	// �������
	CTextureControl		m_TextureControl;
};

#endif