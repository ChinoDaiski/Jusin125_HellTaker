#include "stdafx.h"
#include "BloodEffect.h"

CBloodEffect::CBloodEffect()
{
	// empty
}

CBloodEffect::~CBloodEffect()
{
	Release();
}

HRESULT CBloodEffect::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Player/Effect/BloodEffect/Case0/blood%d.png", L"Blood0", L"Idle", 6)))
		return S_FALSE;

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Player/Effect/BloodEffect/Case1/blood%d.png", L"Blood1", L"Idle", 6)))
		return S_FALSE;

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Player/Effect/BloodEffect/Case2/blood%d.png", L"Blood2", L"Idle", 6)))
		return S_FALSE;

	m_wstrObjKey = L"Blood0";
	m_wstrStateKey = L"Idle";

	m_tFrame = { 0.f, 6.f, 1.f };

	return S_OK;
}
