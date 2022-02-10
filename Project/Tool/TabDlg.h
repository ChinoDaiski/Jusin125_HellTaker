#pragma once
#include "afxcmn.h"

// CTabDlg 대화 상자입니다.
class CTabCharacter;
class CTabObject;
class CTabBrick;
class CTabFlameBase;

class CTabDlg : public CDialog
{
	DECLARE_DYNAMIC(CTabDlg)

public:
	CTabDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTabDlg();

public:


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORMVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// control
	CTabCtrl m_Tab;

	// value


	// general
	CTabCharacter*	m_pTabCharacter;
	CTabObject*		m_pTabObject;
	CTabBrick*		m_pTabBrick;
	CTabFlameBase*	m_pTabFlameBase;


	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);

public:
	afx_msg void OnDestroy();

};
