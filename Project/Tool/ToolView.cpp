
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
#include "MiniView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND	g_hWnd;


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// SetScrollSizes : ��ũ�� ���� ����� �����ϴ� scrollview Ŭ���� ��� �Լ�
	// MM_TEXT : �ȼ����� ũ��� �����ϰڴٴ� �ǹ�
	// �� ��° : ����, ���� ������
	
	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, TILECY * TILEY / 2));
	
	//AfxGetMainWnd : ������ ���� �����츦 ��ȯ�ϴ� ���� �Լ�
	// �ڽ� Ÿ������ �� ��ȯ�Ͽ� ��ȯ��
	CMainFrame*		pMainFrm = (CMainFrame*)AfxGetMainWnd();

	RECT	rcWnd{};

	// GetWindowRect : ���� ������ â�� ��Ʈ ������ ������ �Լ�
	pMainFrm->GetWindowRect(&rcWnd);

	// SetRect : ������ ���ڰ����� rect������ �����ϴ� �Լ�
	// ���� 0,0�������� â�� ��Ʈ�� �����ϰ� �ִ� ��Ȳ
	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom- rcWnd.top);
	
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


	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_SINGLE, L"../Texture/Cube.png", L"Cube")))
	{
		AfxMessageBox(L"Cube Create Failed");
		return;
	}
	
	m_pTerrain = new CTerrain;
	m_pTerrain->Initialize();
	m_pTerrain->SetMainView(this);

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
	
	//m_pTerrain->Render();

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
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
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

	Safe_Delete<CTerrain*>(m_pTerrain);
	CTextureMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->DestroyInstance();

}


void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnLButtonDown(nFlags, point);

	m_pTerrain->TileChange(D3DXVECTOR3(float(point.x)+ GetScrollPos(0), 
									  float(point.y) + GetScrollPos(1), 
									  0.f), 1);

	// Invalidate : �Լ� ȣ�� �� �����쿡 WM_PAINT�� WM_ERASEBKGND �޼����� �߻���Ŵ

	//�Ű����� FALSE �� �� WM_PAINT�� ȣ��
	//�Ű����� true �� �� WM_PAINT, WM_ERASEBKGND �� �� ȣ��
	//WM_ERASEBKGND : ����� ����� �޽���

	Invalidate(FALSE);

	CMainFrame*		pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CMiniView*		pMini = dynamic_cast<CMiniView*>(pMain->m_SecondSplitter.GetPane(0, 0));

	pMini->Invalidate(FALSE);
	
}


void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnMouseMove(nFlags, point);

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		//m_pTerrain->TileChange(D3DXVECTOR3(float(point.x) + GetScrollPos(0), float(point.y) + GetScrollPos(1), 0.f), 1);
		Invalidate(FALSE);

		CMainFrame*		pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
		CMiniView*		pMini = dynamic_cast<CMiniView*>(pMain->m_SecondSplitter.GetPane(0, 0));

		pMini->Invalidate(FALSE);
	}
}
