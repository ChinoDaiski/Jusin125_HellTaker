// UnitTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITTOOL, pParent)
	, m_strTest(_T(""))
	, m_strCopy(_T(""))
	, m_strName(_T(""))
	, m_iAttack(0)
	, m_iHp(0)
{

}

CUnitTool::~CUnitTool()
{
	for_each(m_mapUnitData.begin(), m_mapUnitData.end(), CDeleteMap());
	m_mapUnitData.clear();
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	// UpdateData �Լ��� ȣ���� ������ �ڵ����� ȣ��Ǵ� �Լ�

	// UpdateData �Լ��� ���ڰ� TRUE�� ���, ���� ��Ʈ�ѿ��� ������ ���� ��Ī�� ������
	// ���޵ǰ� FALSE�� ��� ���� ������ ����� ���� ��Ī�� ��Ʈ�ѿ� �����ϰ� �ȴ�.

	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strTest);
	DDX_Text(pDX, IDC_EDIT2, m_strCopy);
	DDX_Text(pDX, IDC_EDIT3, m_strName);
	DDX_Text(pDX, IDC_EDIT4, m_iAttack);
	DDX_Text(pDX, IDC_EDIT5, m_iHp);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnAddCharacter)
END_MESSAGE_MAP()


// CUnitTool �޽��� ó�����Դϴ�.


void CUnitTool::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);	// ���� �����Լ�
	// TRUE : ���̾�α� �ڽ��κ��� �Էµ� ������ ����
	m_strCopy = m_strTest;

	// FALSE : ������ ����� ������ ���̾�α� �ڽ��� �ݿ�
	UpdateData(FALSE);
}


void CUnitTool::OnAddCharacter()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	UNITDATA*		pUnit = new UNITDATA;

	pUnit->strName = m_strName;
	pUnit->iAttack = m_iAttack;
	pUnit->iHp = m_iHp;

	// addstring : listbox�� ���ڰ��� �ش��ϴ� ���ڿ��� �����
	m_ListBox.AddString(pUnit->strName);

	m_mapUnitData.emplace(pUnit->strName, pUnit);

	UpdateData(FALSE);
}