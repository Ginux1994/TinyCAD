#pragma once


// CSphereChreateDlg �Ի���

class CSphereChreateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSphereChreateDlg)

public:
	CSphereChreateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSphereChreateDlg();

	STMeshBuild_Sphere m_stSphere;
// �Ի�������
	enum { IDD = IDD_CREATOR_SPHERE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
