#pragma once


// CTabFlameBase ��ȭ �����Դϴ�.

class CTabFlameBase : public CDialogEx
{
	DECLARE_DYNAMIC(CTabFlameBase)

public:
	CTabFlameBase(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabFlameBase();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABFLAMEBASE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
