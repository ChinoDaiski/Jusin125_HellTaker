// TabDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "TabDlg.h"
#include "afxdialogex.h"

// CTabDlg 대화 상자입니다.
#include "TabCharacter.h"
#include "TabObject.h"
#include "TabBrick.h"
#include "TabFlameBase.h"

IMPLEMENT_DYNAMIC(CTabDlg, CDialog)

CTabDlg::CTabDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MYFORMVIEW, pParent)
{

}

CTabDlg::~CTabDlg()
{
}

void CTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}


BEGIN_MESSAGE_MAP(CTabDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTabDlg::OnTcnSelchangeTab)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CTabDlg 메시지 처리기입니다.


BOOL CTabDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_Tab.InsertItem(0, _T("Character"));
	m_Tab.InsertItem(1, _T("Object"));
	m_Tab.InsertItem(2, _T("Brick"));
	m_Tab.InsertItem(3, _T("FlameBase"));

	m_Tab.SetCurSel(0);

	CRect rect;
	m_Tab.GetWindowRect(&rect);

	m_pTabCharacter = new CTabCharacter;
	m_pTabCharacter->Create(IDD_TABCHARACTER, &m_Tab);
	m_pTabCharacter->MoveWindow(0, 25, rect.Width(), rect.Height());
	m_pTabCharacter->ShowWindow(SW_SHOW);

	m_pTabObject = new CTabObject;
	m_pTabObject->Create(IDD_TABOBJECT, &m_Tab);
	m_pTabObject->MoveWindow(0, 25, rect.Width(), rect.Height());
	m_pTabObject->ShowWindow(SW_HIDE);

	m_pTabBrick = new CTabBrick;
	m_pTabBrick->Create(IDD_TABBRICK, &m_Tab);
	m_pTabBrick->MoveWindow(0, 25, rect.Width(), rect.Height());
	m_pTabBrick->ShowWindow(SW_HIDE);

	m_pTabFlameBase = new CTabFlameBase;
	m_pTabFlameBase->Create(IDD_TABFLAMEBASE, &m_Tab);
	m_pTabFlameBase->MoveWindow(0, 25, rect.Width(), rect.Height());
	m_pTabFlameBase->ShowWindow(SW_HIDE);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTabDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int sel = m_Tab.GetCurSel();

	switch (sel) {

	case 0:
		m_pTabCharacter->ShowWindow(SW_SHOW);
		m_pTabObject->ShowWindow(SW_HIDE);
		m_pTabBrick->ShowWindow(SW_HIDE);
		m_pTabFlameBase->ShowWindow(SW_HIDE);
		break;

	case 1:
		m_pTabCharacter->ShowWindow(SW_HIDE);
		m_pTabObject->ShowWindow(SW_SHOW);
		m_pTabBrick->ShowWindow(SW_HIDE);
		m_pTabFlameBase->ShowWindow(SW_HIDE);
		break;

	case 2:
		m_pTabCharacter->ShowWindow(SW_HIDE);
		m_pTabObject->ShowWindow(SW_HIDE);
		m_pTabBrick->ShowWindow(SW_SHOW);
		m_pTabFlameBase->ShowWindow(SW_HIDE);
		break;

	case 3:
		m_pTabCharacter->ShowWindow(SW_HIDE);
		m_pTabObject->ShowWindow(SW_HIDE);
		m_pTabBrick->ShowWindow(SW_HIDE);
		m_pTabFlameBase->ShowWindow(SW_SHOW);
		break;
	}

	*pResult = 0;
}


void CTabDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
