// UnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool 대화 상자입니다.

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
	// UpdateData 함수를 호출할 때마다 자동으로 호출되는 함수

	// UpdateData 함수의 인자가 TRUE인 경우, 현재 컨트롤에서 제어한 값이 매칭된 변수로
	// 전달되고 FALSE인 경우 현재 변수에 저장된 값이 매칭된 컨트롤에 갱신하게 된다.

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


// CUnitTool 메시지 처리기입니다.


void CUnitTool::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);	// 정보 갱신함수
	// TRUE : 다이얼로그 박스로부터 입력된 값들을 얻어옴
	m_strCopy = m_strTest;

	// FALSE : 변수에 저장된 값들을 다이얼로그 박스에 반영
	UpdateData(FALSE);
}


void CUnitTool::OnAddCharacter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	UNITDATA*		pUnit = new UNITDATA;

	pUnit->strName = m_strName;
	pUnit->iAttack = m_iAttack;
	pUnit->iHp = m_iHp;

	// addstring : listbox에 인자값에 해당하는 문자열을 띄워줌
	m_ListBox.AddString(pUnit->strName);

	m_mapUnitData.emplace(pUnit->strName, pUnit);

	UpdateData(FALSE);
}