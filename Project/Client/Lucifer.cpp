#include "stdafx.h"
#include "Lucifer.h"
#include "Device.h"
#include "TextureMgr.h"

CLucifer::CLucifer()
{
	CObj::m_iChapterNum = 7;
}

CLucifer::~CLucifer()
{
	Release();
}

HRESULT CLucifer::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Evil/Lucifer/lucifer%d.png", L"Lucifer", L"Idle", 12)))
		return S_FALSE;

	m_wstrObjKey = L"Lucifer";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 12.f };

	m_tInfo.vPos -= D3DXVECTOR3{ 0.f, 20.f, 0.f };

	Create_LoveSign();

	return S_OK;
}