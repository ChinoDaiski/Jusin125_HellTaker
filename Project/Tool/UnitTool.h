#pragma once
#include "afxwin.h"

#include "Include.h"

// CUnitTool ��ȭ �����Դϴ�.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnAddCharacter();

public:	
	// value
	CString m_strTest;
	CString m_strCopy;
	CString m_strName;
	int m_iAttack;
	int m_iHp;

	// control
	CListBox m_ListBox;

	// general
	map<CString, UNITDATA*>		m_mapUnitData;
};
