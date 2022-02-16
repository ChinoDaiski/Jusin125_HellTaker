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

void CDeathBackGround::Late_Update(void)
{
	// empty
}
