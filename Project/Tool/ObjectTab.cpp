// ObjectTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "ObjectTab.h"
#include "afxdialogex.h"


// CObjectTab ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CObjectTab, CDialogEx)

CObjectTab::CObjectTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OBJECTTAB, pParent)
{

}

CObjectTab::~CObjectTab()
{
}

void CObjectTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CObjectTab, CDialogEx)
	ON_BN_CLICKED(IDOK, &CObjectTab::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CObjectTab::OnBnClickedCancel)
END_MESSAGE_MAP()


// CObjectTab �޽��� ó�����Դϴ�.


void CObjectTab::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnOK();
}


void CObjectTab::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnCancel();
}
