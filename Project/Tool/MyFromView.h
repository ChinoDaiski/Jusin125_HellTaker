#pragma once

#include "TabDlg.h"
// CMyFromView ���Դϴ�.

class CMyFromView : public CView
{
	DECLARE_DYNCREATE(CMyFromView)

public:
	CMyFromView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyFromView();

public:
	CTabDlg m_TabDlg;

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


