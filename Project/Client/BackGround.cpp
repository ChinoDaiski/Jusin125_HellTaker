#include "stdafx.h"
#include "BackGround.h"

#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"

CBackGround::CBackGround()
	: m_Chapter(ZERO)
{
	ZeroMemory(&m_GridInfo, sizeof(GRID_INFO));
}

CBackGround::~CBackGround()
{
	Release();
}

HRESULT CBackGround::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/BackGround/chapter%d.png", L"BackGround", L"Idle", 8)))
		return S_FALSE;

	m_tInfo.vPos = D3DXVECTOR3(float(WINCX>>1), float(WINCY>>1), 0.f);
	m_wstrObjKey = L"BackGround";
	m_fSpeed = 100.f;

	m_tFrame = { (float)m_Chapter, 8.f };

	Map_Init();
	Create_Grid();

	return S_OK;
}

int CBackGround::Update(void)
{
	D3DXMATRIX	matTrans, matScale;

	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matScale);

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CObj::m_vScroll.x,
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		0.f);

	D3DXMatrixScaling(&matScale, MAPSIZEX, MAPSIZEY, 1.f);

	m_tInfo.matWorld = matScale * matTrans;

	D3DXVECTOR3	vMouse = ::Get_Mouse();

	if (0.f > vMouse.x)
		m_vScroll.x += 300.f * CTimeMgr::GetInstance()->Get_TimeDelta();

	if (WINCX < vMouse.x)
		m_vScroll.x -= 300.f * CTimeMgr::GetInstance()->Get_TimeDelta();

	if (0.f > vMouse.y)
		m_vScroll.y += 300.f * CTimeMgr::GetInstance()->Get_TimeDelta();

	if (WINCY < vMouse.y)
		m_vScroll.y -= 300.f * CTimeMgr::GetInstance()->Get_TimeDelta();

	for (auto& iter : vecGrid)
		iter->Update();

	return OBJ_NOEVENT;
}

void CBackGround::Late_Update(void)
{
	// empty
}

void CBackGround::Render(void)
{
	const TEXINFO*		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(m_wstrObjKey.c_str(), L"Idle", (int)m_tFrame.fFrame);

	if (nullptr == pTexInfo)
		return;

	float		fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float		fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// �ؽ�ó �İ�ü �ּ�
		nullptr,	// ����� �̹��� ������ ���� rect ����ü �ּҰ�, null�� ��� �̹����� 0, 0�� �������� ���
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// ����� �̹��� �߽��࿡ ���� vec3 ����ü �ּҰ�, null�� ��� 0,0�� �߽� ��ǥ�� ��
		nullptr,	// ����� �̹����� ��ġ�� �����ϴ� vec3 ����ü �ּҰ�, null�� ��� ��ũ�� �� 0,0 ��ǥ�� ���
		D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� ���� �̹����� ���� ����, ��� �� ���� ������ �ݿ��ȴ�. �⺻������ 0xffffffff�� �־��ָ� ������ ����

	for (auto& iter : vecGrid)
		iter->Render();
}

void CBackGround::Release(void)
{
	// empty
}

void CBackGround::Create_Grid(void)
{
	for (int i = 2; i < TILEY - 2; ++i)
	{
		for (int j = 5; j < TILEX - 5; ++j)
		{
			m_pGrid = new CGrid;
			m_pGrid->Initialize();

			float fX = float((TILECX * j * m_GridInfo.fCX)) + m_GridInfo.Width;
			float fY = float((TILECY * i * m_GridInfo.fCY)) + m_GridInfo.Height;

			m_pGrid->Set_Pos(D3DXVECTOR3(fX, fY, 0.f));

			vecGrid.push_back(m_pGrid);
		}
	}
}

void CBackGround::Map_Init(void)
{
	switch (m_Chapter)
	{
	case ZERO: case FIVE:
		Part1_ChapterInit();
		m_GridInfo.iStart_Index = 2;
		m_GridInfo.jStart_Index = 5;
		m_GridInfo.iEnd_Index = 2;
		m_GridInfo.jEnd_Index = 5;
		break;
	case ONE:
		Part1_ChapterInit();
		m_GridInfo.iStart_Index = 0;
		m_GridInfo.jStart_Index = 0;
		m_GridInfo.iEnd_Index = 0;
		m_GridInfo.jEnd_Index = 0;
		break;
	case TWO: case THREE: case FOUR: case SIX:
		m_GridInfo.iStart_Index = 2;
		m_GridInfo.jStart_Index = 5;
		m_GridInfo.iEnd_Index = 2;
		m_GridInfo.jEnd_Index = 5;
		break;
	case CBackGround::SEVEN:
		// TODO : ����� �� ���� (Lucifer)
		Part3_ChapterInit();
		break;
	case CBackGround::EIGHT:
		// empty
		break;
	}
}

void CBackGround::Part1_ChapterInit()
{
	m_GridInfo.fCX = MAPSIZEX * ((1920.f / TILEX) / 100.f);
	m_GridInfo.fCY = MAPSIZEY * ((1080.f / TILEY) / 100.f);
	m_GridInfo.Width = ((TILECX * m_GridInfo.fCX) / 2.f);
	m_GridInfo.Height = 0.f;
}

void CBackGround::Part2_ChapterInit()
{
	m_GridInfo.fCX = MAPSIZEX * ((1920.f / TILEX) / 100.f);
	m_GridInfo.fCY = MAPSIZEY * ((1080.f / TILEY) / 100.f);
	m_GridInfo.Width = 0.f;
	m_GridInfo.Height = -((TILECY * m_GridInfo.fCY) / 2.f);
}

void CBackGround::Part3_ChapterInit()
{
	// TODO : Lucifer room Create
}
