#include "stdafx.h"
#include "Modeus.h"
#include "Device.h"
#include "TextureMgr.h"

CModeus::CModeus()
{
	// empty
}

CModeus::~CModeus()
{
	Release();
}

HRESULT CModeus::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Evil/Modeus/modeus%d.png", L"Modeus", L"Idle", 12)))
		return S_FALSE;

	m_wstrObjKey = L"Modeus";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 12.f };

	Create_LoveSign();

	return S_OK;
}