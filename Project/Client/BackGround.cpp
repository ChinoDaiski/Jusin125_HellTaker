#include "stdafx.h"
#include "BackGround.h"

#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"

CBackGround::CBackGround()
	: m_Chapter(ZERO)
	, m_bVibration(false), m_iViveCount(0)
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
	//LoadData();

	return S_OK;
}

int CBackGround::Update(void)
{
	if (m_bVibration)
	{
		if (m_iViveCount % 2 == 0)
		{
			m_tInfo.vPos.x += 4.f;
			m_tInfo.vPos.y += 5.f;
		}
		else
		{
			m_tInfo.vPos.x -= 4.f;
			m_tInfo.vPos.y -= 5.f;
		}

		++m_iViveCount;

		if (m_iViveCount >= 70)
		{
			m_iViveCount = 0;
			m_bVibration = false;
		}
	}

	D3DXMATRIX	matTrans, matScale;

	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matScale);

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CObj::m_vScroll.x,
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		0.f);

	D3DXMatrixScaling(&matScale, MAPSIZEX, MAPSIZEY, 1.f);

	m_tInfo.matWorld = matScale * matTrans;

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
	//Create_Grid();
	LoadData(_chapter);
}

D3DXVECTOR3 CBackGround::Find_IndexPos(int _index)
{
	int index = 0;

	for (auto& iter : vecGrid)
	{
		index = dynamic_cast<CGrid*>(iter)->Get_Index();
		if (index == _index)
			return iter->Get_Info().vPos;
	}

	return D3DXVECTOR3 {0.f,0.f,0.f};
}

GRID_STATE CBackGround::Find_IndexBlock(int _index)
{
	int index = 0;

	for (auto& iter : vecGrid)
	{
		index = dynamic_cast<CGrid*>(iter)->Get_Index();
		if (index == _index)
			return iter->Get_GridState();
	}

	return CAN_MOVE;
}

void CBackGround::Set_GridState(int _index, GRID_STATE _gridState)
{
	int index = 0;

	for (auto& iter : vecGrid)
	{
		index = dynamic_cast<CGrid*>(iter)->Get_Index();
		if (index == _index)
		{
			iter->Set_GridState(_gridState);
		}
	}
}

void CBackGround::Picking(D3DXVECTOR3 _pos)
{
	for (auto& iter : vecGrid)
	{
		if (true == dynamic_cast<CGrid*>(iter)->Click_Grid(_pos))
		{
			iter->Set_GridState(CANT_MOVE);
		}
	}
}

void CBackGround::SaveData()
{
	TCHAR		szFullPath[MAX_PATH] = L"";

	wsprintf(szFullPath, L"../Data/Grid%d.dat", (int)m_Chapter);

	HANDLE	hFile = CreateFile(szFullPath,	// 파일의 경로 및 이름 명시	
		GENERIC_WRITE,		// 파일 접근 모드, WRITE는 쓰기, READ는 읽기
		NULL,				// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가할 것인지 옵션, NULL 공유하지 않음
		NULL,				// 보안속성, NULL일 경우 기본값으로 설정
		CREATE_ALWAYS,		// 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXITING 파일이 있을 경우에만 여는 옵션
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김과 같은 속성을 의미), 아무런 속성이 없는 경우의 플래그
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일이 있는 주소값

	DWORD		dwByte = 0;
	GRID_STATE	gridState;

	for (auto& iter : vecGrid)
	{
		gridState = dynamic_cast<CGrid*>(iter)->Get_GridState();

		WriteFile(hFile, &iter->Get_Info(), sizeof(INFO), &dwByte, nullptr);
		WriteFile(hFile, &gridState, sizeof(GRID_STATE), &dwByte, nullptr);
	}

	// 파일 소멸
	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("Save 완료"), _T("Success"), MB_OK);
}

void CBackGround::LoadData(CHAPTER _chap)
{
	TCHAR		szFullPath[MAX_PATH] = L"";

	wsprintf(szFullPath, L"../Data/Grid%d.dat", (int)_chap);

	HANDLE	hFile = CreateFile(szFullPath,	// 파일의 경로 및 이름 명시	
		GENERIC_READ,		// 파일 접근 모드, WRITE는 쓰기, READ는 읽기
		NULL,				// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가할 것인지 옵션, NULL 공유하지 않음
		NULL,				// 보안속성, NULL일 경우 기본값으로 설정
		OPEN_EXISTING,		// 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXITING 파일이 있을 경우에만 여는 옵션
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김과 같은 속성을 의미), 아무런 속성이 없는 경우의 플래그
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일이 있는 주소값


	DWORD		dwByte = 0;
	INFO		tInfo{};
	GRID_STATE	gridState;

	Release();

	int iIndex = 0;	

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &gridState, sizeof(GRID_STATE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_pGrid = new CGrid;
		m_pGrid->Initialize();

		dynamic_cast<CGrid*>(m_pGrid)->Set_Index(iIndex);
		dynamic_cast<CGrid*>(m_pGrid)->Set_GridState(gridState);
		m_pGrid->Set_Pos(D3DXVECTOR3(tInfo.vPos.x, tInfo.vPos.y, 0.f));

		vecGrid.push_back(m_pGrid);
		++iIndex;
	}

	// 파일 소멸
	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("Load 완료"), _T("Success"), MB_OK);
}
