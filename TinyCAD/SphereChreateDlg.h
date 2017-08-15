#pragma once


// CSphereChreateDlg 对话框

class CSphereChreateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSphereChreateDlg)

public:
	CSphereChreateDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSphereChreateDlg();

	STMeshBuild_Sphere m_stSphere;
// 对话框数据
	enum { IDD = IDD_CREATOR_SPHERE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
