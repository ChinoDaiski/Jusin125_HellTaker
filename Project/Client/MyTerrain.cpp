#include "stdafx.h"
#include "MyTerrain.h"
#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"


CMyTerrain::CMyTerrain()
{
}


CMyTerrain::~CMyTerrain()
{
	Release();
}

HRESULT CMyTerrain::Initialize(void)
{
	if (FAILED(Load_Tile(L"../Data/Map.dat")))
		return E_FAIL;

	m_vecTile.reserve(TILEX * TILEY);

	return S_OK;
}

int CMyTerrain::Update(void)
{
	D3DXVECTOR3	vMouse = ::Get_Mouse();

	if (0.f > vMouse.x)
		m_vScroll.x += 300.f * CTimeMgr::GetInstance()->Get_TimeDelta();

	if (WINCX < vMouse.x)
		m_vScroll.x -= 300.f * CTimeMgr::GetInstance()->Get_TimeDelta();

	if (0.f > vMouse.y)
		m_vScroll.y += 300.f * CTimeMgr::GetInstance()->Get_TimeDelta();

	if (WINCY < vMouse.y)
		m_vScroll.y -= 300.f * CTimeMgr::GetInstance()->Get_TimeDelta();


	return OBJ_NOEVENT;
}

void CMyTerrain::Late_Update(void)
{
	
}

void CMyTerrain::Render(void)
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	int iIndex = 0;
	TCHAR	szBuf[MIN_STR]{};

	int	iCullX = int(-m_vScroll.x) / TILECX;
	int	iCullY = int(-m_vScroll.y) / (TILECY / 2);


	int	iWidthX = WINCX / TILECX;
	int	iHeightY = WINCY / (TILECY / 2);

	for (int i = iCullY; i < iCullY + iHeightY + 2; ++i)
	{
		for (int j = iCullX; j < iCullX + iWidthX + 2; ++j)
		{
			int		iIndex = j + TILEX * i;

			if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
				continue;

			RECT	rc{};

			D3DXMatrixIdentity(&matWorld);

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
			D3DXMatrixTranslation(&matTrans, m_vecTile[iIndex]->vPos.x + m_vScroll.x,
				m_vecTile[iIndex]->vPos.y + m_vScroll.y,
				m_vecTile[iIndex]->vPos.z);

			matWorld = matScale * matTrans;

			const TEXINFO*		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(L"Terrain", L"Tile", m_vecTile[iIndex]->byDrawID);

			if (nullptr == pTexInfo)
				return;

			float		fCenterX = pTexInfo->tImgInfo.Width / 2.f;
			float		fCenterY = pTexInfo->tImgInfo.Height / 2.f;

			// 행렬을 장치를 이용하여 모든 정점에 곱해주는 함수
			CDevice::GetInstance()->Get_Sprite()->SetTransform(&matWorld);

			CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// 텍스처 컴객체 주소
				nullptr,	// 출력할 이미지 영역에 대한 rect 구조체 주소값, null인 경우 이미지의 0, 0을 기준으로 출력
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// 출력할 이미지 중심축에 대한 vec3 구조체 주소값, null인 경우 0,0이 중심 좌표가 됨
				nullptr,	// 출력할 이미지의 위치를 지정하는 vec3 구조체 주소값, null인 경우 스크린 상 0,0 좌표에 출력
				D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 원본 이미지와 섞을 색상, 출력 시 섞은 색상이 반영된다. 기본값으로 0xffffffff를 넣어주면 원본색 유지

													// 타일 인덱스 출력
			swprintf_s(szBuf, L"%d", iIndex);
			// SETTRANSFORM에 영향을 받음
			CDevice::GetInstance()->Get_Font()->DrawTextW(CDevice::GetInstance()->Get_Sprite(),
				szBuf,
				lstrlen(szBuf),
				NULL,
				0,
				D3DCOLOR_ARGB(255, 0, 0, 0));

			++iIndex;
		}
	}
}

void CMyTerrain::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();

	m_vecTile.shrink_to_fit();	// capacity 지우는 함수
}

HRESULT CMyTerrain::Load_Tile(const TCHAR* pTilePath)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Stage/Terrain/Tile/Tile%d.png", L"Terrain", L"Tile", 36)))
	{
		//MessageBox(L"Terrain Create Failed");
		return S_FALSE;
	}

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			TILE*		pTile = new TILE;

			float fX = (TILECX * j) + ((TILECX / 2.f) * (i % 2));
			float fY = (TILECY / 2.f) * i;

			pTile->vPos = D3DXVECTOR3(fX, fY, 0.f);
			pTile->vSize = D3DXVECTOR3((float)TILECX, (float)TILECY, 0.f);
			pTile->byOption = 0;
			pTile->byDrawID = 3;

			m_vecTile.push_back(pTile);
		}
	}

	return S_OK;
}
