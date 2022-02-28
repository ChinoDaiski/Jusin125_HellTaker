// ObjectTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "ObjectTab.h"
#include "afxdialogex.h"


// CObjectTab 대화 상자입니다.

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


// CObjectTab 메시지 처리기입니다.


void CObjectTab::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CObjectTab::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnCancel();
}
