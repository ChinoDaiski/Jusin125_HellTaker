// MapTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTab.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MyForm.h"
#include "ToolView.h"

#include "ObjMgr.h"

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
	DDX_Control(pDX, IDC_COMBO1, m_MapComboBox);
}


BEGIN_MESSAGE_MAP(CMapTab, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMapTab::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMapTab::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMapTab::OnMapComboBox)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTab::OnSaveButton)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapTab::OnLoadButton)
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


void CMapTab::OnMapComboBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	Invalidate(FALSE);

	UpdateData(FALSE);
}


BOOL CMapTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pBackGround = CObjMgr::GetInstance()->Get_Terrain();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	TCHAR		szFullPath[MAX_PATH] = L"";

	for (int i = 0; i < 8; ++i)
	{
		wsprintf(szFullPath, L"%s%d", L"챕터", i);
		m_MapComboBox.AddString(szFullPath);
	}

	Load_MapPreview();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMapTab::Load_MapPreview()
{
	// 검색할 경로 및 파일
	// 특정 확장자를 갖는 파일을 검색하고 싶으면 '경로/*.jpg' 등으로 사용
	CString tpath = _T("../Texture/BackGround/*.png");

	// 검색 클래스
	CFileFind finder;

	// CFileFind는 파일, 디렉터리가 존재하면 TRUE 를 반환함
	BOOL bWorking = finder.FindFile(tpath);

	CString fileName;
	CString DirName;

	while (bWorking)
	{
		//다음 파일 or 폴더 가 존재하면다면 TRUE 반환
		bWorking = finder.FindNextFile();

		//파일의 이름
		CString _fileName = finder.GetFileName();

		// 현재폴더 상위폴더 썸네일파일은 제외
		if (_fileName == _T("Thumbs.db")) continue;

		fileName = finder.GetFileTitle();

		auto	iter = m_MapPngImage.find(fileName);

		if (iter == m_MapPngImage.end())
		{
			CImage*		pPngImage = new CImage;
			pPngImage->Load(finder.GetFilePath());

			m_MapPngImage.emplace(fileName, pPngImage);
		}
	}
}

void CMapTab::OnSaveButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CFileDialog	Dlg(FALSE,	// true인 경우 열기 모드, false 인 경우 다른 이름으로 저장 모드
		L"dat", // default 파일 확장명, 저장 시 확장자명을 명시해주지 않으면 현재 기입한 확장자명을 사용하게 설정됨
		L"*.dat", // 대화상자에 표시될 최초 파일명
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(읽기전용 체크박스 숨김), OFN_OVERWRITEPROMPT(중복 파일 저장 시 경고메시지 띄우기 옵션)
		L"Data File(*.dat)|*.dat||",	// 대화 상자에 표시될 파일 형식, 콤보박스에 출력될 문자열 | 실제 사용할 필터링 문자열 ||
		this); // 부모 윈도우 주소

	TCHAR	szPath[MAX_PATH] = L"";

	// 현재 프로젝트가 있는 디렉토리 경로를 얻어오는 함수
	GetCurrentDirectory(MAX_PATH, szPath);

	// 전체 경로에서 맨 마지막 경로를 잘라내는 함수
	// 경로 상에 맨 마지막 경로가 파일명이면 그 파일명을 제외한 경로만 남고, 만약 파일명이 없으면 마지막 폴더명을 잘라낸다.
	PathRemoveFileSpec(szPath);

	// data폴더 경로를 이어붙임
	lstrcat(szPath, L"\\Data");

	// 대화상자를 열었을 때 보이는 기본 경로 설정, 절대 경로인 상황
	Dlg.m_ofn.lpstrInitialDir = szPath;

	// DoModal : 대화 상자를 실행, IDOK 실행 성공
	if (IDOK == Dlg.DoModal())
	{
		// GetPathName 선택된 경로를 반환
		CString	strFind = Dlg.GetPathName();
		const TCHAR*	pGetPath = strFind.GetString();

		if (dynamic_cast<CBackGround*>(m_pBackGround)->SaveData())
			return;
	}
}

void CMapTab::OnLoadButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CFileDialog	Dlg(FALSE,	// true인 경우 열기 모드, false 인 경우 다른 이름으로 저장 모드
		L"dat", // default 파일 확장명, 저장 시 확장자명을 명시해주지 않으면 현재 기입한 확장자명을 사용하게 설정됨
		L"*.dat", // 대화상자에 표시될 최초 파일명
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(읽기전용 체크박스 숨김), OFN_OVERWRITEPROMPT(중복 파일 저장 시 경고메시지 띄우기 옵션)
		L"Data File(*.dat)|*.dat||",	// 대화 상자에 표시될 파일 형식, 콤보박스에 출력될 문자열 | 실제 사용할 필터링 문자열 ||
		this); // 부모 윈도우 주소

	TCHAR	szPath[MAX_PATH] = L"";

	// 현재 프로젝트가 있는 디렉토리 경로를 얻어오는 함수
	GetCurrentDirectory(MAX_PATH, szPath);

	// 전체 경로에서 맨 마지막 경로를 잘라내는 함수
	// 경로 상에 맨 마지막 경로가 파일명이면 그 파일명을 제외한 경로만 남고, 만약 파일명이 없으면 마지막 폴더명을 잘라낸다.
	PathRemoveFileSpec(szPath);

	// data폴더 경로를 이어붙임
	lstrcat(szPath, L"\\Data");

	// 대화상자를 열었을 때 보이는 기본 경로 설정, 절대 경로인 상황
	Dlg.m_ofn.lpstrInitialDir = szPath;

	// DoModal : 대화 상자를 실행, IDOK 실행 성공
	if (IDOK == Dlg.DoModal())
	{
		// GetPathName 선택된 경로를 반환
		CString	strFind = Dlg.GetPathName();
		const TCHAR*	pGetPath = strFind.GetString();

		if (dynamic_cast<CBackGround*>(m_pBackGround)->LoadData())
			return;
	}
}