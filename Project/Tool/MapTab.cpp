// MapTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTab.h"
#include "afxdialogex.h"


// CMapTab ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMapTab, CDialogEx)

CMapTab::CMapTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAPTAB, pParent)
{

}

CMapTab::~CMapTab()
{
}

void CMapTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMapTab, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMapTab::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMapTab::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMapTab �޽��� ó�����Դϴ�.


void CMapTab::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnOK();
}


void CMapTab::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnCancel();
}
