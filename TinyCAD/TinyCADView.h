
// TinyCADView.h : CTinyCADView 类的接口
//

#pragma once

#include "ModuleInterface.h"

class CTinyCADView : public CView
{
protected: // 仅从序列化创建
	CTinyCADView();
	DECLARE_DYNCREATE(CTinyCADView)

// 特性
public:
	CTinyCADDoc* GetDocument() const;

// 操作
public:
	//IMoudle *m_pShpere;
	CRenderInterface* m_pRender;
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual void OnPaint();
	virtual void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CTinyCADView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCreateSphere();
};

#ifndef _DEBUG  // TinyCADView.cpp 中的调试版本
inline CTinyCADDoc* CTinyCADView::GetDocument() const
   { return reinterpret_cast<CTinyCADDoc*>(m_pDocument); }
#endif

