// MapTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTab.h"
#include "afxdialogex.h"


// CMapTab 대화 상자입니다.

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


// CMapTab 메시지 처리기입니다.


void CMapTab::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CMapTab::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnCancel();
}
