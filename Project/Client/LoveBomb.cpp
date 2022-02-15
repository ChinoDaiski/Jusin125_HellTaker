#include "stdafx.h"
#include "LoveBomb.h"

CLoveBomb::CLoveBomb()
{
	// empty
}

CLoveBomb::~CLoveBomb()
{
	// empty
}

HRESULT CLoveBomb::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Evil/Effect/LoveBomb/LoveBomb%d.png", L"LoveBomb", L"Idle", 15)))
		return S_FALSE;

	m_wstrObjKey = L"LoveBomb";
	m_wstrStateKey = L"Idle";

	m_tFrame = { 0.f, 15.f, 0.5f };

	return S_OK;
}
