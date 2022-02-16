#include "stdafx.h"
#include "DeathEffect.h"

CDeathEffect::CDeathEffect()
{
	// empty
}

CDeathEffect::~CDeathEffect()
{
	Release();
}

HRESULT CDeathEffect::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Death/death%d.png", L"Death", L"Idle", 18)))
		return S_FALSE;

	m_wstrObjKey = L"Death";
	m_wstrStateKey = L"Idle";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 18.f, 0.3f };

	return S_OK;
}
