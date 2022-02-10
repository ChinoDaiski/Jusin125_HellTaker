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

	CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// 텍스처 컴객체 주소
		nullptr,	// 출력할 이미지 영역에 대한 rect 구조체 주소값, null인 경우 이미지의 0, 0을 기준으로 출력
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// 출력할 이미지 중심축에 대한 vec3 구조체 주소값, null인 경우 0,0이 중심 좌표가 됨
		nullptr,	// 출력할 이미지의 위치를 지정하는 vec3 구조체 주소값, null인 경우 스크린 상 0,0 좌표에 출력
		D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 원본 이미지와 섞을 색상, 출력 시 섞은 색상이 반영된다. 기본값으로 0xffffffff를 넣어주면 원본색 유지

	for (auto& iter : vecGrid)
		iter->Render();

}

void CBackGround::Release(void)
{
	for_each(vecGrid.begin(), vecGrid.end(), Safe_Delete<CObj*>);
	vecGrid.clear();
}

void CBackGround::Create_Grid(void)
{
	int iIndex = 0;

	for (int i = m_GridInfo.iStart_Index; i < m_GridInfo.iEnd_Index; ++i)		// Y 축
	{
		for (int j = m_GridInfo.jStart_Index; j < m_GridInfo.jEnd_Index; ++j)	// X 축
		{
			m_pGrid = new CGrid;
			m_pGrid->Initialize();
			dynamic_cast<CGrid*>(m_pGrid)->Set_Index(iIndex);

			float fX = float((TILECX * j * m_GridInfo.fCX)) + m_GridInfo.Width;
			float fY = float((TILECY * i * m_GridInfo.fCY)) + m_GridInfo.Height;

			m_pGrid->Set_Pos(D3DXVECTOR3(fX, fY, 0.f));

			vecGrid.push_back(m_pGrid);
			++iIndex;
		}
	}
}

void CBackGround::Map_Init(void)
{
	switch (m_Chapter)
	{
	case ZERO:
		Part1_ChapterInit();
		m_GridInfo.iStart_Index = 2;
		m_GridInfo.jStart_Index = 5;
		m_GridInfo.iEnd_Index = TILEY - 1;
		m_GridInfo.jEnd_Index = TILEX - 5;
		break;
	case ONE:
		Part1_ChapterInit();
		m_GridInfo.iStart_Index = 1;
		m_GridInfo.jStart_Index = 5;
		m_GridInfo.iEnd_Index = TILEY - 1;
		m_GridInfo.jEnd_Index = TILEX - 5;
		break;
	case FIVE:
		Part1_ChapterInit();
		m_GridInfo.iStart_Index = 1;
		m_GridInfo.jStart_Index = 5;
		m_GridInfo.iEnd_Index = TILEY - 0;
		m_GridInfo.jEnd_Index = TILEX - 5;
		break;
	case TWO:
		Part2_ChapterInit();
		m_GridInfo.iStart_Index = 2;
		m_GridInfo.jStart_Index = 5;
		m_GridInfo.iEnd_Index = TILEY - 0;
		m_GridInfo.jEnd_Index = TILEX - 4;
		break;
	case THREE:
		Part2_ChapterInit();
		m_GridInfo.iStart_Index = 3;
		m_GridInfo.jStart_Index = 5;
		m_GridInfo.iEnd_Index = TILEY - 1;
		m_GridInfo.jEnd_Index = TILEX - 4;
		break;
	case FOUR:
		Part2_ChapterInit();
		m_GridInfo.iStart_Index = 2;
		m_GridInfo.jStart_Index = 6;
		m_GridInfo.iEnd_Index = TILEY - 0;
		m_GridInfo.jEnd_Index = TILEX - 5;
		break;
	case SIX:
		Part2_ChapterInit();
		m_GridInfo.iStart_Index = 2;
		m_GridInfo.jStart_Index = 6;
		m_GridInfo.iEnd_Index = TILEY - 0;
		m_GridInfo.jEnd_Index = TILEX - 5;
		break;
	case SEVEN:
		Part3_ChapterInit();
		m_GridInfo.iStart_Index = 2;
		m_GridInfo.jStart_Index = 4;
		m_GridInfo.iEnd_Index = TILEY + 5;
		m_GridInfo.jEnd_Index = TILEX - 4;
		break;
	case EIGHT:
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
	m_GridInfo.fCX = MAPSIZEX * ((1920.f / TILEX) / 100.f);
	m_GridInfo.fCY = MAPSIZEY * ((1080.f / TILEY) / 100.f);
	m_GridInfo.Width = ((TILECX * m_GridInfo.fCX) / 2.f);
	m_GridInfo.Height = 0.f;
}

void CBackGround::Select_Chapter(CHAPTER _chapter)
{
	m_Chapter = _chapter;
	m_tFrame.fFrame = (float)m_Chapter;
	Map_Init();
	Create_Grid();
}

D3DXVECTOR3 CBackGround::Find_IndexPos(int _index)
{
	int index = 0;

	for (auto& iter : vecGrid)
	{
		index = dynamic_cast<CGrid*>(iter)->Get_Index();
		if (index == _index)
		{
			return iter->Get_Info().vPos;
		}
	}
}
