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

		// :: �Լ� : �۷ι� �����Լ� ȣ�ⱸ��, ���� �̸��� ����� �����ϱ� ���� ���
		// ���� Ŭ���̾�Ʈ ������ rect ������ ������ �Լ�
		::GetClientRect(m_pMainView->m_hWnd, &rc);

		// �ּ�ȭ�� â�������� �������� ������.
		float fX = WINCX / float(rc.right - rc.left);
		float fY = WINCY / float(rc.bottom - rc.top);

		D3DXMatrixIdentity(&matWorld);

		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans, iter->vPos.x - m_pMainView->GetScrollPos(0),// 0�� x ��ũ��, 1�� y��ũ��
										iter->vPos.y - m_pMainView->GetScrollPos(1),
										iter->vPos.z);

		matWorld = matScale * matTrans;

		Set_Ratio(&matWorld, fX, fY);

		const TEXINFO*		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(L"Terrain", L"Tile", iter->byDrawID);
		
		if (nullptr == pTexInfo)
			return;

		float		fCenterX = pTexInfo->tImgInfo.Width / 2.f;
		float		fCenterY = pTexInfo->tImgInfo.Height / 2.f;
		
		// ����� ��ġ�� �̿��Ͽ� ��� ������ �����ִ� �Լ�
		CDevice::GetInstance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// �ؽ�ó �İ�ü �ּ�
			nullptr,	// ����� �̹��� ������ ���� rect ����ü �ּҰ�, null�� ��� �̹����� 0, 0�� �������� ���
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// ����� �̹��� �߽��࿡ ���� vec3 ����ü �ּҰ�, null�� ��� 0,0�� �߽� ��ǥ�� ��
			nullptr,	// ����� �̹����� ��ġ�� �����ϴ� vec3 ����ü �ּҰ�, null�� ��� ��ũ�� �� 0,0 ��ǥ�� ���
			D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� ���� �̹����� ���� ����, ��� �� ���� ������ �ݿ��ȴ�. �⺻������ 0xffffffff�� �־��ָ� ������ ����

		// Ÿ�� �ε��� ���
		swprintf_s(szBuf, L"%d", iIndex);
		// SETTRANSFORM�� ������ ����
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
		D3DXMatrixTranslation(&matTrans, iter->vPos.x ,// 0�� x ��ũ��, 1�� y��ũ��
			iter->vPos.y,
			iter->vPos.z);

		matWorld = matScale * matTrans;

		Set_Ratio(&matWorld, 0.3f, 0.3f);

		const TEXINFO*		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(L"Terrain", L"Tile", iter->byDrawID);

		if (nullptr == pTexInfo)
			return;

		float		fCenterX = pTexInfo->tImgInfo.Width / 2.f;
		float		fCenterY = pTexInfo->tImgInfo.Height / 2.f;

		// ����� ��ġ�� �̿��Ͽ� ��� ������ �����ִ� �Լ�
		CDevice::GetInstance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// �ؽ�ó �İ�ü �ּ�
			nullptr,	// ����� �̹��� ������ ���� rect ����ü �ּҰ�, null�� ��� �̹����� 0, 0�� �������� ���
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// ����� �̹��� �߽��࿡ ���� vec3 ����ü �ּҰ�, null�� ��� 0,0�� �߽� ��ǥ�� ��
			nullptr,	// ����� �̹����� ��ġ�� �����ϴ� vec3 ����ü �ּҰ�, null�� ��� ��ũ�� �� 0,0 ��ǥ�� ���
			D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� ���� �̹����� ���� ����, ��� �� ���� ������ �ݿ��ȴ�. �⺻������ 0xffffffff�� �־��ָ� ������ ����
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
	
	return -1;		// 0�� Ÿ���� ������ �� �ֱ� ������
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

	// �ð�������� ���⺤�͸� ������

	D3DXVECTOR3		vDir[4] = {

		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]	
	
	};

	// �� ���⺤���� ������ ����

	D3DXVECTOR3		vNormal[4] =  {

		D3DXVECTOR3(-vDir[0].y, vDir[0].x, 0.f),
		D3DXVECTOR3(-vDir[1].y, vDir[1].x, 0.f),
		D3DXVECTOR3(-vDir[2].y, vDir[2].x, 0.f),
		D3DXVECTOR3(-vDir[3].y, vDir[3].x, 0.f)
	};

	// ���� ���� ���͵��� ����ȭ(��������) �����ش�.
	for (int i = 0; i < 4; ++i)
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);

	// �� �������κ��� ���콺 ��ġ�� ���ϴ� ���⺤�͸� ���Ѵ�

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
		// ������ ���Դ�
		if (0.f < D3DXVec3Dot(&vNormal[i], &vMouseDir[i]))
			return false;
	}

	return true;
}
/*
bool CTerrain::Picking(const D3DXVECTOR3 & vPos, const int & iIndex)
{
	// 12�� ������ �������� 0~3������ ���⸦ ����
	// 0�� ,2�� ���� ���⸦ ���� ����

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

	/ *ax + b - y == 0 (���� �� ����)
	ax + b - y < 0  (�������� ��)
	ax + b - y > 0  (�������� �Ʒ�)* /

	// �� ���
	if (0.f < fGradient[0] * vPos.x + fB[0] - vPos.y)
		bCheck[0] = true;

	// �� �ϴ�
	if (0.f > fGradient[1] * vPos.x + fB[1] - vPos.y)
		bCheck[1] = true;

	// �� �ϴ�
	if (0.f > fGradient[2] * vPos.x + fB[2] - vPos.y)
		bCheck[2] = true;

	// �� ���
	if (0.f < fGradient[3] * vPos.x + fB[3] - vPos.y)
		bCheck[3] = true;
	
	return bCheck[0] && bCheck[1] && bCheck[2] && bCheck[3];
}*/

