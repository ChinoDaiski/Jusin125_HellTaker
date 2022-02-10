// TabBrick.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "TabBrick.h"
#include "afxdialogex.h"


// CTabBrick 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTabBrick, CDialogEx)

CTabBrick::CTabBrick(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TABBRICK, pParent)
{

}

CTabBrick::~CTabBrick()
{
}

void CTabBrick::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabBrick, CDialogEx)
END_MESSAGE_MAP()


// CTabBrick 메시지 처리기입니다.
