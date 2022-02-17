#include "stdafx.h"
#include "Justice.h"
#include "Device.h"
#include "TextureMgr.h"

CJustice::CJustice()
{
	CObj::m_iChapterNum = 6;
}

CJustice::~CJustice()
{
	Release();
}

HRESULT CJustice::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Evil/Justice/justice%d.png", L"Justice", L"Idle", 12)))
		return S_FALSE;

	m_wstrObjKey = L"Justice";
	m_fSpeed = 100.f;

	m_tFrame = { 0.f, 12.f };

	Create_LoveSign();

	return S_OK;
}