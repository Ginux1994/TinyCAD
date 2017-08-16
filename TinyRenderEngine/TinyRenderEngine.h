#ifndef TINYRENDERENGINE_H
#define TINYRENDERENGINE_H

#include "TinyRenderInterface.h"
#include "camera.h"
#include "MeshData.h"

class CTinyRenderEngine : public CRenderInterface
{
public:
	CTinyRenderEngine(void);
	
	virtual BOOL InitialRenderEngine(int w, int h, HWND mainWin, UGP_MS_TYPE ms);
	// 关闭引擎
	virtual BOOL UnitialRenderEngine();
	// 设置后台缓存颜色
	virtual void SetClearColor(float r, float g, float b);
	// 启动渲染
	virtual void StartRender(BOOL bColor, BOOL bDepth, BOOL bStencil);
	// 渲染
	virtual void Render(int nID /* = -1 */);
	// 清理缓存
	virtual void ClearBuffers(BOOL bColor, BOOL bDepth, BOOL bStencil);
	// 结束渲染
	virtual void EndRendering();
	// 创建模型
	virtual void CreateMesh(int &nID);
	// 创建顶点
	virtual void CreateVertex(int nID, SNxVertex* pVertex, int nCount);
	// 创建索引
	virtual void CreateIndice(int nID, DWORD* pIndice, int nCount);

	virtual void CreateModuleFromSystem(int nID, void* pParam, MESH_TYPE nType);
	// 设置光照
	virtual void SetLight(SNxVEC3 dir, LIGHT_TYPE nType, int r, int g, int b);
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
	// 宽高
	int					m_screenWidth;
	int					m_screenHeight;
	// 摄像机
	Camera				m_camera;
	// 网格数据
	CMeshData*			m_MeshData;
	int					m_nMeshCount;
};

#endif