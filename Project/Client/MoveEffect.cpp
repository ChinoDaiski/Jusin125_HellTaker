#include "stdafx.h"
#include "MoveEffect.h"


CMoveEffect::CMoveEffect()
{
	// empty
}

CMoveEffect::~CMoveEffect()
{
	Release();
}

HRESULT CMoveEffect::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Player/Effect/MoveEffect/Case0/MoveCase0_%d.png", L"MoveCase0", L"Idle", 3)))
		return S_FALSE;

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Player/Effect/MoveEffect/Case1/MoveCase1_%d.png", L"MoveCase1", L"Idle", 3)))
		return S_FALSE;

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Player/Effect/MoveEffect/Case0/MoveCase2_%d.png", L"MoveCase2", L"Idle", 3)))
		return S_FALSE;

	m_tInfo.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_wstrObjKey = L"MoveCase0";
	m_wstrStateKey = L"Idle";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 3.f };

	return S_OK;
}
