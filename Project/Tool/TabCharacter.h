#pragma once


// CTabCharacter ��ȭ �����Դϴ�.

class CTabCharacter : public CDialogEx
{
	DECLARE_DYNAMIC(CTabCharacter)

public:
	CTabCharacter(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabCharacter();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABCHARACTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
