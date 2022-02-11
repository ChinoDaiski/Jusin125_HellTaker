#include "stdafx.h"
#include "HitEffect.h"

CHitEffect::CHitEffect()
{
	// empty
}

CHitEffect::~CHitEffect()
{
	Release();
}

HRESULT CHitEffect::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Player/Effect/HitEffect/Big/Left/BigLeft%d.png", L"BigLeft", L"Idle", 5)))
		return S_FALSE;

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Player/Effect/HitEffect/Big/Right/BigRight%d.png", L"BigRight", L"Idle", 5)))
		return S_FALSE;

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Player/Effect/HitEffect/Small/Left/SmallLeft%d.png", L"SmallLeft", L"Idle", 4)))
		return S_FALSE;

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Player/Effect/HitEffect/Small/Right/SmallRight%d.png", L"SmallRight", L"Idle", 4)))
		return S_FALSE;

	m_wstrObjKey = L"BigLeft";
	m_wstrStateKey = L"Idle";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 5.f, 3.5f };

	return S_OK;
}
