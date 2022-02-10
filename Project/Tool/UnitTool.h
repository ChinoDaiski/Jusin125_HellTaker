#pragma once
#include "afxwin.h"

#include "Include.h"

// CUnitTool 대화 상자입니다.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUnitTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
