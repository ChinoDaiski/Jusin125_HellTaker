#include "stdafx.h"
#include "Lucifer.h"
#include "Device.h"
#include "TextureMgr.h"

CLucifer::CLucifer()
{
	// empty
}

CLucifer::~CLucifer()
{
	Release();
}

HRESULT CLucifer::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Evil/Lucifer/lucifer%d.png", L"Lucifer", L"Idle", 12)))
		return S_FALSE;

	m_tInfo.vPos = D3DXVECTOR3(960.f, 170.f, 0.f);
	m_wstrObjKey = L"Lucifer";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 12.f };

	Create_LoveSign();

	return S_OK;
}