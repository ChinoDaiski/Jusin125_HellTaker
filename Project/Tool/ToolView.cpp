
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "ToolDoc.h"
#include "ToolView.h"

#include "Device.h"
#include "SingleTexture.h"
#include "MainFrm.h"
#include "MyForm.h"

#include "Obj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND	g_hWnd;

// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

CToolView::~CToolView()
{
	// empty
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// SetScrollSizes : 스크롤 바의 사이즈를 지정하는 scrollview 클래스 멤버 함수
	// MM_TEXT : 픽셀단위 크기로 조정하겠다는 의미
	// 두 번째 : 가로, 세로 사이즈

	// SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, TILECY * TILEY / 2));
	SetScrollSizes(MM_TEXT, CSize(0, 0));

	//AfxGetMainWnd : 현재의 메인 윈도우를 반환하는 전역 함수
	// 자식 타입으로 형 변환하여 반환함
	CMainFrame*		pMainFrm = (CMainFrame*)AfxGetMainWnd();

	RECT	rcWnd{};

	// GetWindowRect : 현재 윈도우 창의 렉트 정보를 얻어오는 함수
	pMainFrm->GetWindowRect(&rcWnd);

	// SetRect : 지정한 인자값으로 rect정보를 세팅하는 함수
	// 현재 0,0기준으로 창의 렉트를 조정하고 있는 상황
	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);

	RECT	rcMainView{};
	//GetClientRect : 현재 view 창의 rect 정보를 얻어오는 함수
	GetClientRect(&rcMainView);

	// 프레임과 view창의 가로, 세로 갭을 구한다.
	float	fRowFrm = float(rcWnd.right - rcMainView.right);
	float	fColFrm = float(rcWnd.bottom - rcMainView.bottom);

	// SetWindowPos: 인자값 대로 새롭게 윈도우 위치와 크기를 조정하는 함수
	// 1인자 : 배치할 윈도우의 Z순서에 대한 포인터
	// 2, 3인자 : left, top 좌표
	// 4, 5인자 : 가로, 세로 창 사이즈
	// 6인자 : SWP_NOZORDER : 현재 순서를 유지하겠다는 플래그 값, 만약 null인 경우 순서 변경을 하지 않겠다.

	pMainFrm->SetWindowPos(nullptr, 300, 100, int(WINCX + fRowFrm), int(WINCY + fColFrm), SWP_NOZORDER);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	g_hWnd = m_hWnd;

	if (FAILED(CDevice::GetInstance()->InitDevice()))
		AfxMessageBox(L"Device Create Failed");

	// 백그라운드 생성
	m_pBackGround = new CBackGround;

	if (nullptr != m_pBackGround)
		m_pBackGround->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::TERRAIN, m_pBackGround);

	dynamic_cast<CBackGround*>(m_pBackGround)->Select_Chapter(SEVEN);
}

// CToolView 그리기
void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CDevice::GetInstance()->Render_Begin();

	//Synchro_Scroll();

	m_pBackGround->Update();
	
	m_pBackGround->Render();

	CDevice::GetInstance()->Render_End(g_hWnd);

}

// CToolView 인쇄

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG

// CToolView 메시지 처리기

void CToolView::OnDestroy()
{
	CScrollView::OnDestroy();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CDevice::GetInstance()->DestroyInstance();

}

void CToolView::Synchro_Scroll()
{
	D3DXVECTOR3	vMouse = ::Get_Mouse();

	if (0.f > vMouse.x)
		m_pBackGround->Set_ScrollX(2.f);

	if (WINCX < vMouse.x)
		m_pBackGround->Set_ScrollX(-2.f);

	if (0.f > vMouse.y)
		m_pBackGround->Set_ScrollY(2.f);

	if (WINCY < vMouse.y)
		m_pBackGround->Set_ScrollY(-2.f);

	Invalidate(FALSE);
}

void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnLButtonDown(nFlags, point);

	//CMainFrame*		pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());

	//CMyForm*		pMyForm = dynamic_cast<CMyForm*>(pMain->m_SecondSplitter.GetPane(0, 0));
	//CMapTool*		pMapTool = &(pMyForm->m_MapTool);

	// 피킹
	D3DXVECTOR3 vMouse = ::Get_Mouse();
	vMouse.x -= m_pBackGround->Get_Scroll().x;
	vMouse.y -= m_pBackGround->Get_Scroll().y;

	dynamic_cast<CBackGround*>(m_pBackGround)->Picking(vMouse);

	//Invalidate(FALSE);
}