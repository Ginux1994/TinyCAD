/************************************************************************/
/* Render engine interface                                                
/************************************************************************/
#ifndef TINYRENDERINTERFACE_H
#define TINYRENDERINTERFACE_H

#ifdef TINYRENDERENGINE_EXPORTS
#define TINYRENDERENGINE_API __declspec(dllexport)
#else
#define TINYRENDERENGINE_API __declspec(dllimport)
#endif

#include "defines.h"
#include "structs.h"

class CRenderInterface
{
public:
	// 初始化引擎
	virtual BOOL InitialRenderEngine(int w, int h, HWND mainWin, UGP_MS_TYPE ms) = 0;
	// 关闭引擎
	virtual BOOL UnitialRenderEngine() = 0;
	// 设置后台缓存颜色
	virtual void SetClearColor(float r, float g, float b) = 0;
	// 启动渲染
	virtual void StartRender(BOOL bColor, BOOL bDepth, BOOL bStencil) = 0;
	// 渲染
	virtual void Render(int nID = -1) = 0;
	// 清理缓存
	virtual void ClearBuffers(BOOL bColor, BOOL bDepth, BOOL bStencil) = 0;
	// 结束渲染
	virtual void EndRendering() = 0;
	// 创建一个网格
	virtual void CreateMesh(int &nID) = 0;
	// 设置顶点
	virtual void CreateVertex(int nID, SNxVertex* pVertex, int nCount) = 0;
	// 创建索引
	virtual void CreateIndice(int nID, DWORD* pIndice, int nCount) = 0;

	// 通过D3D内置函数直接创建模型
	virtual void CreateModuleFromSystem(int nID, void* pParam, MESH_TYPE nType) = 0;

	// 设置光照
	virtual void SetLight(SNxVEC3 dir, LIGHT_TYPE nType, int r, int g, int b) = 0;

	// 设置材质
	virtual void SetMaterial(int nID, int r, int g, int b) = 0;
	// 设置相机位置
	virtual void GetCamera(float &x, float &y, float &z) = 0;
	virtual void SetCamera(float x, float y, float z) = 0;
	//// 计算投影矩阵
	virtual void SetProjMatrix(float w, float h) = 0;
	//// 计算正交矩阵
	//virtual void CalculateOrthoMatrix(float n, float f) = 0;

};

TINYRENDERENGINE_API VOID CreateEngineObj(CRenderInterface** pRender);
#endif