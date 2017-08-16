
// TinyCADView.cpp : CTinyCADView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "TinyCAD.h"
#endif
#include "MainFrm.h"
#include "TinyCADDoc.h"
#include "TinyCADView.h"
#include "SphereChreateDlg.h"
#include "MeshBuild_Sphere.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTinyCADView

IMPLEMENT_DYNCREATE(CTinyCADView, CView)

BEGIN_MESSAGE_MAP(CTinyCADView, CView)
	// 标准打印命令
	ON_WM_MOUSEWHEEL()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTinyCADView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CREATE_SPHERE, &CTinyCADView::OnCreateSphere)
END_MESSAGE_MAP()

// CTinyCADView 构造/析构

CTinyCADView::CTinyCADView()
{
	CreateEngineObj(&m_pRender);
	ASSERT(m_pRender);
}

CTinyCADView::~CTinyCADView()
{
	ASSERT(m_pRender);
	m_pRender->UnitialRenderEngine();
	delete m_pRender;
	m_pRender = NULL;
}

BOOL CTinyCADView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	

	return CView::PreCreateWindow(cs);
}
void CTinyCADView::OnSize(UINT nType, int cx, int cy)
{
	m_pRender->SetCamera(0, 0, -(float)cy);
	m_pRender->SetProjMatrix(cx, cy);

	__super::OnSize(nType, cx, cy);
}
void CTinyCADView::OnPaint()
{
	ASSERT(m_pRender);
	m_pRender->StartRender(1, 1, 0);
	m_pRender->Render();
	m_pRender->EndRendering();
}
// CTinyCADView 绘制

void CTinyCADView::OnDraw(CDC* /*pDC*/)
{
	CTinyCADDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码

}

void CTinyCADView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	GetDataFromFile();
	ASSERT(m_pRender);
	HWND hWnd = GetSafeHwnd();
	CRect rc;
	GetClientRect(rc);
	m_pRender->InitialRenderEngine(rc.Width(), rc.Height(), hWnd, UGP_MS_SAMPLES_4);
	m_pRender->SetClearColor(0, 0, 0);
	// 设置灯光
	m_pRender->SetLight(SNxVEC3(1.0f, 1.0f, 1.0f), LIGHT_DIRECTIONAL, 255,255,255);
}
// CTinyCADView 打印


void CTinyCADView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTinyCADView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTinyCADView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CTinyCADView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}

void CTinyCADView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTinyCADView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTinyCADView 诊断

#ifdef _DEBUG
void CTinyCADView::AssertValid() const
{
	CView::AssertValid();
}

void CTinyCADView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTinyCADDoc* CTinyCADView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTinyCADDoc)));
	return (CTinyCADDoc*)m_pDocument;
}
#endif //_DEBUG


// CTinyCADView 消息处理程序

BOOL CTinyCADView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	ASSERT(m_pRender);
	float fScale = zDelta*10 / 120;
	float x = 0, y = 0, z = 0;
	m_pRender->GetCamera(x, y, z);
	z += fScale;
	m_pRender->SetCamera(0, 0, z);

	return __super::OnMouseWheel(nFlags, zDelta, pt);
}

void CTinyCADView::OnCreateSphere()
{
	//ASSERT(m_pShpere);
	CSphereChreateDlg dlg;
	int nRet = dlg.DoModal();

	STMeshBuild_Sphere* pParam = (STMeshBuild_Sphere*)nRet;
	//STMeshBuild_Sphere stParam(0, 0, 0, 100);
	IMoudle* pMoudle = new CMeshBuild_Sphere;
	ASSERT(m_pRender);

	int nID = -1;

	m_pRender->CreateMesh(nID);
	m_pRender->CreateModuleFromSystem(nID, (void*)pParam, MeshBuild_Sphere);
	//// 设定材质
	m_pRender->SetMaterial(nID, 153, 153, 153);

	pMoudle->m_nID = nID;
	pMoudle->CreateModule(&pParam);
	SNxCTreeNode* pNode = new SNxCTreeNode;
	pNode->pData = pMoudle;
	// 更新零件树
	CMainFrame *pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	ASSERT(pMainFrame);
	pMainFrame->m_wndFileView.m_ComponentTree.AddNextNode(pNode);
	// 更新列表
	pMainFrame->m_wndFileView.UpdateComponentTree();
	//((CMainFrame*)(AfxGetMainWnd()))->m_wndFileView.m_ComponentTree.AddNextNode(pNode);
	//m_pShpere->CreateModule((void*)&stParam);
}

void CTinyCADView::GetDataFromFile()
{
	// initialize python
	Py_Initialize();
	if (!Py_IsInitialized())
	{
		return;
	}
	//load py script filename  
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('.//')");

	PyObject *pName = PyString_FromString("mapinfo");
	PyObject *pModule = PyImport_Import(pName);
	if (!pModule){
		return;
	}
	//Py_DECREF(pName);
	//PyObject *pDict = PyModule_GetDict(pModule);
	//if (!pDict) return;
	//Py_DECREF(pModule);
	//find function name 
	PyObject* pFunc = PyObject_GetAttrString(pModule, "mapinfo");
	//PyObject *pFunc = PyDict_GetItemString(pDict, "test");
	if (!pFunc || !PyCallable_Check(pFunc)){
		//printf("cant find function [add]");
		//getchar();
		return;
	}
	//Py_DECREF(pDict);
	//call python function  
	PyObject *pRetVal = PyObject_CallObject(pFunc, NULL);
	if (pRetVal == NULL){
		//printf("CalllObject return NULL");
		return;
	}
	Py_DECREF(pFunc);
	int list_len = PyObject_Size(pRetVal);
	PyObject *list_item = NULL;
	for (int i = 0; i < list_len; i++)
	{
		list_item = PyList_GetItem(pRetVal, i);
		PyObject* pItem = NULL;
		char* pName = NULL;
		int nValue = 0;
		for (int j = 0; j<PyObject_Size(list_item); j++)
		{
			pItem = PyList_GetItem(list_item, j);
			if (j==0)
			{
				pName = PyString_AsString(pItem);
			}
			else if (j==1)
			{
				float x = 0;
				PyObject* pX = NULL;
				for (int k = 0; k < PyObject_Size(pItem); k++)
				{
					pX = PyList_GetItem(pItem, k);
					x = PyFloat_AsDouble(pX);
				}
				Py_DECREF(pX);
				//P *ListItem = (PyArrayObject *)PyList_GetItem(FuncOneBack, Index_i)
			}
			else
			{
				nValue = PyInt_AsLong(pItem);
			}
			
		}
		Py_DECREF(pItem);
	}
	Py_DECREF(pRetVal);
	Py_DECREF(list_item);
	Py_Finalize();
}