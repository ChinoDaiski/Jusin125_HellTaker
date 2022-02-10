// TabCharacter.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "TabCharacter.h"
#include "afxdialogex.h"


// CTabCharacter 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTabCharacter, CDialogEx)

CTabCharacter::CTabCharacter(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TABCHARACTER, pParent)
{

}

CTabCharacter::~CTabCharacter()
{
}

void CTabCharacter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabCharacter, CDialogEx)
END_MESSAGE_MAP()


// CTabCharacter 메시지 처리기입니다.
