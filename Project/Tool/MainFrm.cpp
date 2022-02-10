
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "Tool.h"

#include "MainFrm.h"
#include "MyForm.h"
#include "ToolView.h"
#include "MiniView.h"
#include "MyFromView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)

	ON_WM_CREATE()

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	/*if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);*/


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기


//  뷰 객체를 생성하는 시점에 호출(뷰 생성을 막거나 자신만의 뷰를 생성)
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	// CreateStatic : 분할된 창을 만들기 위한 함수(부모 윈도우 주소, 행의 수, 열의 수, 창 스타일, 자식창 ID)
	// CreateView : 분할 창에 표시할 view 창을 생성하는 함수(행, 열, 배치할 view창을 생성한 포인터, 초기 크기, pContext)

	// 01. 우선 창을 좌우 2분할 시킴
	m_MainSplitter.CreateStatic(this, 1, 2);

	// 02. 분할 시킨 창 중 오른쪽 창에 CToolView class를 연동시킴
	m_MainSplitter.CreateView(0, 1, RUNTIME_CLASS(CToolView), CSize(WINCX, WINCY), pContext);

	// 두 번째 분할 윈도우 생성

	// WS_CHILD : 자식 창이라는 의미
	// WS_VISIBLE : 생성 후 바로 화면에 표시하겠는 의미

	// 03. 위 아래로 2분할 시킨 창을 만듦, 분할 시킨 창은 상위 메인 윈도우의 좌측에 연동되게 함.
	m_SecondSplitter.CreateStatic(&m_MainSplitter, 
									2, 
									1, 
									WS_CHILD | WS_VISIBLE, 
									m_MainSplitter.IdFromRowCol(0, 0));

	// 04. 좌측 위 아래로 분할시킨 창의 위쪽 창에 CMiniView를 연동시킴.
	m_SecondSplitter.CreateView(0, 0, RUNTIME_CLASS(CMiniView), CSize(350, 200), pContext);

	// 05. 좌측 위 아래로 분할시킨 창의 아래쪽 창에 CMyFormView를 연동시킴.
	m_SecondSplitter.CreateView(1, 0, RUNTIME_CLASS(CMyFromView), CSize(350, 400), pContext);

	//SetColumnInfo(열 번호, 열의 크기, 허용 가능한 최소 크기)
	m_MainSplitter.SetColumnInfo(0, 300, 10);
	

	return TRUE; //CFrameWnd::OnCreateClient(lpcs, pContext);
}
