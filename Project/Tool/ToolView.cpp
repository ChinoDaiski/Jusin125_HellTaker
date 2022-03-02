
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}

CToolView::~CToolView()
{
	// empty
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// SetScrollSizes : ��ũ�� ���� ����� �����ϴ� scrollview Ŭ���� ��� �Լ�
	// MM_TEXT : �ȼ����� ũ��� �����ϰڴٴ� �ǹ�
	// �� ��° : ����, ���� ������

	// SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, TILECY * TILEY / 2));
	SetScrollSizes(MM_TEXT, CSize(0, 0));

	//AfxGetMainWnd : ������ ���� �����츦 ��ȯ�ϴ� ���� �Լ�
	// �ڽ� Ÿ������ �� ��ȯ�Ͽ� ��ȯ��
	CMainFrame*		pMainFrm = (CMainFrame*)AfxGetMainWnd();

	RECT	rcWnd{};

	// GetWindowRect : ���� ������ â�� ��Ʈ ������ ������ �Լ�
	pMainFrm->GetWindowRect(&rcWnd);

	// SetRect : ������ ���ڰ����� rect������ �����ϴ� �Լ�
	// ���� 0,0�������� â�� ��Ʈ�� �����ϰ� �ִ� ��Ȳ
	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);

	RECT	rcMainView{};
	//GetClientRect : ���� view â�� rect ������ ������ �Լ�
	GetClientRect(&rcMainView);

	// �����Ӱ� viewâ�� ����, ���� ���� ���Ѵ�.
	float	fRowFrm = float(rcWnd.right - rcMainView.right);
	float	fColFrm = float(rcWnd.bottom - rcMainView.bottom);

	// SetWindowPos: ���ڰ� ��� ���Ӱ� ������ ��ġ�� ũ�⸦ �����ϴ� �Լ�
	// 1���� : ��ġ�� �������� Z������ ���� ������
	// 2, 3���� : left, top ��ǥ
	// 4, 5���� : ����, ���� â ������
	// 6���� : SWP_NOZORDER : ���� ������ �����ϰڴٴ� �÷��� ��, ���� null�� ��� ���� ������ ���� �ʰڴ�.

	pMainFrm->SetWindowPos(nullptr, 300, 100, int(WINCX + fRowFrm), int(WINCY + fColFrm), SWP_NOZORDER);

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	g_hWnd = m_hWnd;

	if (FAILED(CDevice::GetInstance()->InitDevice()))
		AfxMessageBox(L"Device Create Failed");

	// ��׶��� ����
	m_pBackGround = new CBackGround;

	if (nullptr != m_pBackGround)
		m_pBackGround->Initialize();

	CObjMgr::GetInstance()->Add_Object(CObjMgr::TERRAIN, m_pBackGround);

	dynamic_cast<CBackGround*>(m_pBackGround)->Select_Chapter(SEVEN);
}

// CToolView �׸���
void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	CDevice::GetInstance()->Render_Begin();

	//Synchro_Scroll();

	m_pBackGround->Update();
	
	m_pBackGround->Render();

	CDevice::GetInstance()->Render_End(g_hWnd);

}

// CToolView �μ�

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG

// CToolView �޽��� ó����

void CToolView::OnDestroy()
{
	CScrollView::OnDestroy();
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnLButtonDown(nFlags, point);

	//CMainFrame*		pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());

	//CMyForm*		pMyForm = dynamic_cast<CMyForm*>(pMain->m_SecondSplitter.GetPane(0, 0));
	//CMapTool*		pMapTool = &(pMyForm->m_MapTool);

	// ��ŷ
	D3DXVECTOR3 vMouse = ::Get_Mouse();
	vMouse.x -= m_pBackGround->Get_Scroll().x;
	vMouse.y -= m_pBackGround->Get_Scroll().y;

	dynamic_cast<CBackGround*>(m_pBackGround)->Picking(vMouse);

	//Invalidate(FALSE);
}