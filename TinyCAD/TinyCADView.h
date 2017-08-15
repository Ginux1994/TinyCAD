
// TinyCADView.h : CTinyCADView ��Ľӿ�
//

#pragma once

#include "ModuleInterface.h"

class CTinyCADView : public CView
{
protected: // �������л�����
	CTinyCADView();
	DECLARE_DYNCREATE(CTinyCADView)

// ����
public:
	CTinyCADDoc* GetDocument() const;

// ����
public:
	//IMoudle *m_pShpere;
	CRenderInterface* m_pRender;
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual void OnPaint();
	virtual void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CTinyCADView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCreateSphere();
};

#ifndef _DEBUG  // TinyCADView.cpp �еĵ��԰汾
inline CTinyCADDoc* CTinyCADView::GetDocument() const
   { return reinterpret_cast<CTinyCADDoc*>(m_pDocument); }
#endif

