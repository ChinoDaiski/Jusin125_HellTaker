// TabCharacter.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "TabCharacter.h"
#include "afxdialogex.h"


// CTabCharacter ��ȭ �����Դϴ�.

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


// CTabCharacter �޽��� ó�����Դϴ�.
