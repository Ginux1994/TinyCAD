
// TinyCADView.cpp : CTinyCADView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "TinyCAD.h"
#endif
#include "MainFrm.h"
#include "TinyCADDoc.h"
#include "TinyCADView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "MeshBuild_Sphere.h"
#include "NxComponentTree.h"
// CTinyCADView

IMPLEMENT_DYNCREATE(CTinyCADView, CView)

BEGIN_MESSAGE_MAP(CTinyCADView, CView)
	// ��׼��ӡ����
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTinyCADView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CREATE_SPHERE, &CTinyCADView::OnCreateSphere)
END_MESSAGE_MAP()

// CTinyCADView ����/����

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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	

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
// CTinyCADView ����

void CTinyCADView::OnDraw(CDC* /*pDC*/)
{
	CTinyCADDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���

}

void CTinyCADView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	ASSERT(m_pRender);
	HWND hWnd = GetSafeHwnd();
	CRect rc;
	GetClientRect(rc);
	m_pRender->InitialRenderEngine(rc.Width(), rc.Height(), hWnd, UGP_MS_SAMPLES_4);
	m_pRender->SetClearColor(0, 0, 0);
	// ���õƹ�
	m_pRender->SetLight(SNxVEC3(1.0f, 1.0f, 1.0f), LIGHT_DIRECTIONAL, 255,255,255);
}
// CTinyCADView ��ӡ


void CTinyCADView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTinyCADView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTinyCADView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTinyCADView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
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


// CTinyCADView ���

#ifdef _DEBUG
void CTinyCADView::AssertValid() const
{
	CView::AssertValid();
}

void CTinyCADView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTinyCADDoc* CTinyCADView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTinyCADDoc)));
	return (CTinyCADDoc*)m_pDocument;
}
#endif //_DEBUG


// CTinyCADView ��Ϣ�������


void CTinyCADView::OnCreateSphere()
{
	//ASSERT(m_pShpere);
	STMeshBuild_Sphere stParam(0,0,0, 100);
	IMoudle* pMoudle = new CMeshBuild_Sphere;
	ASSERT(m_pRender);

	int nID = -1;

	m_pRender->CreateMesh(nID);

	m_pRender->CreateModuleFromSystem(nID, (void*)&stParam, MeshBuild_Sphere);
	// �趨����
	m_pRender->SetMaterial(nID, 153, 153, 153);

	pMoudle->m_nID = nID;
	pMoudle->CreateModule(&stParam);
	SNxCTreeNode* pNode = new SNxCTreeNode;
	pNode->pData = pMoudle;
	// ���������
	CMainFrame *pMainFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	ASSERT(pMainFrame);
	pMainFrame->m_wndFileView.m_ComponentTree.AddNextNode(pNode);
	// �����б�
	pMainFrame->m_wndFileView.UpdateComponentTree();
	//((CMainFrame*)(AfxGetMainWnd()))->m_wndFileView.m_ComponentTree.AddNextNode(pNode);
	//m_pShpere->CreateModule((void*)&stParam);
}
