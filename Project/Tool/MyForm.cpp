// MyForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"

// CMyForm

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMyForm::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CMyForm 진단입니다.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm 메시지 처리기입니다.


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CRect rect;
	m_TabCtrl.GetWindowRect(rect);		// 탭 컨트롤 크기 가져옴

	m_TabCtrl.InsertItem(0, TEXT("오브젝트 Tab"));
	m_TabCtrl.InsertItem(1, TEXT("맵 Tab"));

	m_TabCtrl.SetCurSel(0);		// 1번째 탭 표시

	m_pObjectTab = new CObjectTab;
	m_pObjectTab->Create(IDD_OBJECTTAB, &m_TabCtrl);
	m_pObjectTab->MoveWindow(0, 20, rect.Width() - 5, rect.Height() - 5);
	m_pObjectTab->ShowWindow(SW_SHOW);

	m_pMapTab = new CMapTab;
	m_pMapTab->Create(IDD_MAPTAB, &m_TabCtrl);
	m_pMapTab->MoveWindow(0, 20, rect.Width() - 5, rect.Height() - 5);
	m_pMapTab->ShowWindow(SW_HIDE);

}


void CMyForm::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (IDC_TAB1 == pNMHDR->idFrom)
	{
		int iSelect = m_TabCtrl.GetCurSel();

		switch (iSelect)
		{
		case 0:
			m_pObjectTab->ShowWindow(SW_SHOW);
			m_pMapTab->ShowWindow(SW_HIDE);
			break;
		case 1:
			m_pObjectTab->ShowWindow(SW_HIDE);
			m_pMapTab->ShowWindow(SW_SHOW);
			break;
		}
	}

	*pResult = 0;
}
