#include "stdafx.h"
#include "DeathBackGround.h"

CDeathBackGround::CDeathBackGround()
{
	// empty
}

CDeathBackGround::~CDeathBackGround()
{
	Release();
}

HRESULT CDeathBackGround::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Death/BackGround/DeathBackGround%d.png", L"DeathBackGround", L"Idle", 1)))
		return S_FALSE;

	m_wstrObjKey = L"DeathBackGround";
	m_wstrStateKey = L"Idle";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 1.f };

	return S_OK;
}

int CDeathBackGround::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	D3DXMATRIX	matTrans, matScale;

	D3DXMatrixIdentity(&matTrans);
	D3DXMatrixIdentity(&matScale);

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CObj::m_vScroll.x,
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		0.f);

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	m_tInfo.matWorld = matScale * matTrans;

	return OBJ_NOEVENT;
}

void CDeathBackGround::Late_Update(void)
{
	// empty
}
