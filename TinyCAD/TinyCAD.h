
// TinyCAD.h : TinyCAD Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CTinyCADApp:
// �йش����ʵ�֣������ TinyCAD.cpp
//

class CTinyCADApp : public CWinAppEx
{
public:
	CTinyCADApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	CRenderInterface* m_pRender;

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTinyCADApp theApp;
