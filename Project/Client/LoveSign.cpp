#include "stdafx.h"
#include "LoveSign.h"

CLoveSign::CLoveSign()
{
	// empty
}

CLoveSign::~CLoveSign()
{
	// empty
}

HRESULT CLoveSign::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture
	(TEX_MULTI, L"../Texture/Player/Effect/LoveSign/LoveSign%d.png", L"LoveSign", L"Idle", 1)))
		return S_FALSE;

	m_wstrObjKey = L"LoveSign";
	m_wstrStateKey = L"Idle";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 1.f };

	return S_OK;
}

void CLoveSign::Late_Update(void)
{
	// empty
}
