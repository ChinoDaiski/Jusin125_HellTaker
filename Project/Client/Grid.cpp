#include "stdafx.h"
#include "Grid.h"

#include "Device.h"
#include "TextureMgr.h"

CGrid::CGrid()
	: m_iIndex(0), m_bOnObject(false)
{
	// empty
}

CGrid::~CGrid()
{
	Release();
}

HRESULT CGrid::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_SINGLE, L"../Texture/BackGround/Layer/Layer.png", L"Layer")))
		return S_FALSE;

	m_tInfo.vPos = { 0.f, 0.f, 0.f };
	m_wstrObjKey = L"Layer";
	m_fSpeed = 100.f;

	m_GridState = CAN_MOVE;

	return S_OK;
}

int CGrid::Update(void)
{
	D3DXMATRIX	matTrans, matScale;

	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matScale);

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CObj::m_vScroll.x,
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		0.f);

	float fX = MAPSIZEX * ((1920.f / 19.f) / 100.f);
	float fY = MAPSIZEY * ((1080.f / 11.f) / 100.f);
	D3DXMatrixScaling(&matScale, fX, fY, 1.f);

	m_tInfo.matWorld = matScale * matTrans;

	return OBJ_NOEVENT;
}

void CGrid::Late_Update(void)
{
	// empty
}

void CGrid::Render(void)
{
	TCHAR	szBuf[MIN_STR]{};

	const TEXINFO*		pTexInfo = CTextureMgr::GetInstance()->Get_Texture(m_wstrObjKey.c_str());

	if (nullptr == pTexInfo)
		return;

	float		fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float		fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->Get_Sprite()->Draw(pTexInfo->pTexture,		// 텍스처 컴객체 주소
		nullptr,	// 출력할 이미지 영역에 대한 rect 구조체 주소값, null인 경우 이미지의 0, 0을 기준으로 출력
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// 출력할 이미지 중심축에 대한 vec3 구조체 주소값, null인 경우 0,0이 중심 좌표가 됨
		nullptr,	// 출력할 이미지의 위치를 지정하는 vec3 구조체 주소값, null인 경우 스크린 상 0,0 좌표에 출력
		D3DCOLOR_ARGB(150, 255, 255, 255)); // 출력할 원본 이미지와 섞을 색상, 출력 시 섞은 색상이 반영된다. 기본값으로 0xffffffff를 넣어주면 원본색 유지

	// 타일 인덱스 출력
	swprintf_s(szBuf, L"%d", m_iIndex);
	// SETTRANSFORM에 영향을 받음
	CDevice::GetInstance()->Get_Font()->DrawTextW(CDevice::GetInstance()->Get_Sprite(),
		szBuf,
		lstrlen(szBuf),
		NULL,
		0,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CGrid::Release(void)
{
	// empty
}
