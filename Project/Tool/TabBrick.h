#pragma once


// CTabBrick ��ȭ �����Դϴ�.

class CTabBrick : public CDialogEx
{
	DECLARE_DYNAMIC(CTabBrick)

public:
	CTabBrick(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabBrick();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABBRICK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
