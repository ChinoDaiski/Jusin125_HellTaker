// MyFromView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyFromView.h"


// CMyFromView

IMPLEMENT_DYNCREATE(CMyFromView, CView)

CMyFromView::CMyFromView()
{

}

CMyFromView::~CMyFromView()
{
}

BEGIN_MESSAGE_MAP(CMyFromView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMyFromView 그리기입니다.

void CMyFromView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CMyFromView 진단입니다.

#ifdef _DEBUG
void CMyFromView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyFromView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyFromView 메시지 처리기입니다.


int CMyFromView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_TabDlg.Create(IDD_MYFORMVIEW, this);
	m_TabDlg.ShowWindow(SW_SHOW);

	return 0;
}


void CMyFromView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_TabDlg.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE|SWP_NOZORDER);
}
