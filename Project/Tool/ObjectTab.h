#pragma once


// CObjectTab ��ȭ �����Դϴ�.

class CObjectTab : public CDialogEx
{
	DECLARE_DYNAMIC(CObjectTab)

public:
	CObjectTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CObjectTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTTAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
