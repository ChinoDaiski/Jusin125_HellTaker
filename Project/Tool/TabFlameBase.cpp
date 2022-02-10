// TabFlameBase.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "TabFlameBase.h"
#include "afxdialogex.h"


// CTabFlameBase 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTabFlameBase, CDialogEx)

CTabFlameBase::CTabFlameBase(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TABFLAMEBASE, pParent)
{

}

CTabFlameBase::~CTabFlameBase()
{
}

void CTabFlameBase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabFlameBase, CDialogEx)
END_MESSAGE_MAP()


// CTabFlameBase 메시지 처리기입니다.
