// MyFromView.cpp : ���� �����Դϴ�.
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


// CMyFromView �׸����Դϴ�.

void CMyFromView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CMyFromView �����Դϴ�.

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


// CMyFromView �޽��� ó�����Դϴ�.


int CMyFromView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	m_TabDlg.Create(IDD_MYFORMVIEW, this);
	m_TabDlg.ShowWindow(SW_SHOW);

	return 0;
}


void CMyFromView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	m_TabDlg.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE|SWP_NOZORDER);
}
