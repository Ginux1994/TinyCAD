// SphereChreateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TinyCAD.h"
#include "SphereChreateDlg.h"
#include "afxdialogex.h"
#include "MeshBuild_Sphere.h"
#include "NxComponentTree.h"

// CSphereChreateDlg 对话框

IMPLEMENT_DYNAMIC(CSphereChreateDlg, CDialogEx)

CSphereChreateDlg::CSphereChreateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSphereChreateDlg::IDD, pParent)
{

}

CSphereChreateDlg::~CSphereChreateDlg()
{
}

void CSphereChreateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSphereChreateDlg, CDialogEx)
	ON_BN_CLICKED(IDOK2, &CSphereChreateDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSphereChreateDlg 消息处理程序


void CSphereChreateDlg::OnBnClickedOk()
{
	CString strRadius;
	GetDlgItem(IDC_EDT_RADIUS)->GetWindowText(strRadius);
	float fRadius = _ttof(strRadius.GetBuffer());

	m_stSphere._Radius = fRadius;

	CString strPos;
	GetDlgItem(IDC_EDT_POSITION)->GetWindowText(strPos);
	int nStart = 0;
	CString strX = strPos.Tokenize(_T(","), nStart);
	CString strY = strPos.Tokenize(_T(","), nStart);
	CString strZ = strPos.Tokenize(_T(","), nStart);

	m_stSphere._x = _ttof(strX.GetBuffer());
	m_stSphere._y = _ttof(strY.GetBuffer());
	m_stSphere._z = _ttof(strZ.GetBuffer());

	EndDialog((int)(&m_stSphere));
}
