#include "stdafx.h"
#include "Azazel.h"
#include "Device.h"
#include "TextureMgr.h"

CAzazel::CAzazel()
{
	// empty
}

CAzazel::~CAzazel()
{
	Release();
}

HRESULT CAzazel::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Evil/Azazel/azazel%d.png", L"Azazel", L"Idle", 12)))
		return S_FALSE;

	m_wstrObjKey = L"Azazel";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 12.f };

	Create_LoveSign();

	return S_OK;
}