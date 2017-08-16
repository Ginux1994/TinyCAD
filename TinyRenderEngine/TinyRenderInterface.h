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
	// ��ʼ������
	virtual BOOL InitialRenderEngine(int w, int h, HWND mainWin, UGP_MS_TYPE ms) = 0;
	// �ر�����
	virtual BOOL UnitialRenderEngine() = 0;
	// ���ú�̨������ɫ
	virtual void SetClearColor(float r, float g, float b) = 0;
	// ������Ⱦ
	virtual void StartRender(BOOL bColor, BOOL bDepth, BOOL bStencil) = 0;
	// ��Ⱦ
	virtual void Render(int nID = -1) = 0;
	// ������
	virtual void ClearBuffers(BOOL bColor, BOOL bDepth, BOOL bStencil) = 0;
	// ������Ⱦ
	virtual void EndRendering() = 0;
	// ����һ������
	virtual void CreateMesh(int &nID) = 0;
	// ���ö���
	virtual void CreateVertex(int nID, SNxVertex* pVertex, int nCount) = 0;
	// ��������
	virtual void CreateIndice(int nID, DWORD* pIndice, int nCount) = 0;

	// ͨ��D3D���ú���ֱ�Ӵ���ģ��
	virtual void CreateModuleFromSystem(int nID, void* pParam, MESH_TYPE nType) = 0;

	// ���ù���
	virtual void SetLight(SNxVEC3 dir, LIGHT_TYPE nType, int r, int g, int b) = 0;

	// ���ò���
	virtual void SetMaterial(int nID, int r, int g, int b) = 0;
	// �������λ��
	virtual void GetCamera(float &x, float &y, float &z) = 0;
	virtual void SetCamera(float x, float y, float z) = 0;
	//// ����ͶӰ����
	virtual void SetProjMatrix(float w, float h) = 0;
	//// ������������
	//virtual void CalculateOrthoMatrix(float n, float f) = 0;

};

TINYRENDERENGINE_API VOID CreateEngineObj(CRenderInterface** pRender);
#endif