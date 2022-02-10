#include "stdafx.h"
#include "Terrain.h"
#include "TextureMgr.h"
#include "Device.h"
#include "ToolView.h"


CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release();
}

void CTerrain::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Stage/Terrain/Tile/Tile%d.png", L"Terrain", L"Tile", 36)))
	{
		AfxMessageBox(L"Terrain Create Failed");
		return;
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


}

void CTerrain::Update(void)
{
}

void CTerrain::Render(void)
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	int iIndex = 0;
	TCHAR	szBuf[MIN_STR]{};

	for (auto& iter : m_vecTile)
	{
		RECT	rc{};

		// :: 함수 : 글로벌 전역함수 호출구문, 같은 이름의 멤버와 구분하기 위해 사용
		// 현재 클라이언트 영역의 rect 정보를 얻어오는 함수
		::GetClientRect(m_pMainView->m_hWnd, &rc);

		// 최소화된 창사이즈의 비율값을 만들어내자.
		float fX = WINCX / float(rc.right - rc.left);
		float fY = WINCY / float(rc.bottom - rc.top);

		D3DXMatrixIdentity(&matWorld);

		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans, iter->vPos.x - m_pMainView->GetScrollPos(0),// 0은 x 스크롤, 1은 y스크롤
										iter->vPos.y - m_pMainView->GetScrollPos(1),
										iter->vPos.z);

		matWorld = matScale * matTrans;

		Set_Ratio(&matWorld, fX, fY);

		const TEXINFO*		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(L"Terrain", L"Tile", iter->byDrawID);
		
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
			D3DCOLOR_ARGB(255, 0,0,0));

		++iIndex;
	}	
}

void CTerrain::Mini_Render(void)
{
	D3DXMATRIX		matWorld, matScale, matTrans;

	for (auto& iter : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);

		D3DXMatrixScaling(&matScale,1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans, iter->vPos.x ,// 0은 x 스크롤, 1은 y스크롤
			iter->vPos.y,
			iter->vPos.z);

		matWorld = matScale * matTrans;

		Set_Ratio(&matWorld, 0.3f, 0.3f);

		const TEXINFO*		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(L"Terrain", L"Tile", iter->byDrawID);

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
	}
}

void CTerrain::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
}

int CTerrain::GetTileIndex(const D3DXVECTOR3 & vPos)
{
	for (size_t iIndex = 0; iIndex < m_vecTile.size(); ++iIndex)
	{
		if (Picking(vPos, iIndex))
			return iIndex;
	}
	
	return -1;		// 0번 타일이 존재할 수 있기 때문에
}



void CTerrain::TileChange(const D3DXVECTOR3 & vPos, const BYTE & byDrawID)
{
	int		iIndex = GetTileIndex(vPos);

	if (-1 == iIndex)
		return;

	m_vecTile[iIndex]->byDrawID = byDrawID;
	m_vecTile[iIndex]->byOption = 1;		
}


void CTerrain::Set_Ratio(D3DXMATRIX* pOut, float fRatioX, float fRatioY)
{
	pOut->_11 *= fRatioX;
	pOut->_21 *= fRatioX;
	pOut->_31 *= fRatioX;
	pOut->_41 *= fRatioX;

	pOut->_12 *= fRatioY;
	pOut->_22 *= fRatioY;
	pOut->_32 *= fRatioY;
	pOut->_42 *= fRatioY;
}

bool CTerrain::Picking(const D3DXVECTOR3& vPos, const int& iIndex)
{
	D3DXVECTOR3	vPoint[4] = {

		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x,	m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f),	// 12
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + (TILECX / 2.f),	m_vecTile[iIndex]->vPos.y, 0.f),	// 3
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x,	m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f),	// 6
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - (TILECX / 2.f),	m_vecTile[iIndex]->vPos.y, 0.f),	// 9

	};

	// 시계방향으로 방향벡터를 만들자

	D3DXVECTOR3		vDir[4] = {

		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]	
	
	};

	// 각 방향벡터의 법선을 구함

	D3DXVECTOR3		vNormal[4] =  {

		D3DXVECTOR3(-vDir[0].y, vDir[0].x, 0.f),
		D3DXVECTOR3(-vDir[1].y, vDir[1].x, 0.f),
		D3DXVECTOR3(-vDir[2].y, vDir[2].x, 0.f),
		D3DXVECTOR3(-vDir[3].y, vDir[3].x, 0.f)
	};

	// 구한 법선 벡터들을 정규화(단위벡터) 시켜준다.
	for (int i = 0; i < 4; ++i)
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);

	// 각 정점으로부터 마우스 위치를 향하는 방향벡터를 구한다

	D3DXVECTOR3	vMouseDir[4] = {

		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]
	};

	for (int i = 0; i < 4; ++i)
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);

	for (int i = 0; i < 4; ++i)
	{
		// 예각이 나왔다
		if (0.f < D3DXVec3Dot(&vNormal[i], &vMouseDir[i]))
			return false;
	}

	return true;
}
/*
bool CTerrain::Picking(const D3DXVECTOR3 & vPos, const int & iIndex)
{
	// 12시 방향을 기점으로 0~3번까지 기울기를 구함
	// 0번 ,2번 음수 기울기를 갖고 있음

	float	fGradient[4] = {
		 (TILECY / 2.f) / (TILECX /2.f) * -1.f,
		 (TILECY / 2.f) / (TILECX / 2.f),
		 (TILECY / 2.f) / (TILECX / 2.f) * -1.f,
		 (TILECY / 2.f) / (TILECX / 2.f)
	};

	D3DXVECTOR3	vPoint[4] = {

		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x,	m_vecTile[iIndex]->vPos.y + (TILECY /2.f), 0.f),	// 12
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + (TILECX / 2.f),	m_vecTile[iIndex]->vPos.y, 0.f),	// 3
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x,	m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f),	// 6
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - (TILECX / 2.f),	m_vecTile[iIndex]->vPos.y, 0.f),	// 9

	};

	// y = ax + b
	// b = y - ax

	float	fB[4] = {

		vPoint[0].y - fGradient[0] * vPoint[0].x, 
		vPoint[1].y - fGradient[1] * vPoint[1].x,
		vPoint[2].y - fGradient[2] * vPoint[2].x,
		vPoint[3].y - fGradient[3] * vPoint[3].x
	};

	bool	bCheck[4]{ false };

	/ *ax + b - y == 0 (직선 상에 있음)
	ax + b - y < 0  (직선보다 위)
	ax + b - y > 0  (직선보다 아래)* /

	// 우 상단
	if (0.f < fGradient[0] * vPos.x + fB[0] - vPos.y)
		bCheck[0] = true;

	// 우 하단
	if (0.f > fGradient[1] * vPos.x + fB[1] - vPos.y)
		bCheck[1] = true;

	// 좌 하단
	if (0.f > fGradient[2] * vPos.x + fB[2] - vPos.y)
		bCheck[2] = true;

	// 좌 상단
	if (0.f < fGradient[3] * vPos.x + fB[3] - vPos.y)
		bCheck[3] = true;
	
	return bCheck[0] && bCheck[1] && bCheck[2] && bCheck[3];
}*/

